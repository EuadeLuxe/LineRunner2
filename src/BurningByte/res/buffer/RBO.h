/*
 * RBO - RenderBufferObject
 * Author: Marvin Blum
 * Last Update: 2014/03/29 16:52
 * */

#ifndef RBO_H_
#define RBO_H_

#include "Buffer.h"

namespace bb{

class RBO:public Buffer{
	public:
		RBO(const std::string &name, const unsigned int target = GL_RENDERBUFFER);
		virtual ~RBO();

		void drop();

		bool storage(const unsigned int format, const unsigned int width, const unsigned int height, const unsigned int samples = 0);
};

};

#endif
