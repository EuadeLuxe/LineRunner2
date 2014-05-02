/*
 * DeferredShading
 * Author: Marvin Blum
 * Last Update: 2014/05/01 13:58
 * */

#ifndef DEFERREDSHADING_H_
#define DEFERREDSHADING_H_

#include <memory>
#include "../../res/buffer/FBO.h"
#include "../../res/Texture.h"

namespace bb{

class DeferredShading:public FBO{
	public:
		std::shared_ptr<Texture> position, diffuse, normal, depth;

		DeferredShading(const unsigned int width, const unsigned int height, const std::string &name = "");

		void setSize(const unsigned int width, const unsigned int height);
};

};

#endif
