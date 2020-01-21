// ConsoleMosaic.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <array>
#include "ImgLoader.h"

int main()
{
    std::cout << "Wesh Morray\n";
	ImgLoader* img = new ImgLoader();
	int widthImg = (int)img->Load("dems.jpg")->Width;
	int heightImg = (int)img->Load("dems.jpg")->Height;
	int nbCompImg = (int)img->Load("dems.jpg")->NumComponent;
	int* pixels = NULL;
	pixels = (int*) malloc((sizeof(int) * nbCompImg) * widthImg * heightImg);
	for(int i = 0; i < widthImg * heightImg * nbCompImg; i++)
	{
		pixels[i] = (int)img->Load("dems.jpg")->Data[i];
	}
	
	std::cout << "Bam!";
	std::cout << pixels;
	free(pixels);
}
