#include "Animation.h"

Animation::Animation(const float speed){
	this->speed = speed;
	interpolation = 0.0f;
	currentSet = 0;
}

void Animation::add(const std::string &name, const std::shared_ptr<Set> set){
	sets.insert(std::make_pair(name, set));

	if(!currentSet){
		currentSet = sets[name];
	}
}

void Animation::set(const std::string &name){
	if(sets.find(name) != sets.end()){
		currentSet = sets[name];
		interpolation = 0.0f;
	}
}

void Animation::update(const float deltaTime){
	if(!currentSet){
		return;
	}

	interpolation += speed*deltaTime;

	if(interpolation >= 1.0f){
		interpolation = 0.0f;
		currentSet->next();
	}
}

std::shared_ptr<Animation::Set> Animation::current(){
	return currentSet;
}

Animation::Keyframe::Keyframe(const bb::vec2 &scale, const bb::vec2 &offset){
	this->scale = scale;
	this->offset = offset;
}

Animation::Set::Set(const bool loop){
	this->loop = loop;
	currentFrame = 0;
}

void Animation::Set::add(const std::shared_ptr<Keyframe> frame){
	frames.push_back(frame);
}

void Animation::Set::set(const unsigned int i){
	if(i < frames.size()){
		currentFrame = i;
	}
}

void Animation::Set::next(){
	currentFrame++;

	if(currentFrame == frames.size()){
		if(loop){
			currentFrame = 0;
		}
		else{
			currentFrame--;
		}
	}
}

std::shared_ptr<Animation::Keyframe> Animation::Set::current(){
	if(frames.size()){
		return frames[currentFrame];
	}

	return 0;
}
