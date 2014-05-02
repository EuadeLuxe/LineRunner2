#include "DeferredShading.h"

namespace bb{

DeferredShading::DeferredShading(const unsigned int width, const unsigned int height, const std::string &name):FBO(name, GL_FRAMEBUFFER){
	setSize(width, height);
}

void DeferredShading::setSize(const unsigned int width, const unsigned int height){
	bind();

	// attach color attachments
	position = std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D));
	position->bind();
	position->texture2D(0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, 0);
	position->parameterf(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	position->parameterf(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	position->parameterf(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	position->parameterf(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	position->unbind();

	diffuse = std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D));
	diffuse->bind();
	diffuse->texture2D(0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, 0);
	diffuse->parameterf(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	diffuse->parameterf(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	diffuse->parameterf(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	diffuse->parameterf(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	diffuse->unbind();

	normal = std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D));
	normal->bind();
	normal->texture2D(0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, 0);
	normal->parameterf(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	normal->parameterf(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	normal->parameterf(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	normal->parameterf(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	normal->unbind();

	texture2D(GL_COLOR_ATTACHMENT0, position->getID(), 0);
	texture2D(GL_COLOR_ATTACHMENT0+1, diffuse->getID(), 0);
	texture2D(GL_COLOR_ATTACHMENT0+2, normal->getID(), 0);

	drawBuffers(); // activate attachments for drawing

	// attach depth attachment
	depth = std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D));
	depth->bind();
	depth->texture2D(0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	depth->parameterf(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	depth->parameterf(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	depth->parameterf(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	depth->parameterf(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	depth->unbind();

	texture2D(GL_DEPTH_ATTACHMENT, depth->getID(), 0);
	unbind();
}

};
