#pragma once

#include <vector>

#include "opencv2/highgui/highgui.hpp"

#include "../model/Symbol.h"

#define DEFAULT_STREAM_ID 0
#define DEFAULT_WINDOW_NAME "Webcam window"
#define DEFAULT_WRITER_FILENAME "video.avi"

using namespace std;

class cStream {
	char * windowName;
	bool windowIsOpen;

  CvCapture * capture;
	static const int WIDTH_CELL_AMT = 40;
	static const int HEIGHT_CELL_AMT = 30;

	int mouvementThreshold;

	vector <Symbol> data;
	void initRectangles(IplImage* frame);
	IplImage* getBinaryDiff(IplImage *firstFrame, IplImage *secondFrame);

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

	void paintRectangles(IplImage* frame);
	IplImage* showMovement(IplImage *firstFrame, IplImage *secondFrame);
	IplImage* showGrayImage(IplImage *frame);

	cStream(void);
	~cStream(void);
};
