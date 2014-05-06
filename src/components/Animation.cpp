#include "Animation.h"

Animation::Animation(const float speed, const bool loop){
	this->speed = speed;
	this->loop = loop;
	interpolation = 0.0f;
	currentFrame = 0;
}

void Animation::add(const std::shared_ptr<Keyframe> keyframe){
	frames.push_back(keyframe);
}

void Animation::setCurrent(const unsigned int i){
	if(i < frames.size()){
		currentFrame = i;
	}
}

void Animation::update(const float deltaTime){
	interpolation += speed*deltaTime;

	if(interpolation >= 1.0f){
		interpolation = 0.0f;
		currentFrame++;

		if(currentFrame >= frames.size()){
			if(loop){
				currentFrame = 0;
			}
			else{
				currentFrame--; // stay at last frame
			}
		}
	}
}

std::shared_ptr<Animation::Keyframe> Animation::current(){
	if(!frames.size()){
		return 0;
	}

	return frames[currentFrame];
}

Animation::Keyframe::Keyframe(const bb::vec2 &scale, const bb::vec2 &offset){
	this->scale = scale;
	this->offset = offset;
}
