#include "Sound.h"

namespace bb{

Sound::Sound(){
	loaded = false;

	alGenBuffers(1, &id);
}

Sound::~Sound(){
	drop();
}

void Sound::drop(){
	loaded = false;
	id = 0;

	alDeleteBuffers(1, &id);
}

void Sound::load(const std::string &path){
	drop();

	id = alutCreateBufferFromFile(path.c_str());
	loaded = true;
}

bool Sound::good(){
	return loaded;
}

unsigned int Sound::getID(){
	return id;
}

};
