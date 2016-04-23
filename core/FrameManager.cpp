#include "FrameManager.h"
#include "opencv2/highgui/highgui.hpp"
#include "stdio.h"

IplImage* FrameManager::procImg() {
	return this->processedImg; //Return processed image (colored)
}

IplImage* FrameManager::procImgGray() {
   return this->processedImgGray; //Return processed image (grayscale)
}

//Function to get white pixels in grayscale image area
int FrameManager::getWhiteInArea(int startX, int startY, int w, int h) {
   if (this->processedImgGray == 0) return -1; //If there's no grayscale processed image, return error.

   //Go back to bounds
   if (startX < 0) startX = 0;
   if (startX >= this->processedImgGray->width) return -1;

   if (startY < 0) startY = 0;
   if (startY >= this->processedImgGray->height) return -1;

   //Initialise counter
   int whiteCount = 0;

   //Loop through area
   for (int x = startX; ((x <= startX+w) && (x < this->processedImgGray->width)); x++) {
      for (int y = startY; ((y <= startY+h) && (y < this->processedImgGray->height)); y++) {
		  int tmp = ((uchar*)(this->processedImgGray->imageData + this->processedImgGray->widthStep*y))[x];
		  if (tmp == 255) whiteCount++; //If it's white -> add to whitecount.
	  }
   }

   return whiteCount;
}

void FrameManager::compareImages(IplImage *img1, IplImage *img2) { //Compare two images (frame)
    this->clear(); //Clear everything

	//Check if it's images
	if ((img1 == 0) || (img2 == 0)) { fprintf(stderr, "One/both of images to compare are null\n"); return; }

	//Clone image in order not to modify the original
	this->img1 = cvCloneImage(img1);
	this->img2 = cvCloneImage(img2);

	//Create processed image buffer
	this->processedImg = cvCreateImage(cvGetSize(this->img1), 8, 3);

  //Blur images to get rid of camera noise
	cvSmooth(this->img1, this->img1, CV_BLUR, 3);
	cvSmooth(this->img2, this->img2, CV_BLUR, 3);

	//Calc absolute difference
	cvAbsDiff(this->img1, this->img2, this->processedImg);

	//Create gray image buffer
	this->processedImgGray = cvCreateImage(cvGetSize(this->processedImg), 8, 1);

    //Convert colored image to grayscale
	cvCvtColor(this->processedImg, this->processedImgGray, CV_RGB2GRAY);

	//Perform binary treshold filter on image to leave only white and black pixels
	cvThreshold(this->processedImgGray, this->processedImgGray, 30, 255, CV_THRESH_BINARY);

	//char *nombre = "archivo2.png";
	//cvSaveImage(nombre, this->processedImgGray);
}

void FrameManager::clear() { //Clear everything (prepare for reuse)
   cvReleaseImage(&this->img1);
   cvReleaseImage(&this->img2);
   cvReleaseImage(&this->processedImg);
   cvReleaseImage(&this->processedImgGray);

   this->img1 = 0;
   this->img2 = 0;
   this->processedImg = 0;
   this->processedImgGray = 0;
}

bool FrameManager::movementDetected(CvRect area) {
	int amount = this->getWhiteInArea(area.x, area.y, area.width, area.height);
	return amount >= 100;
}

FrameManager::FrameManager(void) {
  this->img1 = 0;
   this->img2 = 0;
   this->processedImg = 0;
   this->processedImgGray = 0;
}

FrameManager::~FrameManager(void) {
	this->clear();
}
