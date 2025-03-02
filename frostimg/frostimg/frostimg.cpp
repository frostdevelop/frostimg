// frostimg.cpp : Defines the entry point for the application.
//

#include "frostimg.h"
#include "datatool.h"
#include <iostream>
#include <stdint.h>

frostbmpimg::frostbmpimg(uint_fast32_t width = 0, uint_fast32_t height = 0, char dr = 0, char dg = 0, char db = 0)
{
	header.type[0] = 'B';
	header.type[1] = 'M';
	infoheader.rowpad = (4 * ceil(float(width * 3) / 4.0)) - width * 3;
	header.offset = 54;
	header.reserved1 = 0;
	header.reserved2 = 0;
	header.size = 54+height*(width*3+infoheader.rowpad);
	infoheader.compression = 0;
	infoheader.size = 40;
	infoheader.width = width;
	infoheader.height = height;
	raster = new char[width * height][3];
	infoheader.planes = 1;
	infoheader.bitc = 24;
	infoheader.xperm = uint_fast32_t(2834);
	infoheader.yperm = uint_fast32_t(2834);
	for (uint_fast32_t i = 0;i < width * height;i++) { raster[i][0] = db;raster[i][1] = dg;raster[i][2] = dr; }
}

void frostbmpimg::writeFile(std::string name)
{
	std::ofstream wfile(name + ".bmp");
	wfile.write(header.type, 2);
	wfile.write(dtt::ufast322byte(header.size,true).data(), 4);
	wfile.write(dtt::ufast162byte(header.reserved1, true).data(), 2);
	wfile.write(dtt::ufast162byte(header.reserved2, true).data(), 2);
	wfile.write(dtt::ufast322byte(header.offset, true).data(), 4);
	/*
	char* gap = new char[header.offset];
	wfile.write(gap, header.offset);
	delete[] gap;
	*/
	//const uint_fast16_t dibsize = 40;
	wfile.write(dtt::ufast322byte(infoheader.size, true).data(), 4);
	wfile.write(dtt::ufast322byte(infoheader.width, true).data(), 4);
	wfile.write(dtt::ufast322byte(infoheader.height, true).data(), 4);
	wfile.write(dtt::ufast162byte(infoheader.planes, true).data(), 2);
	wfile.write(dtt::ufast162byte(infoheader.bitc, true).data(), 2);
	wfile.write(dtt::ufast322byte(infoheader.compression, true).data(), 4);
	//Add compression in future update :)
	wfile.write(dtt::ufast322byte(uint_fast32_t(0), true).data(), 4); //ImageSize
	//std::array<char, 4> defresa = dtt::ufast322byte(uint_fast32_t(2834));
	wfile.write(dtt::ufast322byte(infoheader.xperm, true).data(), 4); //XPPM
	wfile.write(dtt::ufast322byte(infoheader.yperm, true).data(), 4); //YPPM
	wfile.write(dtt::ufast322byte(uint_fast32_t(0), true).data(), 4); //Colors Used
	wfile.write(dtt::ufast322byte(uint_fast32_t(0), true).data(), 4); //Important
	char czro = 0;
	for (uint_fast32_t y = 0; y < infoheader.height;y++) {
		for (uint_fast32_t x = 0;x < infoheader.width;x++) {
			uint_fast32_t post = (y * infoheader.width) + x;
			switch (infoheader.bitc) {
			case 24:
				wfile.write(&raster[post][0], 1);
				wfile.write(&raster[post][1], 1);
				wfile.write(&raster[post][2], 1);
				std::cout << std::to_string(static_cast<unsigned char>(raster[post][2])) + ',' + std::to_string(static_cast<unsigned char>(raster[post][1])) + ',' + std::to_string(static_cast<unsigned char>(raster[post][0])) << std::endl;
				break;
			case 16:
				wfile.write(&raster[post][0],1);
				wfile.write(&raster[post][1],1);
				break;
			}
		}
		for (uint_fast8_t i = 0;i < infoheader.rowpad;i++) { wfile.write(&czro,1); }
		std::cout << (4 * ceil(float(infoheader.width*3) / 4.0)) - infoheader.width*3 << std::endl;
		//wfile.write(0, (4 * ceil(float(infoheader.width) / 4.0)) - infoheader.width);
	}
	wfile.close();
}

