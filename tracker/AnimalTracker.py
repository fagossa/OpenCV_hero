import cv2
import tracker.AOITracker


class AnimalTracker:
    """ Handle the animal detection and recognition """

    def __init__(self, windowName):
        print "AnimalTracker::__init__"
        self.windowName = windowName
        self.counter = 0

    def update(self, baseImg):
        self.counter = self.counter + 1
        self.baseImg = baseImg
        img = cv2.blur(baseImg, (5, 5))
        # calculates diff
        imgray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        ret, thresh = cv2.threshold(imgray, 127, 255, 0)
        _, contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        self.img = imgray
        self.contours = contours
        self.persistIteration(imgray)

    def persistIteration(self, img):
        cv2.imwrite("tests/result-" + str(self.counter) + ".png", img)

    def getCounter(self):
        return self.counter

    def display(self):
        # shows the aoi
        width, height = self.img.shape[:2]
        if width > 0 and height > 0:
            cv2.imshow("aoi", self.img)
            cv2.imshow("aoi-original", self.baseImg)
            cv2.drawContours(self.img, self.contours, -1, (0, 255, 0), 1)
