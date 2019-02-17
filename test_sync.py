import logging
import multiprocessing
import time
import serial

from google.cloud import pubsub_v1

project_id = "communications-1550350888587"
subscription_name = "testsub"

subscriber = pubsub_v1.SubscriberClient()
subscription_path = subscriber.subscription_path(
    project_id, subscription_name)

NUM_MESSAGES = 2
ACK_DEADLINE = 30
SLEEP_TIME = 10

# The subscriber pulls a specific number of messages.
response = subscriber.pull(subscription_path, max_messages=NUM_MESSAGES)

multiprocessing.log_to_stderr()
logger = multiprocessing.get_logger()
logger.setLevel(logging.INFO)

def worker(msg):
    """Simulates a long-running process."""
    RUN_TIME = 3000
    logger.info('{}: Running {} for {}s'.format(
        time.strftime("%X", time.gmtime()), msg.message.data, RUN_TIME))
    time.sleep(RUN_TIME)

# `processes` stores process as key and ack id and message as values.
processes = dict()
for message in response.received_messages:
    process = multiprocessing.Process(target=worker, args=(message,))
    processes[process] = (message.ack_id, message.message.data)
    process.start()

while processes:
    for process in list(processes):
        ack_id, msg_data = processes[process]
        # If the process is still running, reset the ack deadline as
        # specified by ACK_DEADLINE once every while as specified
        # by SLEEP_TIME.
        if process.is_alive():
            # `ack_deadline_seconds` must be between 10 to 600.
            subscriber.modify_ack_deadline(
                subscription_path,
                [ack_id],
                ack_deadline_seconds=ACK_DEADLINE)
            logger.info('{}: Reset ack deadline for {} for {}s'.format(
                time.strftime("%X", time.gmtime()),
                msg_data, ACK_DEADLINE))

        # If the processs is finished, acknowledges using `ack_id`.
        else:
            subscriber.acknowledge(subscription_path, [ack_id])
            logger.info("{}: Acknowledged {}".format(
                time.strftime("%X", time.gmtime()), msg_data))
            processes.pop(process)

    # If there are still processes running, sleeps the thread.
    if processes:
        time.sleep(SLEEP_TIME)

print("Received and acknowledged {} messages. Done.".format(NUM_MESSAGES))
