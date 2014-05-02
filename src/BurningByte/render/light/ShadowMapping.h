/*
 * ShadowMapping
 * Author: Marvin Blum
 * Last Update: 2014/05/01 13:58
 * */

#ifndef SHADOWMAPPING_H_
#define SHADOWMAPPING_H_

#include <memory>
#include "../../res/buffer/FBO.h"
#include "../../res/Texture.h"

namespace bb{

class ShadowMapping:public FBO{
	public:
		std::shared_ptr<Texture> shadowMap;

		ShadowMapping(const unsigned int width, const unsigned int height, const std::string &name = "");

		void setSize(const unsigned int width, const unsigned int height);
};

};

#endif
