import cv2
import numpy as np
import tracker.AnimalTracker


class Window:
    """ Handles application loop"""

    def __init__(self, imgName):
        print "Window::__init__"
        self.windowName = 'image'
        cv2.namedWindow(self.windowName)
        self.actualImage = cv2.imread(imgName)
        # update dimensions
        width, height = self.actualImage.shape[:2]
        self.height = height
        self.width = width
        print "Window::found image having w:{0} h:{1}".format(str(self.width), str(self.height))
        self.emptyImage = np.zeros((self.width, self.height, 3), np.uint8)
        # animal tracker
        self.tracker = tracker.AnimalTracker(self.windowName, self.width, self.height)
        # aoi tracker
        self.aoi = tracker.AOITracker(self.windowName, '0 : OFF \n1 : ON')
        self.aoi.createTrackers(self.width, self.height)
        # display loop
        self.displayLoop(1)
        print "Window::bye"

    def hasStarted(self):
        return self.aoi.trackSwitchValue()

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

            s = self.hasStarted()
            if s == 0:
                temp = self.emptyImage
                cv2.imshow(self.windowName, temp.copy())
            else:
                overlay = self.actualImage.copy()
                aoiImg = self.aoi.getAOI(overlay)
                self.tracker.update(aoiImg)
                self.tracker.display()
                self.displayRectangle(overlay)
                cv2.imshow(self.windowName, overlay)
        cv2.destroyAllWindows()
