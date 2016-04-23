#pragma once
//#include <opencv2/cv.h>
#include "opencv2/highgui/highgui.hpp"
#include "ImgUtil.h"

IplImage* ImgUtil::doPtrDown(IplImage* in, int filter) {
	IplImage* out = cvCreateImage(
		cvSize(in->width/2, in->height/2),
		in->depth,
		in->nChannels
	);
	cvPyrDown(in, out);
	return out;
}

IplImage* ImgUtil::doSmoothing(IplImage* in) {
	IplImage* out = cvCreateImage(
		cvGetSize(in),
		IPL_DEPTH_8U,
		3
	);
	cvSmooth(in, out, CV_GAUSSIAN, 3, 3);
	return out;
}

/**
 *
 */
int ImgUtil::generateRandomNumber(int lowest, int highest) {
	int range = (highest-lowest) + 1;
	return lowest + int(range*rand()/(RAND_MAX + 1.0));
}
