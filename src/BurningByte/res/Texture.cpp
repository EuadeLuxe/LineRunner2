#include "Texture.h"

namespace bb{

Texture::Texture(unsigned int target){
    this->target = target;
	id = 0;
	bitsPerPixel = 0;
	bytesPerPixel = 0;
	size[0] = 0;
	size[1] = 0;
	size[2] = 0;
    activeTexture = 0;
    loaded = false;
}

Texture::~Texture(){
    drop();
}

void Texture::drop(){
	if(loaded){
		unbind();
		glDeleteBuffers(1, &id);
		data.clear();

		size[0] = 0;
		size[1] = 0;
		size[2] = 0;

		loaded = false;
	}
}

bool Texture::good(){
	return loaded;
}

void Texture::generateID(){
	drop();
	glGenTextures(1, &id);
}

void Texture::texture1D(const int level, const int internalFormat, const unsigned int width, const int border, const unsigned int format, const unsigned int type, const void* data){
	drop();

	size[0] = width;

	glGenTextures(1, &id);
	glBindTexture(target, id);

	glTexImage1D(target,
				 level,
				 internalFormat,
				 GLsizei(size[0]),
				 border,
				 format,
				 type,
				 data);

	loaded = true;
}

void Texture::texture2D(const int level, const int internalFormat, const unsigned int width, const unsigned int height, const int border, const unsigned int format, const unsigned int type, const void* data){
	drop();

	size[0] = width;
	size[1] = height;

	glGenTextures(1, &id);
	glBindTexture(target, id);

	glTexImage2D(target,
				 level,
				 internalFormat,
				 GLsizei(size[0]),
				 GLsizei(size[1]),
				 border,
				 format,
				 type,
				 data);

	loaded = true;
}

void Texture::texture3D(const int level, const int internalFormat, const unsigned int width, const unsigned int height, const unsigned int depth, const int border, const unsigned int format, const unsigned int type, const void* data){
	drop();

	size[0] = width;
	size[1] = height;
	size[2] = depth;

	glGenTextures(1, &id);
	glBindTexture(target, id);

	glTexImage3D(target,
				 level,
				 internalFormat,
				 GLsizei(size[0]),
				 GLsizei(size[1]),
				 GLsizei(size[2]),
				 border,
				 format,
				 type,
				 data);

	loaded = true;
}

bool Texture::loadTGA(const std::string &path, const bool saveImgData, const TEXFILTER filter){
	drop();
	
	tgaFile tga(path, filter);
	
	if(!tga.good()){
		return false;
	}

	size[0] = tga.width();
	size[1] = tga.height();
	bitsPerPixel = tga.getBitsPerPixel();
	bytesPerPixel = tga.getBytesPerPixel();

	if(saveImgData){
		data.resize(tga.width()*tga.height()*tga.getBytesPerPixel());
		copy(tga.getImageData(), tga.getImageData()+data.size(), data.begin());
	}

	// Buffer kopieren
	glGenTextures(1, &id);
	glBindTexture(target, id);
	
	if(filter == LINEAR){
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else{
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT); // default
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if(tga.getBitsPerPixel() == 24){
		glTexImage2D(target,
					 0,
					 GL_RGB8,
					 tga.width(),
					 tga.height(),
					 0,
					 GL_RGB,
					 GL_UNSIGNED_BYTE,
					 tga.getImageData());
	}
	else{
		glTexImage2D(target,
					 0,
					 GL_RGBA,
					 tga.width(),
					 tga.height(),
					 0,
					 GL_RGBA,
					 GL_UNSIGNED_BYTE,
					 tga.getImageData());
	}
	
	loaded = true;

	return true;
}

void Texture::parameterf(const unsigned int pname, const float param){
	glTexParameterf(target, pname, param);
}

void Texture::parameteri(const unsigned int pname, const int param){
	glTexParameteri(target, pname, param);
}

void Texture::bind(unsigned int activeTexture){
    this->activeTexture = activeTexture;

    glActiveTexture(activeTexture);
    glBindTexture(target, id);
}

void Texture::unbind(){
    glActiveTexture(activeTexture);
    glBindTexture(target, 0);
}

unsigned int Texture::getTarget(){
    return target;
}

unsigned int Texture::getID(){
	return id;
}

unsigned int Texture::width(){
	return size[0];
}

unsigned int Texture::height(){
	return size[1];
}

unsigned int Texture::depth(){
	return size[2];
}

unsigned int Texture::getBitsPerPixel(){
	return bitsPerPixel;
}

unsigned int Texture::getBytesPerPixel(){
	return bytesPerPixel;
}

};
