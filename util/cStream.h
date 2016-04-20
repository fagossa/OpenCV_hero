#pragma once

#include <vector>

#include "cv.h"
#include "highgui.h"

#define DEFAULT_STREAM_ID 0
#define DEFAULT_WINDOW_NAME "Webcam window"
#define DEFAULT_WRITER_FILENAME "video.avi"

using namespace std;

class cStream {
	char * windowName;
	bool windowIsOpen;
  CvCapture * capture;
	static const int WIDTH_CELL_AMT = 40;//80
	static const int HEIGHT_CELL_AMT =	30;//60

	//fabian
	vector <CvRect> data;
	void initRectangles(IplImage* frame);
	CvScalar avgColor(IplImage *frame, int startX, int startY, int w, int h);
	IplImage* getBinaryDiff(IplImage *firstFrame, IplImage *secondFrame);
	int countWhiteInArea(IplImage *frame, int startX, int startY, int w, int h);

public:

	IplImage * frame;
	void openStream(int streamId = DEFAULT_STREAM_ID);
	void getFrame();

	int getWidth();
  int getHeight();

	void setWinName(char * wName);
	void openWin(void);
	void closeWin(void);
	void updateWin(IplImage * frame = 0);

	void captureFrame();

	IplImage * currentFrame(void);
	void streamToWindow(char * wName);
	//fabian
	void paintRectangles(IplImage* frame);
	IplImage* showMovement(IplImage *firstFrame, IplImage *secondFrame);
	IplImage* showGrayImage(IplImage *frame);

	cStream(void);
	~cStream(void);
};
