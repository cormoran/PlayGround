import multiprocessing as mp
import time


def run(args):
    lock, obj, val = args
    with lock:
        print("locked {}".format(mp.current_process()))
        time.sleep(1)
    print("released {}".format(mp.current_process()))
    time.sleep(1)


def start(procs=10):
    m = mp.Manager()
    obj = m.dict()
    lock = m.Lock()
    for i in range(procs):
        obj[i] = 0
    with mp.Pool(processes=5) as pool:
        pool.map(run, map(lambda i: (lock, obj, i), range(procs)))


start()