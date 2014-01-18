import cv2
import numpy as np

#ucitavanje prve slike
img1 = cv2.imread('foi_zgrada.jpg')
#ucitavanje druge slike
img2 = cv2.imread('foi_logo.jpg')

#blending -> postavljanje opacity-ja za pojedinu sliku
src = cv2.addWeighted(img1,0.50,img2,0.60,0)
while(1):
	#resize slike (jer je 1600*1200)
	dst = cv2.resize(src,None,fx=0.5, fy=0.5, interpolation = cv2.INTER_AREA)
	#prikaz
	cv2.imshow('image', dst)
	k = cv2.waitKey(1)
	if k == 27:
		break
		
cv2.destroyAllWindows()
