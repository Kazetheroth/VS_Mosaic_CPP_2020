#ifndef IMG_LOADER_H
#define IMG_LOADER_H
	#include <stdio.h>
	#include <jpeglib.h>
	#include <setjmp.h>
	#include <stdint.h>

class ImgWriter
{
public:
	ImgWriter();

	void Write(const char* fileName, const int compression, const int width, const int height);

private:
	JSAMPLE* imageBuffer;
	
};

#endif