from flask import Flask,render_template,request
from imutils.video import VideoStream
from flask import Response
import argparse
import imutils
import cv2
import time
import threading

outputFrame = None
#lock = threading.Lock()

app = Flask(__name__)

vs = VideoStream(usePiCamera=1).start()
time.sleep(2.0)
#def stream():
#    global vs, outputFrame, lock 
#
#    while True:
#        with lock:
#                outputFrame = frame.copy()

def generate():
    global outputFrame, lock

    while True:
        frame = vs.read()
        frame = imutils.rotate(frame, 180)
        frame = imutils.resize(frame, width=800)
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.GaussianBlur(gray, (7,7), 0)

        outputFrame = frame

        (flag, encodedImage) = cv2.imencode(".jpg", outputFrame)

        yield (b'--frame\r\n' b'Content-Type: image/jpeg\r\n\r\n' + bytearray(encodedImage) + b'\r\n')

@app.route('/')
def hello_world():
    return render_template('index.html') 

@app.route('/video_feed')
def video_feed():
    return Response(generate(), mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/hello/<name>')
def hello_name(name):
    return "Wasssup Mr. %s" % name

@app.route("/control", methods=["POST"])
def get_control():
    print(request.method)
    code = request.form["control_code"]
    print(code)
    return ('', 200) 



if __name__=="__main__":
    #app.run(host, port, debug, options)
    #t = threading.Thread(target=stream)
    #t.daemon=True
    #t.start()
    app.debug = True
    app.run("192.168.0.22", 5000, debug=True, threaded = True, use_reloader = False)

vs.stop()
