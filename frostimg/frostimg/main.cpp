#include "frostimg.h"
#include <iostream>
#include <string>

void drawTest(frostimg &img) {
	img.setPixel(1, 1, 247, 72, 154);
	img.setPixel(0, 0, 255, 0, 0);
	img.setPixel(2, 2, 0, 255, 0);
	img.setPixel(0, 2, 0, 0, 255);
	img.setPixel(2, 0, 255, 255, 255);
	img.setPixel(1, 0, 255, 255, 0);
	img.setPixel(0, 1, 0, 255, 255);
	img.setPixel(2, 1, 255, 0, 255);
}

int main() {
	frostbmpimg image(3,3,0,0,0);
	drawTest(image);
	image.writeFile("test");
	/*
	std::array<char, 4> temp = image.getPixel(1, 1);
	std::cout << std::to_string(static_cast<unsigned char>(temp[0])) << ',' << std::to_string(static_cast<unsigned char>(temp[1])) << ',' << std::to_string(static_cast<unsigned char>(temp[2])) << std::endl;
	*/
	return 0;
}