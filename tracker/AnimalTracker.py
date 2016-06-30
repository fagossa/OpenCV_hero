import cv2
import tracker.AOITracker


class AnimalTracker:
    """ Handle the animal detection and recognition """

    def __init__(self, windowName, max_width, max_height):
        print "AnimalTracker::__init__"
        self.windowName = windowName
        # create switch for ON/OFF functionality
        self.switch = '0 : OFF \n1 : ON'
        self.aoi = tracker.AOITracker(self.windowName, self.switch)
        self.aoi.createTrackers(max_width, max_height)

    def hasStarted(self):
        return self.aoi.trackSwitchValue()

    def update(self, img):
        (x, y, width, height) = self.aoi.trackValues()
        self.img = img
        self.c = (0, 0, 255)
        self.x1 = x
        self.y1 = y
        self.x2 = x + width
        self.y2 = y + height
        self.crop_img = img[self.y1:self.y2, self.x1:self.x2]

    def display(self):
        # shows the aoi
        width, height = self.crop_img.shape[:2]
        if width > 0 and height > 0:
            cv2.imshow("aoi", self.crop_img)
        cv2.rectangle(self.img, (self.x1, self.y1), (self.x2, self.y2), self.c, 0)
