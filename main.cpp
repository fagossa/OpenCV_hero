#include <ctime>
#include <vector>

//#include <cv.h>
#include "opencv2/highgui/highgui.hpp"

#include "core/FrameManager.h"
#include "util/ImgUtil.h"
#include "util/cStream.h"
#include "util/videoWriter.h"

#define DEMO_1_KEY		49
#define DEMO_2_KEY		50
#define DEMO_3_KEY		51
#define DEMO_4_KEY		52
#define DEMO_5_KEY		53
#define DEMO_SAVE_KEY	115
#define DEMO_ESC_KEY	27

using namespace std;

int main( int argc, char** argv ) {
	srand((unsigned int)time(0)); // Seed random

	// inicio del juego
	bool started = true;
	// fin de inicio

	FrameManager fmngr;

	//Creating cameraStream object
	cStream cs;
	cs.openStream(0);

	int fps = 15;
	videoWriter vidWr("video.avi", cs.getWidth(), cs.getHeight(), fps);

	//Open window
	cs.setWinName("Video Test");
	cs.openWin();

  IplImage* firstFrame;
	IplImage* secondFrame;

	char lastOption = DEMO_1_KEY;
	while(1) {
		cs.captureFrame();
		firstFrame = cvCloneImage(cs.currentFrame());

		cs.captureFrame();
		secondFrame = cvCloneImage(cs.currentFrame());

		char c = cvWaitKey(33);

		// no presiono tecla?
		if (c==-1) {
			if( lastOption == DEMO_1_KEY ) {
				cs.updateWin(secondFrame);
			} else if( lastOption == DEMO_2_KEY ) {
				cs.paintRectangles(secondFrame);
				cs.updateWin(secondFrame);
			} else if( lastOption == DEMO_3_KEY ) {
				cs.showMovement(firstFrame, secondFrame);
				cs.updateWin(secondFrame);
			} else if( lastOption == DEMO_4_KEY ) {
				IplImage* fr = cs.showMovement(firstFrame, secondFrame);
				cs.updateWin(fr);
				cvReleaseImage(&fr);
			} else if( lastOption == DEMO_5_KEY ) {
				IplImage* fr = cs.showGrayImage(secondFrame);
				cs.updateWin(fr);
				cvReleaseImage(&fr);
			}
		} else {
			lastOption = c;
			if( c == DEMO_SAVE_KEY ) {
				if (!vidWr.isOpen()) {
					printf("Starting video output\n");
					vidWr.openWriter();
				} else {
					printf("Stopping video output\n");
					vidWr.closeWriter();
				}
			}
		}

		//cs.updateWin(secondFrame);
		int response = vidWr.imageToWriter(secondFrame);

		cvReleaseImage(&firstFrame);
		cvReleaseImage(&secondFrame);

		if( c == DEMO_ESC_KEY ) { break; }
    }
	cs.closeWin();

	// Release memory and destroy window
	cvReleaseImage(&firstFrame);
	cvReleaseImage(&secondFrame);

    return(0);
}
