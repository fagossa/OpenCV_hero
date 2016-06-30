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
        self.updateDimensions(self.actualImage)
        print "Window::found image having w:{0} h:{1}".format(str(self.width), str(self.height))
        self.emptyImage = np.zeros((self.width, self.height, 3), np.uint8)
        self.tracker = tracker.AnimalTracker(self.windowName, self.width, self.height)
        self.display(1)
        print "Window::bye"

    def updateDimensions(self, image):
        width, height = image.shape[:2]
        self.height = height
        self.width = width

    def display(self, condition):
        print "Window::displayLoop"
        while(condition):
            k = cv2.waitKey(1) & 0xFF
            if k == 27:
                break

            s = self.tracker.hasStarted()
            if s == 0:
                temp = self.emptyImage
                cv2.imshow(self.windowName, temp.copy())
            else:
                overlay = self.actualImage.copy()
                self.tracker.update(overlay)
                self.tracker.display()
                cv2.imshow(self.windowName, overlay)
        cv2.destroyAllWindows()
