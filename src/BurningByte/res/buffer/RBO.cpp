#include "RBO.h"

namespace bb{

RBO::RBO(const std::string &name, const unsigned int target):Buffer(name, target){
	glGenRenderbuffers(1, &id);
}

RBO::~RBO(){
	drop();
}

void RBO::drop(){
	loaded = false;

	glDeleteRenderbuffers(1, &id);
}

bool RBO::storage(const unsigned int format, const unsigned int width, const unsigned int height, const unsigned int samples){
	if(samples < GL_MAX_SAMPLES){
		bind();
		glRenderbufferStorageMultisample(target, samples, format, width, height);
		unbind();

		loaded = true;

		return true;
	}

	return false;
}

};
