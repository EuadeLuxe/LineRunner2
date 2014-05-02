/*
 * FBO - FrameBufferObject
 * Author: Marvin Blum
 * Last Update: 2014/03/21 16:18
 * */

#ifndef FBO_H_
#define FBO_H_

#include <vector>
#include "Buffer.h"

namespace bb{

class FBO:public Buffer{
	protected:
		std::vector<unsigned int> attachments;

    public:
        FBO(const std::string &name, const unsigned int target = GL_FRAMEBUFFER);
        FBO(const unsigned int target = GL_FRAMEBUFFER);
        virtual ~FBO();

        void bind();
        void unbind();

        void drawBuffer(const unsigned int mode);
        void readBuffer(const unsigned int mode);
        void drawBuffers();

        void texture(const unsigned int attachment, const unsigned int textureID, const int level);
        void texture1D(const unsigned int attachment, const unsigned int textureID, const int level);
        void texture2D(const unsigned int attachment, const unsigned int textureID, const int level);
        void texture3D(const unsigned int attachment, const unsigned int textureID, const int level, const int layer);
        void attachRBO(const unsigned int attachment, const unsigned int rboTarget, const unsigned int rboID);

        unsigned int status();
        bool complete();
};

};

#endif
