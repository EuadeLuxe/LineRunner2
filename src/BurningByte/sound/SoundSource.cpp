#include "SoundSource.h"

namespace bb{

SoundSource::SoundSource(const std::shared_ptr<Sound> &sound, const vec3 &position, const bool loop){
	this->sound = sound;

	alGenSources(1, &id);
	alSourcei(id, AL_BUFFER, sound->getID());

	setPosition(position);
	setLoop(loop);
}

SoundSource::~SoundSource(){
	alDeleteSources(1, &id);
}

void SoundSource::play(){
	alSourcePlay(id);
}

void SoundSource::pause(){
	alSourcePause(id);
}

void SoundSource::rewind(){
	alSourceRewind(id);
}

void SoundSource::stop(){
	alSourceStop(id);
}

void SoundSource::setSound(const std::shared_ptr<Sound> &sound){
	alSourcei(id, AL_BUFFER, sound->getID());
}

void SoundSource::setPosition(const vec3 &position){
	alSource3f(id, AL_DIRECTION, position.x, position.y, position.z);
}

void SoundSource::setVelocity(const vec3 &velocity){
	alSource3f(id, AL_DIRECTION, velocity.x, velocity.y, velocity.z);
}

void SoundSource::setDirection(const vec3 &direction){
	alSource3f(id, AL_DIRECTION, direction.x, direction.y, direction.z);
}

void SoundSource::setGain(const float gain){
	alSourcef(id, AL_GAIN, gain);
}

void SoundSource::setPitch(const float pitch){
	alSourcef(id, AL_PITCH, pitch);
}

void SoundSource::setRange(const float range){
	alSourcef(id, AL_MAX_DISTANCE, range);
}

void SoundSource::setLoop(const bool loop){
	alSourcei(id, AL_LOOPING, loop);
}

void SoundSource::set(const unsigned int param, const float value){
	alSourcef(id, param, value);
}

void SoundSource::set(const unsigned int param, const float v0, const float v1, const float v2){
	alSource3f(id, param, v0, v1, v2);
}

void SoundSource::set(const unsigned int param, const float* value){
	alSourcefv(id, param, value);
}

void SoundSource::set(const unsigned int param, const int value){
	alSourcei(id, param, value);
}

void SoundSource::set(const unsigned int param, const int v0, const int v1, const int v2){
	alSource3i(id, param, v0, v1, v2);
}

void SoundSource::set(const unsigned int param, const int* value){
	alSourceiv(id, param, value);
}

float SoundSource::getf(const unsigned int param){
	float f;
	alGetSourcef(id, param, &f);

	return f;
}

vec3 SoundSource::get3f(const unsigned int param){
	vec3 v;
	alGetSource3f(id, param, &v.x, &v.y, &v.z);

	return v;
}

float* SoundSource::getfv(const unsigned int param){
	float* f = 0;
	alGetSourcefv(id, param, f);

	return f;
}

int SoundSource::geti(const unsigned int param){
	int i;
	alGetSourcei(id, param, &i);

	return i;
}

SoundSource::int3 SoundSource::get3i(const unsigned int param){
	int3 v;
	alGetSource3i(id, param, &v.x, &v.y, &v.z);

	return v;
}

int* SoundSource::getiv(const unsigned int param){
	int* i = 0;
	alGetSourceiv(id, param, i);

	return i;
}

unsigned int SoundSource::getID(){
	return id;
}

int SoundSource::status(){
	int state;
	alGetSourcei(id, AL_SOURCE_STATE, &state);

	return state;
}

};
