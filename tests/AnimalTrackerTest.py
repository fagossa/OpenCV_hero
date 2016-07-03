import unittest
import os
import cv2
import numpy as np

import tracker.AnimalTracker
from tracker import Point

this_dir = os.path.dirname(os.path.realpath(__file__))


def pathFor(img_name):
    return os.path.join(this_dir, img_name)


class AnimalTrackerTest(unittest.TestCase):

    def testAnimalTracker(self):
        self.step0 = cv2.imread(pathFor('train-way-step0.png'))
        self.step1 = cv2.imread(pathFor("train-way-step1.png"))
        animal = tracker.AnimalTracker("window", True)
        animal.update(self.step0)
        animal.update(self.step0)
        animal.update(self.step0)
        animal.update(self.step1)
        self.assertEqual(animal.getCounter(), 4)
