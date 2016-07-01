import unittest
import cv2
import tracker.AnimalTracker
from tracker import Point

class AnimalTrackerTest(unittest.TestCase):

    def testAnimalTracker(self):
        self.step0 = cv2.imread("../resources/train-way-step0.jpg")
        animal = tracker.AnimalTracker("window")
        animal.update(self.step0)
        animal.update(self.step0)
        animal.update(self.step0)
        self.assertEqual(animal.getCounter(), 3)
