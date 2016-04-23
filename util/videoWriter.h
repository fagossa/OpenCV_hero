#pragma once
#define DEFAULT_FILENAME "video.avi"
#define DEFAULT_FPS 25
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

#define WRITER_ERROR_WRITER_OPEN -3
#define WRITER_ERROR_WRITER_NOT_OPEN -2
#define WRITER_ERROR_NO_FRAME -1
#define WRITER_OK 0

#include "opencv2/highgui/highgui.hpp"

class videoWriter {
   char * fileName;
   CvVideoWriter *writer;
   bool writerOpen;

   int fps;
   int width;
   int height;


public:
	videoWriter(char * fileName = DEFAULT_FILENAME, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, int fps = DEFAULT_FPS);

	void openWriter();

	int imageToWriter(IplImage * frame);

	int changeFileName(char * newFileName);

	char * getFileName();

	bool isOpen();

	int getWidth();

	int getHeight();

	void closeWriter(void);

	~videoWriter(void);
};
