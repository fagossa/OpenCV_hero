#pragma once

#include "cv.h"
#include "highgui.h"

/**
 *
 */
class ImgUtil {
private:

public:
	static IplImage* doPtrDown(IplImage* in, int filter=IPL_GAUSSIAN_5x5);

	static IplImage* doSmoothing(IplImage* in);
	
	static int generateRandomNumber(int lowest, int highest);
};
