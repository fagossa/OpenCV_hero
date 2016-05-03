#pragma once
#include "opencv2/highgui/highgui.hpp"

#define TYPE_LEFT_SYMBOL		0
#define TYPE_CENTERED_SYMBOL	1
#define TYPE_RIGHT_SYMBOL		2
#define MOVEMENT_X_AXIS		2
#define MOVEMENT_Y_AXIS		10
#define OCV_HERO_DEFAULT_HEIGHT	20
#define OCV_HERO_DEFAULT_WIDTH	20
#define OCV_HERO_GREEN_COLOR	CV_RGB(0, 255, 0)
#define OCV_HERO_DARK_GREEN_COLOR	CV_RGB(0, 100, 0)
#define OCV_HERO_RED_COLOR		CV_RGB(255, 0, 0)
#define OCV_HERO_YELLOW_COLOR	CV_RGB(255, 255, 0)
#define OCV_HERO_WHITE_COLOR	CV_RGB(255, 255, 255)

class Symbol {
private:
	CvRect *rectangle;
  CvScalar avgColor(IplImage *frame, int startX, int startY, int w, int h);
  int alphaReductionAfterMouvement;
  int alpha;
  int mouvementThreshold;

public:
	void draw(IplImage* frame);
	int countWhiteInArea(IplImage *processedImgGray);
	void reactToMovement(int whitePixels, IplImage *frame);

	Symbol(int posx, int posy, int width, int height);
	~Symbol(void);
};
