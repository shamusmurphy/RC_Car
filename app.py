""" Python script that runs a live stream feed from a camera
	to a web page index.html. Also takes in inputs for 
	forward, reverse, right, and left. 
"""

from flask import Flask, Response, render_template, request, jsonify
from picamera2 import Picamera2
from time import sleep
import io
from PIL import Image
import serial

app = Flask(__name__)

#initialize camera
picam2 = Picamera2()
picam2.configure(picam2.create_preview_configuration())

# initialize serial communication
ser = serial.Serial("/dev/ttyUSB0", 9600, timeout=1)
ser.reset_input_buffer()

#function to generate live video
def generate_frames():
    picam2.start()
    try:
        while True:
            frame = picam2.capture_array()

            # convert to rgb format since rgba does not work for some reason
            stream = io.BytesIO()
            Image.fromarray(frame).convert("RGB").save(stream, format='JPEG')
            stream.seek(0)
            
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + stream.getvalue() + b'\r\n')
            stream.seek(0)
            stream.truncate()
    finally:
        picam2.stop()

#render html
@app.route('/')
def index():
    return render_template('index.html')

#render stream
@app.route('/stream')
def video_feed():
    return Response(generate_frames(),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

#commans root
@app.route('/command/<command>', methods=['POST'])
def handle_command(command):
    if command == 'forward':
        print("Forward command received")
        ser.write("f")
    elif command == 'reverse':
        print("Reverse command received")
        ser.write("b")
    elif command == 'left':
        print("Left command received")
        ser.write("l")
    elif command == 'right':
        print("Right command received")
        ser.write("r")
    
    # json that does not work yet
    return jsonify({"status": "success", "command": command})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

