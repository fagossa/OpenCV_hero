#include "opencv2/highgui/highgui.hpp"
#include "cStream.h"

using namespace std;

cStream::cStream(void) {
 this->capture = 0;
 this->windowName = 0;
 this->windowIsOpen = false;
 this->mouvementThreshold = 20;
}

cStream::~cStream(void) {
  cvReleaseCapture(&this->capture);
  cvReleaseImage(&this->frame);
  cvReleaseImage(&this->backgroundImage);
  this->data.clear();
}

//Return capture width
int cStream::getWidth() {
 if (this->capture == 0) return -1;
 return int(cvGetCaptureProperty(this->capture, CV_CAP_PROP_FRAME_WIDTH));
}

//Return capture height
int cStream::getHeight() {
 if (this->capture == 0) return -1;
 return int(cvGetCaptureProperty(this->capture, CV_CAP_PROP_FRAME_HEIGHT));
}

//Return current frame
IplImage * cStream::currentFrame() {
 return this->frame;
}

//Open window
void cStream::openWin() {
  if (this->windowIsOpen) return;
  //If window name hasn't been set, set it to default
  if (this->windowName == 0) 
    this->setWinName(DEFAULT_WINDOW_NAME);

  cvNamedWindow(this->windowName, CV_WINDOW_AUTOSIZE); //open window
  this->windowIsOpen = true;
}

//Close window
 void cStream::closeWin() {
  if (this->windowIsOpen) {
    cvDestroyWindow(this->windowName);
    this->windowIsOpen = false;
  }
}

//Set window name
void cStream::setWinName(char * wName) {
 if (this->windowIsOpen) this->closeWin();
 this->windowName = wName;
 this->windowIsOpen = false;
}

// Reads a file from disk and resize it to capture size
void cStream::createResizedBackgroundImage(char * fileName) {
  IplImage* imageFromDisk = cvLoadImage(fileName);
  //cvSaveImage("outFileName_1.png", imageFromDisk);
  IplImage* newImg = cvCreateImage(cvSize(this->getWidth(), this->getHeight()), imageFromDisk->depth, imageFromDisk->nChannels);
  cvResize(imageFromDisk, newImg);
  this->backgroundImage = newImg;
}

//Update window with new image
void cStream::updateWin(IplImage * frame) {
 if (this->windowIsOpen) {
  if (frame == 0) cvShowImage(this->windowName, this->frame);
  else cvShowImage(this->windowName, frame);
 } else {
    fprintf(stderr, "Could not update window, because window is not open\n"); //Error
 }
}

// Gets a new frame
 void cStream::captureFrame() {
	if (this->capture == 0) { fprintf(stderr, "Capture is null\n"); return; } //Error

	this->frame = cvQueryFrame(this->capture); //Get frame
	cvFlip(this->frame, NULL, 1);

	if (data.size()==0) {
		this->initRectangles(this->frame);
	}
}

//A shortcut to stream image to window only (with no frame modifications)
void cStream::streamToWindow(char * winName) {
	if (this->capture == 0) this->openStream();
	if (this->capture != 0) {
    this->setWinName(winName);
    this->openWin();

    while (true) {
     this->captureFrame();
     this->updateWin();

		 // Break on escape key press.
     if ((cvWaitKey(1) & 255) == 27) break;
   }
   this->closeWin();
 }
}

//Open camera capture stream defalt streamId = 0
void cStream::openStream(int streamId) {
	this->capture = cvCreateCameraCapture(streamId);
	int frames = (int) cvGetCaptureProperty(
                                          this->capture,
                                          CV_CAP_PROP_FRAME_COUNT
                                          );
	if (this->capture == 0) {
    fprintf(stderr, "Could not open capture stream\n");
    return;
  }
}

// divides screen into squares of equal size
void cStream::initRectangles(IplImage* frame) {
	int posx = 0;
	int posy = 0;
	int temp = 0;
	int width = frame->width/WIDTH_CELL_AMT + 1;
	int height = frame->height/HEIGHT_CELL_AMT + 1;
	for (int i=0 ; i<HEIGHT_CELL_AMT; i++) {
		for (int j=0 ; j<WIDTH_CELL_AMT ; j++) {

      Symbol symbol (posx, posy, width, height);
      data.push_back(symbol);

			posx += width;
			temp++;
		}
		posx = 0;
		posy += height;
	}
}

// shows restangles of the AVG color in the occupied region
void cStream::paintRectangles(IplImage* frame) {
	for (unsigned int i=0 ; i<data.size() ; i++) {
    data[i].draw(frame);
	}
}

// get image as grey level
IplImage* cStream::showGrayImage(IplImage *secondFrame) {
	IplImage* processedImgGray = cvCreateImage(cvGetSize(secondFrame), 8, 1);
	cvCvtColor(secondFrame, processedImgGray, CV_RGB2GRAY);
	return processedImgGray;
}

// show mouvement sampling
IplImage* cStream::reactToMovement(IplImage *firstFrame, IplImage *secondFrame) {
	IplImage* diff = getBinaryDiff(firstFrame, secondFrame);
  IplImage* newImage = cvCloneImage(this->backgroundImage);
	for (unsigned int i=0 ; i<data.size() ; i++) {
		int whitePixels = data[i].countWhiteInArea(diff);
		if (whitePixels > mouvementThreshold) {
      data[i].reactToMovement(newImage);
		}
	}
	return newImage;
}

// show mouvement sampling
IplImage* cStream::reactToMovementAndGetDiff(IplImage *firstFrame, IplImage *secondFrame) {
  IplImage* diff = getBinaryDiff(firstFrame, secondFrame);
  for (unsigned int i=0 ; i<data.size() ; i++) {
    int whitePixels = data[i].countWhiteInArea(diff);
    if (whitePixels > mouvementThreshold) {
      data[i].reactToMovement(secondFrame);
    }
  }
  return diff;
}

// get the binary diff between two images
IplImage* cStream::getBinaryDiff(IplImage *firstFrame, IplImage *secondFrame) {
	IplImage* img1 = cvCloneImage(firstFrame);
	IplImage* img2 = cvCloneImage(secondFrame);

	if ((firstFrame == 0) || (secondFrame == 0)) { fprintf(stderr, "One/both of images to compare are null\n"); return NULL; }

	//create processed image buffer
	IplImage* processedImg = cvCreateImage(cvGetSize(img1), 8, 3);

  //blur images to get rid of camera noise
	cvSmooth(img1, img1, CV_BLUR, 3);
	cvSmooth(img2, img2, CV_BLUR, 3);

	//calc absolute difference
	cvAbsDiff(img1, img2, processedImg);

	//create gray image buffer
	IplImage* processedImgGray = cvCreateImage(cvGetSize(processedImg), 8, 1);

  //convert colored image to grayscale
	cvCvtColor(processedImg, processedImgGray, CV_RGB2GRAY);

	//perform binary treshold filter on image to leave only white and black pixels
	cvThreshold(processedImgGray, processedImgGray, 30, 255, CV_THRESH_BINARY);

	cvReleaseImage(&img1);
  cvReleaseImage(&img2);
  cvReleaseImage(&processedImg);

  return processedImgGray;
}

