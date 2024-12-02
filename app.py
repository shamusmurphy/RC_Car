"""
    Python script that runs a live stream
    feed from the camera on the RC Car to
    a web page.
    Created by Shamus Murphy
"""

from flask import Flask, Response, request
from picamera2 import Picamera2
from PIL import Image
from time import sleep
import io
<<<<<<< HEAD
=======
from PIL import Image
>>>>>>> 765c7ec2229a8d16bd7decfe9d69929669803f04
import serial

app = Flask(__name__)

#initialize camera
cam = Picamera2()

# initialize serial communication
ser = serial.Serial("/dev/ttyUSB0", 9600, timeout=1)
ser.reset_input_buffer()


<<<<<<< HEAD
#function for camera
def start_video():
    cam.start()
=======
# initialize serial communication
ser = serial.Serial("/dev/ttyUSB0", 9600, timeout=1)
ser.reset_input_buffer()

#function to generate live video
def generate_frames():
    picam2.start()
>>>>>>> 765c7ec2229a8d16bd7decfe9d69929669803f04
    try:
        while True:
            frame = cam.capture_array()

            #stream variable to temp store data
            stream = io.BytesIO()

            #need to convert from rgba to rgb
            #would not work otherwise
            Image.fromarray(frame).convert("RGB").save(stream, format="JPEG")
            stream.seek(0)

            #yield to efficiently generate frames
            #translating from jpeg to mjpeg format to have continous stream
            yield (b'--frame\r\n'
                    b'Content-Type: image/jpeg\r\n\r\n' + stream.getvalue() + b'\r\n')
            stream.seek(0)
            stream.truncate()
    finally:
        #turn off camera
        cam.stop()

#render stream
#MIME type (Multipurpose Internet Mail Extensions) verifies the content being received
@app.route('/stream')
def live_stream():
    return Response(start_video(),
                mimetype='multipart/x-mixed-replace; boundary=frame')


#commans root
@app.route('/command/<command>', methods=['POST'])
def handle_command(command):
<<<<<<< HEAD
    if command == 'increase':
        print("Increase command received")
        ser.write("f")
    elif command == 'Decrease':
        print("Decrease command received")
=======
    if command == 'forward':
        print("Forward command received")
        ser.write("f")
    elif command == 'reverse':
        print("Reverse command received")
>>>>>>> 765c7ec2229a8d16bd7decfe9d69929669803f04
        ser.write("b")
    elif command == 'left':
        print("Left command received")
        ser.write("l")
    elif command == 'right':
        print("Right command received")
        ser.write("r")
<<<<<<< HEAD
=======
    
    # json that does not work yet
    return jsonify({"status": "success", "command": command})
>>>>>>> 765c7ec2229a8d16bd7decfe9d69929669803f04

if __name__ == '__main__':
    #run flask app
    app.run(host='0.0.0.0', port=5000)
