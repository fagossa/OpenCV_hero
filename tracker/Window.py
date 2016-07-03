import cv2
import numpy as np
import tracker.AnimalTracker
import tracker.Point



class Window:
    """ Handles application loop"""

    def __init__(self, frames, p1, p2):
        print "Window::__init__"
        self.windowName = 'image'
        cv2.namedWindow(self.windowName)
        # animal tracker
        self.tracker = tracker.AnimalTracker(self.windowName, False)
        # aoi tracker
        self.frames = map(lambda x: cv2.imread(x), frames)
        self.aoi = tracker.AOITracker(self.windowName, p1, p2)
        # first image to get image size
        firstImage = self.frames[0]
        width, height = firstImage.shape[:2]
        # create trackers
        self.aoi.createTrackers(width, height, len(self.frames))
        # display loop
        self.displayLoop(1)
        print "Window::bye"

    def displayRectangle(self, img):
        c = (0, 0, 255)
        (x1, y1, x2, y2) = self.aoi.getCurrentPosition()
        cv2.rectangle(img, (x1, y1), (x2, y2), c, 0)

    def displayLoop(self, condition):
        print "Window::displayLoop"
        while(condition):
            k = cv2.waitKey(1) & 0xFF
            if k == 27:
                break

            framePos = self.aoi.currentFrame()
            frameImg = self.frames[framePos]
            overlay = frameImg.copy()
            aoiImg = self.aoi.getAOI(overlay)
            self.tracker.update(aoiImg)
            self.tracker.display()
            self.displayRectangle(overlay)
            cv2.imshow(self.windowName, overlay)
        cv2.destroyAllWindows()
