#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int g_slider_position = 0;
CvCapture* g_capture = NULL;
void onTrackbarSlide(int pos) {
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
}

int main( int argc, char** argv ) {
	cvNamedWindow( "Example2", CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture( argv[1] );
	int frames = (int) cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT);
	if( frames!= 0 ) {
		cvCreateTrackbar("Position", "Example3", &g_slider_position, frames, onTrackbarSlide);
	}
	IplImage* frame;

	while(1) {
		frame = cvQueryFrame( g_capture );
		if( !frame ) break;
		cvShowImage( "Example2", frame );
		char c = cvWaitKey(25);
		if( c == 27 ) break;
	}
	cvReleaseCapture( &g_capture );
	cvDestroyWindow( "Example2" );
}
