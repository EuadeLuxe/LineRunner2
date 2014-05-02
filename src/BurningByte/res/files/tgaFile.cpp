#include "tgaFile.h"

namespace bb{

tgaFile::tgaFile(const std::string &path, const TEXFILTER filter){
	imgWidth = 0;
	imgHeight = 0;
	bitsPerPixel = 0;
	bytesPerPixel = 0;
	textureID = 0;
	loaded = false;

	if(!load(path)){
		std::cerr<<"Texture could not be loaded ("<<path<<")!"<<std::endl;
	}
	else{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		if(filter == LINEAR){
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		else{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if(bitsPerPixel == 24){
			glTexImage2D(GL_TEXTURE_2D,
						 0,
						 GL_RGB8,
						 imgWidth,
						 imgHeight,
						 0,
						 GL_RGB,
						 GL_UNSIGNED_BYTE,
						 &imageData[0]);
		}
		else{
			glTexImage2D(GL_TEXTURE_2D,
						 0,
						 GL_RGBA,
						 imgWidth,
						 imgHeight,
						 0,
						 GL_RGBA,
						 GL_UNSIGNED_BYTE,
						 &imageData[0]);
		}

		loaded = true;
	}
}

tgaFile::tgaFile(){
	imgWidth = 0;
	imgHeight = 0;
	bitsPerPixel = 0;
	bytesPerPixel = 0;
	textureID = 0;
	loaded = false;
}

tgaFile::~tgaFile(){
	drop();
}

bool tgaFile::loadCompressedTarga(std::istream &file){
    unsigned int pixelcount	= imgHeight*imgWidth;
    unsigned int currentpixel = 0;   
    unsigned int currentbyte = 0;   

    std::vector<unsigned char> colorBuffer(bytesPerPixel);

    do{
        unsigned char chunkheader = 0;
        file.read(reinterpret_cast<char*>(&chunkheader), sizeof(unsigned char));
    
        if(chunkheader < 128){
            chunkheader++;

            for(short counter = 0; counter < chunkheader; counter++){
                file.read(reinterpret_cast<char*>(&colorBuffer[0]), bytesPerPixel);

                imageData[currentbyte] = colorBuffer[2];
                imageData[currentbyte+1] = colorBuffer[1];
                imageData[currentbyte+2] = colorBuffer[0];

                if(bytesPerPixel == 4){
                    imageData[currentbyte+3] = colorBuffer[3];
                }
                 
                currentbyte += bytesPerPixel;
                currentpixel++;

                if(currentpixel > pixelcount){
                    return false;
                }
            }
        } 
        else{
            chunkheader -= 127;

            file.read(reinterpret_cast<char*>(&colorBuffer[0]), bytesPerPixel);

            for(short counter = 0; counter < chunkheader; counter++){
                imageData[currentbyte] = colorBuffer[2];
                imageData[currentbyte+1] = colorBuffer[1];
                imageData[currentbyte+2] = colorBuffer[0];

                if(bytesPerPixel == 4){
                    imageData[currentbyte+3] = colorBuffer[3];
                }

                currentbyte += bytesPerPixel;
                currentpixel++;

                if(currentpixel > pixelcount){
                    return false;
                }
            }
        }
    }while(currentpixel < pixelcount);

    return true;
}

bool tgaFile::loadUncompressedTarga(std::istream &file){
    unsigned int imageSize = imageData.size();
    file.read(reinterpret_cast<char*>(&imageData[0]), imageSize);
		
    for(unsigned int swap = 0; swap < imageSize; swap += bytesPerPixel){
        char cswap = imageData[swap];
        imageData[swap] = imageData[swap+2];
        imageData[swap+2] = cswap;
    }

    return true;
}

void tgaFile::flipImageVertically(){
	std::vector<unsigned char> flippedData;
    flippedData.reserve(imageData.size());
	int step = bytesPerPixel; // 3 = RGB, 4 = RGBA

    for(int row = imgHeight-1; row >= 0; row--){
        unsigned char *rowData = &imageData[row*imgWidth*step];

        for(unsigned int i = 0; i < imgWidth*step; i++){
            flippedData.push_back(*rowData);
            rowData++;
        }
    }

    imageData.assign(flippedData.begin(), flippedData.end());
}

void tgaFile::drop(){
	imageData.clear();
	glDeleteTextures(1, &textureID);
	loaded = false;
}

bool tgaFile::isImageTypeSupported(const tgaHeader &header){
	return (header.imageTypeCode == TFT_RGB && header.imageTypeCode == TFT_RLE_RGB) || (header.colorMapType == 0);
}

bool tgaFile::isUncompressedTarga(const tgaHeader &header){
	return (header.imageTypeCode == TFT_RGB || header.imageTypeCode == TFT_GRAYSCALE);
}

bool tgaFile::load(const std::string &path){
	drop();

	std::ifstream file(path.c_str(), std::ios::binary);

    if(!file.good()){
        return false;
    }

    // Header
    file.read(reinterpret_cast<char*>(&header), sizeof(tgaHeader));

    if(!isImageTypeSupported(header)){
        return false;
    }

    imgWidth = header.width;
    imgHeight = header.height;
    bitsPerPixel = header.bpp;
    bytesPerPixel = header.bpp/8;

    if(bytesPerPixel < 3){ // RGB = 3, RGBA = 4
        return false;
    }

    imageData.resize(imgWidth*imgHeight*bytesPerPixel);

    if(header.idLength > 0){
        file.ignore(header.idLength);
    }

    loaded = false;

    if(isUncompressedTarga(header)){
    	loaded = loadUncompressedTarga(file);
    }
    else{
    	loaded = loadCompressedTarga(file);
    }

    if((header.imageDesc & TOP_LEFT) == TOP_LEFT) {
        flipImageVertically();
    }

    return loaded;
}

bool tgaFile::good(){
	return loaded;
}

unsigned int tgaFile::width(){
	return imgWidth;
}

unsigned int tgaFile::height(){
	return imgHeight;
}

unsigned int tgaFile::getBitsPerPixel(){
	return bitsPerPixel;
}

unsigned int tgaFile::getBytesPerPixel(){
	return bytesPerPixel;
}

unsigned int tgaFile::getTextureID(){
	return textureID;
}

unsigned char* tgaFile::getImageData(){
	if(imageData.size()){
		return &imageData[0];
	}
	
	return 0;
}

};
