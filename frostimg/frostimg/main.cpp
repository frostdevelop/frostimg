#include "frostimg.h"
#include <iostream>
#include <string>
#include <array>

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
	/*
	frostbmpimg image(3,3,0,0,0);
	drawTest(image);
	image.writeFile("test.bmp");
	*/
	frostbmpimg rimg = frostbmpimg("tester.bmp"); //* //larger than 32x is rpetty strange
	std::cout << rimg.getWidth() << ',' << rimg.getHeight() << std::endl;
	/*
	std::array<char, 4> color = rimg->getPixel(0, 0);
	std::cout << color[0] << ',' << color[1] << ',' << color[2] << std::endl;
	*/
	//rimg->setPixel(1, 2, 0, 255, 187);
	//rimg->setPixel(0, 0, 0, 255, 167);
	drawTest(rimg);
	/*
	for (size_t y = 0;y < rimg->getHeight();y++) {
		for (size_t x = 0;x < rimg->getWidth();x++) {
			std::array<char, 4> color = rimg->getPixel(x, y);
			std::cout << std::to_string(static_cast<unsigned char>(color[0])) + ',' + std::to_string(static_cast<unsigned char>(color[1])) + ',' + std::to_string(static_cast<unsigned char>(color[2])) << std::endl;
		}
	}
	*/
	rimg.writeFile("test2.bmp");
	//delete rimg;
	/*
	std::array<char, 4> temp = image.getPixel(1, 1);
	std::cout << std::to_string(static_cast<unsigned char>(temp[0])) << ',' << std::to_string(static_cast<unsigned char>(temp[1])) << ',' << std::to_string(static_cast<unsigned char>(temp[2])) << std::endl;
	*/
	return 0;
}