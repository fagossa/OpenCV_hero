#include "opencv2/highgui/highgui.hpp"
#include "cStream.h"

using namespace std;

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

cStream::cStream(void) {
 this->capture = 0;
 this->windowName = 0;
 this->windowIsOpen = false;
}

cStream::~cStream(void) {
  cvReleaseCapture(&this->capture);
  cvReleaseImage(&this->frame);
  this->data.clear();
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
			CvRect rectangle;
			rectangle.x = posx;
			rectangle.y = posy;
			rectangle.width = width;
			rectangle.height = height;
			posx += width;
			data.push_back(rectangle);
			temp++;
		}
		posx = 0;
		posy += height;
	}
}

// shows restangles of the AVG color in the occupied region
void cStream::paintRectangles(IplImage* frame) {
	for (unsigned int i=0 ; i<data.size() ; i++) {
		CvScalar color = avgColor(frame, data[i].x, data[i].y, data[i].width, data[i].height);

		cvRectangle(frame,
               cvPoint(data[i].x, data[i].y),
               cvPoint(data[i].x + data[i].width, data[i].y + data[i].height),
               color, CV_FILLED, 8, 0);
	}
}

// get average color in the specified area
CvScalar cStream::avgColor(IplImage *frame, int startX, int startY, int w, int h) {
 CvScalar color = CV_RGB(0, 0, 0);
   //Go back to bounds
 if (startX < 0) startX = 0;
 if (startX >= frame->width) return color;

 if (startY < 0) startY = 0;
 if (startY >= frame->height) return color;

   //initialise counter
 int sumR = 0, sumG = 0, sumB = 0, counter = 0;

   //loop through area
 for (int x = startX; ((x <= startX+w) && (x < frame->width)); x++) {
  for (int y = startY; ((y <= startY+h) && (y < frame->height)); y++) {
    int blue = ((uchar*)(frame->imageData + frame->widthStep*y))[x * 3];
    int green = ((uchar*)(frame->imageData + frame->widthStep*y))[x * 3 + 1];
    int red = ((uchar*)(frame->imageData + frame->widthStep*y))[x * 3 + 2];

    sumR += red;
    sumG += green;
    sumB += blue;
    counter++;
  }
}
color.val[0] = sumB/counter;
color.val[1] = sumG/counter;
color.val[2] = sumR/counter;
color.val[3] = 4;
return color;
}

// get image as grey level
IplImage* cStream::showGrayImage(IplImage *secondFrame) {
	IplImage* processedImgGray = cvCreateImage(cvGetSize(secondFrame), 8, 1);
	cvCvtColor(secondFrame, processedImgGray, CV_RGB2GRAY);
	return processedImgGray;
}

// show mouvement sampling
IplImage* cStream::showMovement(IplImage *firstFrame, IplImage *secondFrame) {
	CvScalar color = CV_RGB(255, 242, 0);
	IplImage* diff = getBinaryDiff(firstFrame, secondFrame);
	for (unsigned int i=0 ; i<data.size() ; i++) {
		int whitePixels = countWhiteInArea(diff, data[i].x, data[i].y, data[i].width, data[i].height);
		if (whitePixels > mouvementThreshold) {
			cvRectangle(
                  secondFrame,
                  cvPoint(data[i].x, data[i].y),
                  cvPoint(data[i].x + data[i].width, data[i].y + data[i].height),
                  color, CV_FILLED, 8, 0
                  );
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

// get the amt of white in a binay image
int cStream::countWhiteInArea(IplImage *processedImgGray, int startX, int startY, int w, int h) {
   if (processedImgGray == 0) return -1; //If there's no grayscale processed image, return error.

   //Go back to bounds
   if (startX < 0) startX = 0;
   if (startX >= processedImgGray->width) return -1;

   if (startY < 0) startY = 0;
   if (startY >= processedImgGray->height) return -1;

   //Initialise counter
   int whiteCount = 0;

   //Loop through area
   for (int x = startX; ((x <= startX+w) && (x < processedImgGray->width)); x++) {
    for (int y = startY; ((y <= startY+h) && (y < processedImgGray->height)); y++) {
      int tmp = ((uchar*)(processedImgGray->imageData + processedImgGray->widthStep*y))[x];
		  if (tmp == 255) whiteCount++; //If it's white -> add to whitecount.
   }
 }

 return whiteCount;
}
