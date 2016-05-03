#include <ctime>
#include <vector>

#include "opencv2/highgui/highgui.hpp"

#include "util/ImgUtil.h"
#include "controller/cStream.h"
#include "util/videoWriter.h"

// to get current directory
#include <string>
#include <limits.h>
#include <unistd.h>
#include <iostream>

// some constants
#define DEMO_1_KEY		49
#define DEMO_2_KEY		50
#define DEMO_3_KEY		51
#define DEMO_4_KEY		52
#define DEMO_5_KEY		53
#define DEMO_SAVE_KEY	115
#define DEMO_ESC_KEY	27
#define NO_ERROR	0

using namespace std;
using namespace cv;

int main( int argc, char** argv ) {
	srand((unsigned int)time(0)); // Seed random

	//Creating cameraStream object
	cStream cs;
	cs.openStream(0);

	//Open window
	cs.setWinName("Xebicon demo");
	cs.openWin();

	IplImage* firstFrame;
	IplImage* secondFrame;

	char selection = DEMO_1_KEY;
	printf("Press from 1..5, ESC to exit\n");

	cs.createResizedBackgroundImage("xebicon.png");

	while(1) {
		cs.captureFrame();
		firstFrame = cvCloneImage(cs.currentFrame());

		cs.captureFrame();
		secondFrame = cvCloneImage(cs.currentFrame());

		char c = cvWaitKey(33);

		// no key pressed?
		if (c != -1) selection = c;

		if( selection == DEMO_1_KEY ) {
			cs.updateWin(secondFrame);
		} else if( selection == DEMO_2_KEY ) {
			cs.paintRectangles(secondFrame);
			cs.updateWin(secondFrame);
		} else if( selection == DEMO_3_KEY ) {
			IplImage* fr = cs.reactToMovement(firstFrame, secondFrame);
			cs.updateWin(fr);
			cvReleaseImage(&fr);
		} else if( selection == DEMO_4_KEY ) {
			IplImage* fr = cs.reactToMovementAndGetDiff(firstFrame, secondFrame);
			cs.updateWin(fr);
			cvReleaseImage(&fr);
		} else if( selection == DEMO_5_KEY ) {
			IplImage* fr = cs.showGrayImage(secondFrame);
			cs.updateWin(fr);
			cvReleaseImage(&fr);
		}

		cvReleaseImage(&firstFrame);
		cvReleaseImage(&secondFrame);

		if( c == DEMO_ESC_KEY ) { break; }
	}
	cs.closeWin();

	// Release memory and destroy window
	//cvReleaseImage(&backgroundImage);
	cvReleaseImage(&firstFrame);
	cvReleaseImage(&secondFrame);

	return NO_ERROR;
}
