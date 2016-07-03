from tracker import Window
from tracker import Point
from array import array

# default aoi
p1 = Point(178, 162)
p2 = Point(427, 416)

# Loads the default image
frames = [
    'resources/train-way-step0.png',
    'resources/train-way-step1.png',
    'resources/train-way-step2.png'
]
launcher = Window(frames, p1, p2)
