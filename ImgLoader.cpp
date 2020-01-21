#include "ImgLoader.h"

ImgLoader::ImgLoader()
{
	imageInfo = NULL;
}

ImgLoader::~ImgLoader()
{
	Clean();
}

const ImgLoader::ImageInfo* ImgLoader::Load(const char* fileName)
{
	Clean();
	jpeg_decompress_struct info;
	ErrorTracker errorTracker;
	FILE* pFile = NULL;
	fopen_s(&pFile, fileName, "rb");
	if (!pFile)
		return NULL;
	info.err = jpeg_std_error(&errorTracker.defaultMessageError);
	errorTracker.defaultMessageError.error_exit = ErrorExit;
	errorTracker.defaultMessageError.output_message = OuputMessage;
	if(setjmp(errorTracker.jumpBuffer))
	{
		Clean();
		jpeg_destroy_decompress(&info);
		fclose(pFile);
		return NULL;
	}

	jpeg_create_decompress(&info);
	jpeg_stdio_src(&info, pFile);
	jpeg_read_header(&info, TRUE);
	jpeg_start_decompress(&info);

	imageInfo = new ImageInfo();
	imageInfo->Width = info.image_width;
	imageInfo->Height = info.image_height;
	imageInfo->NumComponent = info.num_components;
	imageInfo->Data = new uint8_t[imageInfo->Width * imageInfo->Height * imageInfo->NumComponent];

	while (info.output_scanline < info.image_height)
	{
		uint8_t* dataInfo = imageInfo->Data + info.output_scanline * info.image_width * info.num_components;
		jpeg_read_scanlines(&info, &dataInfo, 1);
	}

	jpeg_finish_decompress(&info);
	jpeg_destroy_decompress(&info);
	fclose(pFile);
	return imageInfo;
}

void ImgLoader::Clean()
{
	if (imageInfo)
	{
		delete[] imageInfo->Data;
		delete imageInfo;
		imageInfo = NULL;
	}
}

void ImgLoader::ErrorExit(j_common_ptr info)
{
	// cinfo->err is actually a pointer to my_error_mgr.defaultErrorManager, since pub
	// is the first element of my_error_mgr we can do a sneaky cast
	ErrorTracker* errorTracker = (ErrorTracker*)info->err;
	(*info->err->output_message)(info); // print error message (actually disabled below)
	longjmp(errorTracker->jumpBuffer, 1);
}


void ImgLoader::OuputMessage(j_common_ptr info)
{
	// disable error messages
	char buffer[JMSG_LENGTH_MAX];
	(*info->err->format_message) (info, buffer);
	fprintf(stderr, "%s\n", buffer);
}
