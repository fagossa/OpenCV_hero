#pragma once
#include "opencv2/highgui/highgui.hpp"

/**
 *
 */
class FrameManager {
private:
   IplImage * img1;
   IplImage * img2;

   IplImage * processedImg;
   IplImage * processedImgGray;

public:
	IplImage * procImg(void);
	IplImage * procImgGray(void);

  void clear(void);

	void compareImages(IplImage * img1, IplImage * img2);

  int getWhiteInArea(int startX, int startY, int w, int h);

	bool movementDetected(CvRect area);

	FrameManager(void);
	~FrameManager(void);
};
