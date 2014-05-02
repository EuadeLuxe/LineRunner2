#include "ShadowMapping.h"

namespace bb{

ShadowMapping::ShadowMapping(const unsigned int width, const unsigned int height, const std::string &name):FBO(name, GL_FRAMEBUFFER){
	setSize(width, height);
}

void ShadowMapping::setSize(const unsigned int width, const unsigned int height){
	bind();

	shadowMap = std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D));
	shadowMap->bind();
	shadowMap->texture2D(0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	shadowMap->parameterf(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	shadowMap->parameterf(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	shadowMap->parameterf(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	shadowMap->parameterf(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	shadowMap->unbind();

	texture2D(GL_DEPTH_ATTACHMENT, shadowMap->getID(), 0);
	drawBuffer(GL_NONE);
	readBuffer(GL_NONE);

	unbind();
}

};
