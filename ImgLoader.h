#ifndef IMG_LOADER_H
#define IMG_LOADER_H
	#include <stdio.h>
	#include <jpeglib.h>
	#include <setjmp.h>
	#include <stdint.h>

	class ImgLoader
	{
	public:
		struct ImageInfo
		{
			uint32_t Width;
			uint32_t Height;
			uint8_t NumComponent;
			uint8_t* Data;
		};
		ImgLoader();
		~ImgLoader();

		const ImageInfo* Load(const char* fileName);

	private:
		ImageInfo* imageInfo;
		void Clean();

		struct ErrorTracker
		{
			jpeg_error_mgr defaultMessageError;
			jmp_buf jumpBuffer;
		};
		static void ErrorExit(j_common_ptr eInfo);
		static void OuputMessage(j_common_ptr ioInfo);
	};
#endif
