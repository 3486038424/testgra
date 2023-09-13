#include "Image.h"
#pragma once
#include <iostream>
#include <fstream>
#include<windows.h>
#include "lodepng.h"


Image::Image(const char* str) {
	std::vector<unsigned char> img;
	unsigned error = lodepng::decode(img, width, height, str, LCT_RGB, 8);
	len = img.size()/3;
	image=(int*)malloc(len * 4);
	for (int i = 0; i < len; i++)
		image[i] = RGB(img[i*3+2],img[i*3+1],img[i*3]);
	if (error) {
		std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
		return;
	}
}


int Image::get_color(int k) { if (k > len || k < 0)return RGB(255, 255, 255); return image[k]; }


/*
unsigned int buffer2int(unsigned char* buffer, int& index, int depth = 4)
{
	int i = 0;
	for (int j = 0; j < depth; j++, index++)
	{
		i = i * 256 + (int)(buffer[index]);
	}
	return i;
}
bool compare(unsigned char* buffer, int index, unsigned char* c, int beg,int len)
{
	index += beg;
	for (int i = 0; i < len; i++, index++,beg++)
	{
		//std::cout << std::hex << int(buffer[index]) << ' ' << int(c[beg]) << '\n';
		if (int(buffer[index]) != int(c[beg]))return false;
	}
	return true;
}

Image::Image() {
	std::ifstream infile("E:\\t.png", std::ios::binary);

	if (!infile) { return; }

	infile.seekg(0, infile.end);
	int length = infile.tellg();
	infile.seekg(0, infile.beg);
	unsigned char* buffer = new unsigned char[length];

	infile.read((char*)buffer, length);

	infile.close();

	int index = 0;
	int file_type = buffer2int(buffer, index);
	for (int i = 0; i < 3; i++) buffer2int(buffer, index);
	width = buffer2int(buffer, index), height = buffer2int(buffer, index);
	depth = (int)(buffer[index]);
	colors = new int[1 << depth];
	pic = new unsigned char[width * height];
	index += 9;
	unsigned char c1[] = { 0,0,128,0,'I','D','A','T' };
	color_num = 0;
	for (int i = 0; 1; i++)
	{
		if (compare(buffer, index, c1, 4,4))break;
		colors[i] = buffer2int(buffer, index, 3);
		color_num++;
	}
	unsigned char c2[] = {0,0,0,0,'I','E','N','D',174,'B',96,130};
	while (1)
	{
		if (compare(buffer, index, c2, 0, 12))break;
		int d = buffer2int(buffer, index);
		index += 4;
		int i = 0;
		for (int j = 0; j < d; i++, index++, j++)
		{
			pic[i] = buffer[index];
		}
		index += 4;
		std::cout << std::hex << index << '\n';
	}
	delete buffer;
}
*/