import threading, queue
from asyncio import wait
from threading import Lock
from random import randint
import random
from random import choice
from string import ascii_uppercase
import time

q = queue.Queue(3)
ql = queue.Queue(3)
carsList = []
cnt = 0
cntL = 0
lc = []
rc = []
has_lock_a = -1
has_lock_b = -1
has_lock_c = -1


class Car:
    def __init__(self, t_arrive, direction, name, idx):
        self.t_arrive = t_arrive
        self.direction = direction
        self.name = name
        self.idx = idx
        self.currDir = 0

    def __str__(self):
        return "Car(name: " + self.name + ", time: " + str(self.t_arrive) + ", direction: " + str(
            self.direction) + ")\n"


class Bridge:

    def __init__(self):
        self.threads = []
        self.threadCnt = 0
        self.cntL = 0
        self.cnt = 0
        self.rc_nt = 0
        self.lock_a = Lock()
        self.lock_b = Lock()
        self.lock_c = Lock()
        self.lock_d = Lock()
        self.lock_e = Lock()
        self.lock_f = Lock()
        self.sem = threading.Semaphore(0)
        self.capacity = 3
        self.dir = -1

    def workerR(self):

        while True:
            itemR = q.get()
            print(itemR)
            if rc:
                index = rc.pop(0)
                self.arrive_bridge(carsList[index], index)

                self.lock_a.acquire()
                self.cntL += 1
                self.cross_bridge(carsList[index], index)
                self.exit_bridge(carsList[index])
                self.lock_a.release()
                self.dir = carsList[index].direction
                self.rc_nt += 1
                q.task_done()

    def workerR2(self):

        while True:
            itemR = q.get()
            print(itemR)
            if rc:
                index = rc.pop(0)
                self.arrive_bridge(carsList[index], index)
                self.lock_a.acquire()
                self.cntL += 1
                self.cross_bridge(carsList[index], index)
                self.exit_bridge(carsList[index])
                self.lock_a.release()
                self.dir = carsList[index].direction
                self.rc_nt += 1
                q.task_done()

    def workerR3(self):
        while True:
            itemR = q.get()
            print(itemR)
            if rc:
                index = rc.pop(0)
                self.arrive_bridge(carsList[index], index)
                self.lock_a.acquire()
                self.cntL += 1
                self.cross_bridge(carsList[index], index)
                self.exit_bridge(carsList[index])
                self.lock_a.release()
                self.dir = carsList[index].direction
                self.rc_nt += 1
                q.task_done()

    def workerL(self):
        while True:
            itemL = ql.get()
            print(itemL)
            if lc:
                index = lc.pop(0)
                self.arrive_bridge(carsList[index], index)

                self.lock_a.acquire()
                self.cntL += 1

                self.cross_bridge(carsList[index], index)
                self.exit_bridge(carsList[index])
                self.lock_a.release()
                self.dir = carsList[index].direction
                ql.task_done()

    def workerL2(self):
        while True:
            itemL = ql.get()
            print(itemL)
            if lc:
                index = lc.pop(0)
                self.arrive_bridge(carsList[index], index)

                self.lock_a.acquire()
                self.cntL += 1

                self.cross_bridge(carsList[index], index)
                self.exit_bridge(carsList[index])
                self.lock_a.release()
                self.dir = carsList[index].direction
                ql.task_done()

    def workerL3(self):
        while True:
            itemL = ql.get()
            print(itemL)
            if lc:
                index = lc.pop(0)

                self.arrive_bridge(carsList[index], index)
                self.lock_a.acquire()
                self.cntL += 1
                self.cross_bridge(carsList[index], index)
                self.exit_bridge(carsList[index])
                self.lock_a.release()
                self.dir = carsList[index].direction
                ql.task_done()

    def arrive_bridge(self, car: Car, cnt):
        print(car.name + " arrived at bridge\n")

    def cross_bridge(self, car: Car, cnt):
        print(car.name + " crossing bridge\n")
        time.sleep(car.t_arrive)

    def exit_bridge(self, car: Car):
        print(car.name + " Exiting bridge\n")


if __name__ == "__main__":
    totalNumberOfCars = randint(8, 11)

    id = 0
    for i in range(totalNumberOfCars):
        direction = randint(0, 1)
        time3 = randint(3, 5)

        car = Car(time3, direction, ''.join(choice(ascii_uppercase) for z in range(4)), id)
        id += 1
        carsList.append(car)
    random.shuffle(carsList)
    car_cnt = 0
    for car in carsList:
        car.idx = car_cnt
        car_cnt += 1
    # turn-on the worker thread
    bridge = Bridge()
    threading.Thread(target=bridge.workerR, daemon=True).start()
    threading.Thread(target=bridge.workerR2, daemon=True).start()
    threading.Thread(target=bridge.workerR3, daemon=True).start()
    threading.Thread(target=bridge.workerL, daemon=True).start()
    threading.Thread(target=bridge.workerL2, daemon=True).start()
    threading.Thread(target=bridge.workerL3, daemon=True).start()
    # send thirty task requests to the worker
    for item in range(len(carsList)):
        if carsList[item].direction == 1:
            q.put(carsList[item])
            rc.append(item)
        else:
            ql.put(carsList[item])
            lc.append(item)
    # block until all tasks are done
    q.join()
    print("-------------. 2. > " + str(len(carsList)))
    print('All work completed')
