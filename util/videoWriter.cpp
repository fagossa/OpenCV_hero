#include "videoWriter.h"

//Return width and height functions
int videoWriter::getWidth() {
   return this->width;
}

int videoWriter::getHeight() {
   return this->height;
}

//Check if writer is open
bool videoWriter::isOpen() {
   return this->writerOpen;
}
//Create new videowriter (but not open it)
videoWriter::videoWriter(char * fileName, int width, int height, int fps) {
	this->writer = 0;
	this->fileName = fileName;
	this->fps = fps;
	this->width = width;
	this->height = height;

	this->writerOpen = false;
}

//Return filename.
char * videoWriter::getFileName() {
   return this->fileName;
}

//Change output filename (only when writer is not open)
int videoWriter::changeFileName(char * newFileName) {
   if (this->writerOpen == true) return WRITER_ERROR_WRITER_OPEN;
   else
   {
      this->fileName = newFileName;
	  return WRITER_OK;
   }
}

//Write image to output
int videoWriter::imageToWriter(IplImage * frame) {
	if (!this->writerOpen) return WRITER_ERROR_WRITER_NOT_OPEN;
	if (frame == 0) {
	   return WRITER_ERROR_NO_FRAME;
	}

	cvWriteFrame(this->writer,frame);

	return WRITER_OK;
}

//Open writer to write
void videoWriter::openWriter() {
   if (this->writerOpen) return;
   this->writer = cvCreateVideoWriter(
      this->fileName,
		  -1,
		  this->fps,
		  cvSize(this->getWidth(),this->getHeight()),
		  1
	  );

   this->writerOpen = true;
}

//Close writer.
void videoWriter::closeWriter() {
   if (!this->writerOpen) return;
   cvReleaseVideoWriter(&this->writer);
   this->writerOpen = false;
}

videoWriter::~videoWriter(void) {
   this->closeWriter();
}
