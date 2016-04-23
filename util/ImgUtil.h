#pragma once

#include "opencv2/highgui/highgui.hpp"

class ImgUtil {
private:

public:
	static IplImage* doPtrDown(IplImage* in, int filter=CV_GAUSSIAN_5x5);

	static IplImage* doSmoothing(IplImage* in);

	static int generateRandomNumber(int lowest, int highest);
};
