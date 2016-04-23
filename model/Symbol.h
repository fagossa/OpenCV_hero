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

/**
 * Clase encargada de representar los s&iacute;mbolos en movimiento
 * @author Fabian Gutierrez
 */
class Symbol {
private:
	CvPoint *pos;
	int width;
	int height;
	int type;
	bool valid;
public:
	bool hitted;
	bool started;
	int startIteration;
	void move(void);
	void draw(IplImage* in);
	bool inside(CvRect areaToCheck);
	Symbol(int type);
	~Symbol(void);
};
