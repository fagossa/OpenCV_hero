import cv2


class AOITracker:
    """ Handle tracker components """

    def __init__(self, windowName, switch):
        print "AnimalTracker::__init__"
        self.windowName = windowName
        self.switch = switch

    def createTrackers(self, width, height):
        cv2.createTrackbar('posx', self.windowName, 0, width, self.nothing)
        cv2.createTrackbar('posy', self.windowName, 0, height, self.nothing)
        cv2.createTrackbar('width', self.windowName, 0, width, self.nothing)
        cv2.createTrackbar('height', self.windowName, 0, height, self.nothing)
        cv2.createTrackbar(self.switch, self.windowName, 0, 1, self.nothing)

    def trackSwitchValue(self):
        """ create trackbars for color change """
        return cv2.getTrackbarPos(self.switch, self.windowName)

    def trackValues(self):
        """ get values from trackers """
        x = cv2.getTrackbarPos('posx', self.windowName)
        y = cv2.getTrackbarPos('posy', self.windowName)
        width = cv2.getTrackbarPos('width', self.windowName)
        height = cv2.getTrackbarPos('height', self.windowName)
        return (x, y, width, height)

    def nothing(self, param):
        pass
