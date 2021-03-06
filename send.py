import time
import serial
import struct

from google.cloud import pubsub_v1

project_id = "communications-1550350888587"
topic_name = "test"

ser = serial.Serial('/dev/tty96B0',9600)

publisher = pubsub_v1.PublisherClient()
topic_path = publisher.topic_path(project_id, topic_name)

def callback(message_future):
    # When timeout is unspecified, the exception method waits indefinitely.
    if message_future.exception(timeout=30):
        print('Publishing message on {} threw an Exception {}.'.format(
            topic_name, message_future.exception()))
    else:
        print(message_future.result())

#for n in range(1, 10):
#    data = u'Message number {}'.format(n)
    # Data must be a bytestring
#    data = data.encode('utf-8')
    # When you publish a message, the client returns a Future.
#    message_future = publisher.publish(topic_path, data=data)
#    message_future.add_done_callback(callback)

#print('Published message IDs:')

# We must keep the main thread from exiting to allow it to process
# messages in the background.
x_old = 0
while True:
    if (ser.in_waiting > 0):
        x = ser.read(1)
        x = struct.unpack('>H', b'\x00' + x)[0]
        if (abs(x-x_old) > 5):
            print(x)
            data = '{}'.format(x)
            data = data.encode('utf-8')
            message_future = publisher.publish(topic_path, data=data)
            message_future.add_done_callback(callback)
            print(data)
            x_old = x
