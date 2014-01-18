# FAST algorithm
import numpy as np
import cv2
from matplotlib import pyplot as plt
cap = cv2.VideoCapture(0)
img = cv2.imread('foi_zgrada.jpg',0)
while True:
	# Initiate FAST object with default values
	fast = cv2.FastFeatureDetector()
	_, img = cap.read()

	# find and draw the keypoints
	kp = fast.detect(img,None)
	img2 = cv2.drawKeypoints(img, kp, color=(255,0,0))

	# Print all default params
	print "Threshold: ", fast.getInt('threshold')
	print "nonmaxSuppression: ", fast.getBool('nonmaxSuppression')
	print "Total Keypoints with nonmaxSuppression: ", len(kp)

	cv2.imwrite('fast_true.png',img2)

	# Disable nonmaxSuppression
	#fast.setBool('nonmaxSuppression',0)
	kp = fast.detect(img,None)

	print "Total Keypoints without nonmaxSuppression: ", len(kp)

	img3 = cv2.drawKeypoints(img, kp, color=(255,0,0))

	#cv2.imwrite('fast_false.png',img3)
	cv2.imshow('frame',img3)
	key = cv2.waitKey(1)
	if key == 27:
		break