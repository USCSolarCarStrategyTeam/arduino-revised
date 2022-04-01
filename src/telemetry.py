import time
from random import randint
from multiprocessing import Process, Queue, Pipe


# pipe testing
def generate_random_update():
    data_type = randint(1, 6)
    data_val = 0
    if data_type == 1:  # speed
        data_val = randint(50, 59)
    elif data_type == 2:  # range
        data_val = randint(40, 49)
    elif data_type == 3:  # battery
        data_val = randint(0, 99)
    elif data_type == 4:  # temp
        data_val = randint(60, 69)
    elif data_type == 5:  # current
        data_val = randint(60, 69)
    elif data_type == 6:  # power
        data_val = randint(60, 69)
    return data_type + ' ' + data_val

def send_updates(sender):
    while 1:
        msg = generate_random_update()
        sender.send(msg)
        time.sleep(60)
    sender.close()

