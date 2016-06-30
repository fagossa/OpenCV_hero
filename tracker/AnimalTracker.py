import cv2


class AnimalTracker:
    """ Handle the animal detection and recognition """

    def __init__(self, imgName):
        print "AnimalTracker::__init__"
        self.imgName = imgName

    def update(self, img, area_x, area_y, area_width, area_height):
        self.img = img
        self.c = (0, 0, 255)
        self.x = area_x
        self.y = area_y
        self.w = area_x + area_width
        self.h = area_y + area_height

    def display(self):
        cv2.rectangle(self.img, (self.x, self.y), (self.w, self.h), self.c, 0)
