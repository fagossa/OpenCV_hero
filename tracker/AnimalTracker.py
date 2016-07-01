import cv2
import tracker.AOITracker


class AnimalTracker:
    """ Handle the animal detection and recognition """

    def __init__(self, windowName):
        print "AnimalTracker::__init__"
        self.windowName = windowName
        self.counter = 0

    def update(self, img):
        self.img = img
        self.counter = self.counter + 1

    def getCounter(self):
        return self.counter

    def display(self):
        # shows the aoi
        width, height = self.img.shape[:2]
        if width > 0 and height > 0:
            cv2.imshow("aoi", self.img)
