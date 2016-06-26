import cv2
import numpy as np


def nothing(x):
    pass


def drawAOI(img, area_x, area_y, area_width, area_height):
    color = (0, 0, 255)
    cv2.rectangle(img, (area_x, area_y), (area_width, area_height), color, 0)


def trackValues():
    x = cv2.getTrackbarPos('posx', 'image')
    y = cv2.getTrackbarPos('posy', 'image')
    width = cv2.getTrackbarPos('width', 'image')
    height = cv2.getTrackbarPos('height', 'image')
    s = cv2.getTrackbarPos(switch, 'image')
    return (x, y, width, height, s)

# Create a black image, a window
emptyImage = np.zeros((300, 512, 3), np.uint8)
cv2.namedWindow('image')

# loads actual image from disk
actualImage = cv2.imread("jurassic_world.jpg")
height, width = actualImage.shape[:2]

# create trackbars for color change
cv2.createTrackbar('posx', 'image', 0, width, nothing)
cv2.createTrackbar('posy', 'image', 0, height, nothing)
cv2.createTrackbar('width', 'image', 0, width, nothing)
cv2.createTrackbar('height', 'image', 0, height, nothing)

# create switch for ON/OFF functionality
switch = '0 : OFF \n1 : ON'
cv2.createTrackbar(switch, 'image', 0, 1, nothing)

while(1):
    k = cv2.waitKey(1) & 0xFF
    if k == 27:
        break

    overlay = actualImage.copy()
    # get current positions of five trackbars
    (area_x, area_y, area_width, area_height, s) = trackValues()

    if s == 0:
        cv2.imshow('image', emptyImage.copy())
    else:
        drawAOI(overlay, area_x, area_y, area_width, area_height)
        cv2.imshow('image', overlay)


cv2.destroyAllWindows()
