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

	vector <Symbol> data;
	void initRectangles(IplImage* frame);
	IplImage* getBinaryDiff(IplImage *firstFrame, IplImage *secondFrame);

	IplImage* backgroundImage;

public:

	// handle frame capture
	IplImage * frame;
	void openStream(int streamId = DEFAULT_STREAM_ID);
	void getFrame();
	void captureFrame();
	IplImage * currentFrame(void);
	void streamToWindow(char * wName);

	// handle size
	int getWidth();
  int getHeight();

  // handle window
	void setWinName(char * wName);
	void openWin(void);
	void closeWin(void);
	void updateWin(IplImage * frame = 0);

	// related to motion capture
	void createResizedBackgroundImage(char * fileName);
	void paintRectangles(IplImage* frame);
	IplImage* reactToMovement(IplImage *firstFrame, IplImage *secondFrame);
	IplImage* reactToMovementAndGetDiff(IplImage *firstFrame, IplImage *secondFrame);
	
	// related to image transformations
	IplImage* showGrayImage(IplImage *frame);

	cStream(void);
	~cStream(void);
};
