import cv2
import numpy as np
import tracker.AnimalTracker


class Main:
    """ Handles application loop"""

    # create switch for ON/OFF functionality
    switch = '0 : OFF \n1 : ON'
    tracker = tracker.AnimalTracker

    def __init__(self, imgName):
        cv2.namedWindow('image')
        self.actualImage = cv2.imread(imgName)
        self.height, self.width = self.actualImage.shape[:2]
        self.createTrackers
        self.displayLoop

    def createTrackers(self):
        """ create trackbars for color change """
        cv2.createTrackbar('posx', 'image', 0, self.width, self.nothing)
        cv2.createTrackbar('posy', 'image', 0, self.height, self.nothing)
        cv2.createTrackbar('width', 'image', 0, self.width, self.nothing)
        cv2.createTrackbar('height', 'image', 0, self.height, self.nothing)
        cv2.createTrackbar(self.switch, 'image', 0, 1, self.nothing)

    def trackValues(self):
        """ get values from trackers """
        x = cv2.getTrackbarPos('posx', 'image')
        y = cv2.getTrackbarPos('posy', 'image')
        width = cv2.getTrackbarPos('width', 'image')
        height = cv2.getTrackbarPos('height', 'image')
        s = cv2.getTrackbarPos(self.switch, 'image')
        return (x, y, width, height, s)

    def nothing(self):
        pass

    def emptyImage(self):
        np.zeros((300, 512, 3), np.uint8)

    def displayLoop(self):
        while(1):
            k = cv2.waitKey(1) & 0xFF
            if k == 27:
                break

            overlay = self.actualImage.copy()
            # get current positions of five trackbars
            (area_x, area_y, area_w, area_h, s) = self.trackValues()

            if s == 0:
                cv2.imshow('image', self.emptyImage.copy())
            else:
                self.tracker.update(overlay, area_x, area_y, area_w, area_h)
                self.tracker.displey
                cv2.imshow('image', overlay)
        cv2.destroyAllWindows()
