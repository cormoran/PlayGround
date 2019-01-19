import signal
import time


def task(arg1, arg2):
    print(time.time())


signal.signal(signal.SIGALRM, task)
signal.setitimer(signal.ITIMER_REAL, 0.1, 0.1)

while True:
    time.sleep(1)