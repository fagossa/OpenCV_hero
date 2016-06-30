import cv2


class AnimalTracker:
    """ Handle the animal detection and recognition """

    def __init__(self, windowName):
        print "AnimalTracker::__init__"
        self.windowName = windowName
        # create switch for ON/OFF functionality
        self.switch = '0 : OFF \n1 : ON'

    def createTrackers(self, width, height):
        """ create trackbars for color change """
        cv2.createTrackbar('posx', self.windowName, 0, width, self.nothing)
        cv2.createTrackbar('posy', self.windowName, 0, height, self.nothing)
        cv2.createTrackbar('width', self.windowName, 0, width, self.nothing)
        cv2.createTrackbar('height', self.windowName, 0, height, self.nothing)
        cv2.createTrackbar(self.switch, self.windowName, 0, 1, self.nothing)

    def trackSwitchValue(self):
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

    def update(self, img):
        (x, y, width, height) = self.trackValues()
        self.img = img
        self.c = (0, 0, 255)
        self.x1 = x
        self.y1 = y
        self.x2 = x + width
        self.y2 = y + height
        print "AnimalTracker::x:{0} y:{1}, w:{2} h:{3}".format(str(self.x1), str(self.y1), str(self.x2), str(self.y2))

    def display(self):
        cv2.rectangle(self.img, (self.x1, self.y1), (self.x2, self.y2), self.c, 0)
