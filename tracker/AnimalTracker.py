import cv2
import tracker.AOITracker


class AnimalTracker:
    """ Handle the animal detection and recognition """

    def __init__(self, windowName, max_width, max_height):
        print "AnimalTracker::__init__"
        self.windowName = windowName

    def update(self, img):
        self.crop_img = img

    def display(self):
        # shows the aoi
        width, height = self.crop_img.shape[:2]
        if width > 0 and height > 0:
            cv2.imshow("aoi", self.crop_img)
