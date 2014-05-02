#include "FBO.h"

namespace bb{

FBO::FBO(const std::string &name, const unsigned int target):Buffer(name, target){
	glGenFramebuffers(1, &id);
}

FBO::FBO(const unsigned int target):Buffer("", target){
	glGenFramebuffers(1, &id);
}

FBO::~FBO(){
	glDeleteFramebuffers(1, &id);
}

void FBO::bind(){
	glBindFramebuffer(target, id);
}

void FBO::unbind(){
	glBindFramebuffer(target, 0);
}

void FBO::drawBuffer(const unsigned int mode){
	glDrawBuffer(mode);
}

void FBO::readBuffer(const unsigned int mode){
	glReadBuffer(mode);
}

void FBO::drawBuffers(){
	glDrawBuffers(attachments.size(), &attachments[0]);
}

void FBO::texture(const unsigned int attachment, const unsigned int textureID, const int level){
	attachments.push_back(attachment);

	glFramebufferTexture(target,
						 attachment,
						 textureID,
						 level);

	loaded = true;
}

void FBO::texture1D(const unsigned int attachment, const unsigned int textureID, const int level){
	attachments.push_back(attachment);

	glFramebufferTexture1D(target,
						   attachment,
						   GL_TEXTURE_1D,
						   textureID,
						   level);

	loaded = true;
}

void FBO::texture2D(const unsigned int attachment, const unsigned int textureID, const int level){
	attachments.push_back(attachment);

	glFramebufferTexture2D(target,
						   attachment,
						   GL_TEXTURE_2D,
						   textureID,
						   level);

	loaded = true;
}

void FBO::texture3D(const unsigned int attachment, const unsigned int textureID, const int level, const int layer){
	attachments.push_back(attachment);

	glFramebufferTexture3D(target,
						   attachment,
						   GL_TEXTURE_3D,
						   textureID,
						   level,
						   layer);

	loaded = true;
}

void FBO::attachRBO(const unsigned int attachment, const unsigned int rboTarget, const unsigned int rboID){
	glBindFramebuffer(target, id);
	attachments.push_back(attachment);

	glFramebufferRenderbuffer(target,
							  attachment,
							  rboTarget,
							  rboID);
}

unsigned int FBO::status(){
	return glCheckFramebufferStatus(target);
}

bool FBO::complete(){
	if(status() == GL_FRAMEBUFFER_COMPLETE){
		return true;
	}

	return false;
}

};
