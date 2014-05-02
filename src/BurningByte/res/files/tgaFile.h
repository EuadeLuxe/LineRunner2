/*
 * tgaFile
 * Author: Marvin Blum
 * Last Update: 31/12/2013 16:29
 * */

#ifndef TGAFILE_H_
#define TGAFILE_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <GL/gl3w.h>

namespace bb{

enum TEXFILTER{ // OpenGL texture filter
	LINEAR,
	NEAREST
};

class tgaFile{
	private:
		struct tgaHeader{
			unsigned char idLength;
			unsigned char colorMapType;
			unsigned char imageTypeCode;
			unsigned char colorMapSpec[5];
			unsigned short xOrigin;
			unsigned short yOrigin;
			unsigned short width;
			unsigned short height;
			unsigned char bpp;
			unsigned char imageDesc;
		};

		enum TargaFileTypes{
			TFT_NO_DATA = 0,
			TFT_INDEXED = 1,
			TFT_RGB = 2,
			TFT_GRAYSCALE = 3,
			TFT_RLE_INDEXED = 9,
			TFT_RLE_RGB = 10,
			TFT_RLE_GRAYSCALE = 11
		};

		enum IMAGE_ORIENTATIONS{
			BOTTOM_LEFT = 0x00,
			BOTTOM_RIGHT = 0x10,
			TOP_LEFT = 0x20,
			TOP_RIGHT = 0x30
		};

		tgaHeader header;
		std::vector<unsigned char> imageData;

		unsigned int imgWidth, imgHeight, bitsPerPixel, bytesPerPixel, textureID;
		bool loaded;

		bool loadUncompressedTarga(std::istream &file);
		bool loadCompressedTarga(std::istream &file);
		void flipImageVertically();

		bool isImageTypeSupported(const tgaHeader &header);
		bool isUncompressedTarga(const tgaHeader &header);

	public:
		tgaFile(const std::string &path, const TEXFILTER filter = LINEAR);
		tgaFile();
		virtual ~tgaFile();

		void drop();

		bool load(const std::string &path);
		bool good();

		unsigned int width();
		unsigned int height();
		unsigned int getBitsPerPixel();
		unsigned int getBytesPerPixel();
		unsigned int getTextureID();
		unsigned char* getImageData();
};

};

#endif
