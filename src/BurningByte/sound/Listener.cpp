#include "Listener.h"

namespace bb{

Listener::Listener(const vec3 &position, const vec3 &velocity, const vec3 &orientation){
	this->position = position;
	this->velocity = velocity;
	this->orientation = orientation;
	up = vec3(0.0f, 0.0f, 1.0f);
	gain = 1.0f;

	set();
}

Listener::Listener(const vec3 &position){
	this->position = position;
	velocity = vec3();
	orientation = vec3();
	up = vec3(0.0f, 0.0f, 1.0f);
	gain = 1.0f;

	set();
}

void Listener::set(){
	float orient[] = {orientation.x, orientation.y, orientation.z, up.x, up.y, up.z};

	alListener3f(AL_POSITION, position.x, position.y, position.z);
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	alListenerfv(AL_ORIENTATION, orient);
	alListenerf(AL_GAIN, gain);
}

void Listener::setPosition(const vec3 &position){
	this->position = position;
	alListener3f(AL_POSITION, position.x, position.y, position.z);
}

void Listener::setVelocity(const vec3 &velocity){
	this->velocity = velocity;
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}

void Listener::setOrientation(const vec3 &orientation){
	this->orientation = orientation;
	float orient[] = {orientation.x, orientation.y, orientation.z, up.x, up.y, up.z};

	alListenerfv(AL_ORIENTATION, orient);
}

void Listener::setUp(const vec3 &up){
	this->up = up;
	float orient[] = {orientation.x, orientation.y, orientation.z, up.x, up.y, up.z};

	alListenerfv(AL_ORIENTATION, orient);
}

void Listener::setGain(float gain){
	this->gain = gain;
	alListenerf(AL_GAIN, gain);
}

};
