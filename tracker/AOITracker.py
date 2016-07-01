import cv2


class AOITracker:
    """ Handle tracker components """

    def __init__(self, windowName, switch, p1, p2):
        print "AOITracker::__init__"
        self.windowName = windowName
        self.switch = switch
        self.calculateDefaultPosition(p1, p2)

    def calculateDefaultPosition(self, p1, p2):
        self.y = p1.y
        self.x = p1.x
        self.width = p2.x - p1.x
        self.height = p2.y - p1.y

    def createTrackers(self, width, height):
        cv2.createTrackbar('posx', self.windowName, self.x, width, self.nothing)
        cv2.createTrackbar('posy', self.windowName, self.y, height, self.nothing)
        cv2.createTrackbar('width', self.windowName, self.width, width, self.nothing)
        cv2.createTrackbar('height', self.windowName, self.height, height, self.nothing)
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

    def getCurrentPosition(self):
        (x, y, width, height) = self.trackValues()
        return (x, y, x + width, y + height)

    def getAOI(self, img):
        (x1, y1, x2, y2) = self.getCurrentPosition()
        return img[y1:y2, x1:x2]

    def nothing(self, param):
        pass
