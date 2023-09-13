#pragma once
#include<vector>
class Image
{
public:
	//int* colors;
	//unsigned char* pic;
	//int color_num;

	std::vector<unsigned char> image;
	unsigned int width,height,depth;
	int get_color(int k);
	Image(const char* str);
};