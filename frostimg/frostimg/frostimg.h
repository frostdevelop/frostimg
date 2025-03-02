// frostimg.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <stdint.h>

#ifndef FRCORE
#define FRCORE
namespace frost {
	struct databuf {
		unsigned char* data;
		size_t size;
	};
}
#endif // !FRCORE

namespace frimg {
	struct bmpHeader {
		char type[2];
		uint_fast16_t reserved1;
		uint_fast16_t reserved2;
		uint_fast32_t size;
		uint_fast32_t offset;
	};
	struct infoHeader {
		uint_fast32_t size;
		uint_fast32_t width;
		uint_fast32_t height;
		uint_fast32_t planes;
		uint_fast16_t bitc;
		uint_fast32_t compression;
		uint_fast32_t xperm;
		uint_fast32_t yperm;
		uint_fast32_t colorsused;
		uint_fast32_t colorsimportant;
		uint_fast8_t rowpad;
	};
}

class frostimg {
public:
	virtual void writeFile(std::string name);
	virtual frost::databuf writeBuf();
	virtual std::array<char, 4> getPixel(uint_fast32_t x, uint_fast32_t y);
	virtual bool setPixel(uint_fast32_t x, uint_fast32_t y, char r, char g, char b);
	virtual void setSize(uint_fast32_t width, uint_fast32_t height);
	static frostimg from(std::string name);
};

class frostbmpimg : public frostimg {
public:
	frostbmpimg(uint_fast32_t width, uint_fast32_t height, char dr, char dg, char db);
	~frostbmpimg();
	virtual void writeFile(std::string name);
	virtual frost::databuf writeBuf();
	virtual std::array<char, 4> getPixel(uint_fast32_t x, uint_fast32_t y);
	virtual bool setPixel(uint_fast32_t x, uint_fast32_t y, char r, char g, char b);
	virtual void setSize(uint_fast32_t width, uint_fast32_t height);
	static frostbmpimg from(std::string name);
	//int readFrom(std::string name);
protected:
	frimg::bmpHeader header;
	frimg::infoHeader infoheader;
	char (*raster)[3];
};

/*
class frostpalettebmpimg : public frostbmpimg {
public:

private:
	std::vector<std::array<char, 4>> palette;
};
*/