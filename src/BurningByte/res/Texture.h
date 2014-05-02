/*
 * Texture
 * Author: Marvin Blum
 * Last Update: 2014/03/20 00:09
 * */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <vector>
#include <string>
#include <GL/gl3w.h>
#include "../Component.h"
#include "files/tgaFile.h"

namespace bb{

class Texture:public Component{
	private:
		unsigned int size[3]; // width, height, depth
		unsigned int target, activeTexture, id, bitsPerPixel, bytesPerPixel;

        bool loaded;

	public:
        std::vector<unsigned char> data;

		Texture(unsigned int target);
		virtual ~Texture();

		void drop();
        bool good();

        void generateID();
        void texture1D(const int level, const int internalFormat, const unsigned int width, const int border, const unsigned int format, const unsigned int type, const void* data = NULL);
        void texture2D(const int level, const int internalFormat, const unsigned int width, const unsigned int height, const int border, const unsigned int format, const unsigned int type, const void* data = NULL);
        void texture3D(const int level, const int internalFormat, const unsigned int width, const unsigned int height, const unsigned int depth, const int border, const unsigned int format, const unsigned int type, const void* data = NULL);

        bool loadTGA(const std::string &path, const bool saveImgData = false, const TEXFILTER filter = LINEAR);

		void parameterf(const unsigned int pname, const float param);
		void parameteri(const unsigned int pname, const int param);

        void bind(unsigned int activeTexture = GL_TEXTURE0);
        void unbind();
        
        unsigned int getTarget();
        unsigned int getID();
		unsigned int width();
		unsigned int height();
		unsigned int depth();
		unsigned int getBitsPerPixel();
		unsigned int getBytesPerPixel();
};

};

#endif
