import numpy as np
import cv2
from itertools import cycle

cap = cv2.VideoCapture(0)

modes = cycle([cv2.COLOR_BGR2GRAY, 0])
cur_mode = modes.next()
func = 4
while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Our operations on the frame come here
    if func == 0:
    	frm = cv2.Laplacian(frame,cv2.CV_64F)
    elif func == 1:
    	frm = cv2.GaussianBlur(frame,(0,0),5)
    elif func == 2:
    	frm = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    elif func == 3:
    	frm = cv2.Canny(frame, 5, 100)
    else:
    	frm = cv2.cvtColor(frame, 0)


    # Display the resulting frame
    cv2.imshow('frame',frm)
    key = cv2.waitKey(1)
    if key == 27:
    	break
    if key == ord('a'):
    	print func
    	func = 1
    if key == ord('s'):
    	func = 0
    if key == ord('d'):
    	func = 2
    if key == ord('f'):
    	func = 3
# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()