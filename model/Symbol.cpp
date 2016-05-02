//#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "Symbol.h"

Symbol::Symbol(int posx, int posy, int width, int height) {
	rectangle = new CvRect();
	this->rectangle->x = posx;
	this->rectangle->y = posy;
	this->rectangle->width = width;
	this->rectangle->height = height;
  this->alpha = 0;
}

/**
 * destruye la instancia de la clase
 */
Symbol::~Symbol(void) {}

/*
 * Draws the symbol in the frame specified
 */
void Symbol::draw(IplImage* frame) {
	CvScalar color = avgColor(frame, 
	                          this->rectangle->x, 
	                          this->rectangle->y,
	                          this->rectangle->width, 
	                          this->rectangle->height);
	cvRectangle(frame,
             cvPoint(this->rectangle->x, this->rectangle->y),
             cvPoint(this->rectangle->x + this->rectangle->width, this->rectangle->y + this->rectangle->height),
             color, CV_FILLED, 8, 0);
}

/*
 * Gets average color in the specified area
 */
CvScalar Symbol::avgColor(IplImage *frame, int startX, int startY, int w, int h) {
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

/*
 * Get the amt of white in a binay image
 */
int Symbol::countWhiteInArea(IplImage *processedImgGray) {
	int startX = this->rectangle->x;
	int startY=this->rectangle->y;
	int w = this->rectangle->width;
	int h = this->rectangle->height;
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

/*
 * Shows a graphic representation of mouvement
 */
void Symbol::showMovement(IplImage *frame) {
	CvScalar color = CV_RGB(255, 242, 0);
	cvRectangle(
            frame,
            cvPoint(this->rectangle->x, this->rectangle->y),
            cvPoint(this->rectangle->x + this->rectangle->width, this->rectangle->y + this->rectangle->height),
            color, CV_FILLED, 8, 0
            );
}

