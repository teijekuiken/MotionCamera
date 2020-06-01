import paho.mqtt.client as mqttclient 
import time
from picamera import PiCamera

camera = PiCamera()

def on_connect(client, userdata, flags, rc):
    if rc==0:
        print("client is connected")
        global connected
        connected=True
    else:
        print("client is not connected")

def on_message(client, userdate, message):
    messagePayload = str(message.payload.decode("utf-8"))
    if messagePayload == "FIRE!":
        camera.capture('/home/pi/Desktop/image255.jpg')
        print("capture")

connected=False
Messagerecieved=False

broker_address="192.168.2.31"

print("creating new instance")
client= mqttclient.Client("P1")
client.on_message = on_message
client.on_connect=on_connect
client.connect(broker_address)
client.loop_start()
client.subscribe("dev/test")
while connected!=True:
    time.sleep(0.2)
while Messagerecieved!=True:
    time.sleep(0.2)
client.loop_stop()
