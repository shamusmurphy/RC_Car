"""
    Python script that runs a live stream
    feed from the camera on the RC Car to
    a web page.
    Created by Shamus Murphy
"""

from flask import Flask, Response, request
from flask_cors import CORS
from picamera2 import Picamera2
from PIL import Image
from time import sleep
import io

app = Flask(__name__)

#allow react app to make requests flask using Cross-Origin Resource Sharing
CORS(app)

#initialize camera
cam = Picamera2()


#function for camera
def start_video():
    cam.start()
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


#speed
@app.route('/set_speed', methods=['POST'])
def set_speed():
    speed = request.json['speed']
    #MASON - all you bro
    return {'status': 'success'}

#direction
@app.route('/set_direction', methods=['POST'])
def set_direction():
    direction = request.json['direction']
    #MASON = all you bro
    return {'status': 'success'}

if __name__ == '__main__':
    #run flask app
    app.run(host='0.0.0.0', port=5000)
