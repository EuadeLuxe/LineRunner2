#include "Buffer.h"

namespace bb{

Buffer::Buffer(const std::string &name, const unsigned int target){
	this->name = name;
	id = 0;
	this->target = target;
	this->loaded = false;
}

Buffer::~Buffer(){
	glDeleteBuffers(1, &id);
}

void Buffer::drop(){
	glDeleteBuffers(1, &id);

	id = 0;
	target = 0;
	loaded = false;
}

void Buffer::bind(){
	glBindBuffer(target, id);
}

void Buffer::unbind(){
	glBindBuffer(target, 0);
}

bool Buffer::good(){
	return loaded;
}

unsigned int Buffer::getID(){
	return id;
}

unsigned int Buffer::getType(){
	return target;
}

};