frost::databuf frostbmpimg::writeBuf()
{
	frost::databuf buffer;
	buffer.data = new unsigned char[header.size];
	buffer.size = header.size;
	return buffer;
}

frostbmpimg::~frostbmpimg() {
	delete[] raster;
}

std::array<char, 4> frostbmpimg::getPixel(uint_fast32_t x, uint_fast32_t y)
{
	uint_fast32_t pos = (((infoheader.height-y-1) * infoheader.width) + x); //(infoheader.width*infoheader.height) - ((y * infoheader.width) + x) - 1
	switch (infoheader.bitc) {
	case 24:
		return std::array<char, 4>({ raster[pos][2], raster[pos][1], raster[pos][0], 0});
		break;
	case 16:
		return std::array<char, 4>({raster[pos][1] >> 2, (raster[pos][0] >> 5) | ((raster[pos][1] << 3) & 0x03), raster[pos][0] & 0x1f, 0});
		break;
	}
	return std::array<char, 4>();
}

bool frostbmpimg::setPixel(uint_fast32_t x, uint_fast32_t y, char r, char g, char b)
{
	uint_fast32_t pos = (((infoheader.height - y - 1) * infoheader.width) + x);
	switch (infoheader.bitc) {
	case 24:
		raster[pos][0] = b;
		raster[pos][1] = g;
		raster[pos][2] = r;
		break;
	case 16:
		raster[pos][0] = (b & 0x1f) | (g << 5);
		raster[pos][1] = ((g >> 3) & 0x03) | ((r << 2) & 0x7c);
		break;
	default:
		return false;
	}
	return true;
}

void frostbmpimg::setSize(uint_fast32_t width, uint_fast32_t height)
{
	infoheader.width = width;
	infoheader.height = height;
	delete[] raster;
	raster = new char[width * height][3];
	infoheader.rowpad = (4 * ceil(float(width * 3) / 4.0)) - width * 3;
	header.size = 54 + height * (width * 3 + infoheader.rowpad);
}

frostbmpimg frostbmpimg::from(std::string name)
{
	std::ifstream rfile(name + ".bmp");
	frostbmpimg outimg;
	if (!rfile.is_open()) { return frostbmpimg(); } //1
	size_t filesize = rfile.tellg();
	rfile.seekg(0, std::ios::end);
	filesize = static_cast<size_t>(rfile.tellg()) - filesize;
	char tempbuf2[2];
	rfile.read(tempbuf2, 2);
	if (tempbuf2[0] != 'B' && tempbuf2[1] != 'M') { return frostbmpimg(); } //2
	char tempbuf4[4];
	rfile.read(tempbuf4, 4);
	uint_fast32_t filesized = dtt::byte2ufast32(tempbuf4, true);
	if (filesized != filesize) { std::cout << "Warning: BMP File has file size mismatch." << std::endl; }
	rfile.read(tempbuf4, 4); //reserved
	return outimg;
}

/*
int frostbmpimg::readFrom(std::string name)
{
	return 0;
}
*/

void frostimg::writeFile(std::string name)
{
}

frost::databuf frostimg::writeBuf()
{
	return frost::databuf();
}

std::array<char, 4> frostimg::getPixel(uint_fast32_t x, uint_fast32_t y)
{
	return std::array<char, 4>();
}

bool frostimg::setPixel(uint_fast32_t x, uint_fast32_t y, char r, char g, char b)
{
	return false;
}

void frostimg::setSize(uint_fast32_t width, uint_fast32_t height)
{
}

frostimg frostimg::from(std::string name)
{
	return frostimg();
}
