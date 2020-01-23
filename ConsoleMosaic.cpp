// ConsoleMosaic.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "ImgLoader.h"

int main()
{
    std::cout << "Wesh Morray\n";
	ImgLoader* img = new ImgLoader();
    const int widthImg = static_cast<int>(img->Load("dems.jpg")->Width);
    const int heightImg = static_cast<int>(img->Load("dems.jpg")->Height);
    const int nbCompImg = static_cast<int>(img->Load("dems.jpg")->NumComponent);
	int* pixels = nullptr;
	pixels = static_cast<int*>(malloc((sizeof(int) * nbCompImg) * widthImg * heightImg));
	for(int i = 0; i < widthImg * heightImg * nbCompImg; i++)
	{
		pixels[i] = static_cast<int>(img->Load("dems.jpg")->Data[i]);
	}

	//ImageWriter::ImageWriter();
	
	std::cout << "Bam!";
	std::cout << pixels;
	free(pixels);
}
