import cv2
import numpy as np
import tracker.AnimalTracker


class Window:
    """ Handles application loop"""

    def __init__(self, imgName):
        print "Window::__init__"
        cv2.namedWindow('image')
        # create switch for ON/OFF functionality
        self.switch = '0 : OFF \n1 : ON'
        self.actualImage = cv2.imread(imgName)
        self.updateDimensions(self.actualImage)
        print "Window::found image having w:{0} h:{1}".format(str(self.width), str(self.height))
        self.emptyImage = np.zeros((self.width, self.height, 3), np.uint8)
        self.tracker = tracker.AnimalTracker(imgName)
        self.createTrackers("image")
        self.display(1)
        print "Window::bye"

    def updateDimensions(self, image):
        width, height = image.shape[:2]
        self.height = height
        self.width = width

    def createTrackers(self, name):
        """ create trackbars for color change """
        cv2.createTrackbar('posx', 'image', 0, self.width, self.nothing)
        cv2.createTrackbar('posy', 'image', 0, self.height, self.nothing)
        cv2.createTrackbar('width', 'image', 0, self.width, self.nothing)
        cv2.createTrackbar('height', 'image', 0, self.height, self.nothing)
        cv2.createTrackbar(self.switch, 'image', 0, 1, self.nothing)

    def trackValues(self, switch):
        """ get values from trackers """
        x = cv2.getTrackbarPos('posx', 'image')
        y = cv2.getTrackbarPos('posy', 'image')
        width = cv2.getTrackbarPos('width', 'image')
        height = cv2.getTrackbarPos('height', 'image')
        s = cv2.getTrackbarPos(switch, 'image')
        return (x, y, width, height, s)

    def nothing(self, param):
        pass

    def display(self, condition):
        print "Window::displayLoop"
        while(condition):
            k = cv2.waitKey(1) & 0xFF
            if k == 27:
                break

            overlay = self.actualImage.copy()
            # get current trackbars positions
            (area_x, area_y, area_w, area_h, s) = self.trackValues(self.switch)

            if s == 0:
                temp = self.emptyImage
                cv2.imshow('image', temp.copy())
            else:
                self.tracker.update(overlay, area_x, area_y, area_w, area_h)
                self.tracker.display
                cv2.imshow('image', overlay)
        cv2.destroyAllWindows()
