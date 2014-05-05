#include "Background.h"

Background::Background(const float speed, const float x){
	this->speed = speed;
	this->x = x;
}

void Background::update(const float deltaTime){
	for(auto entity : entities){
		auto position = std::static_pointer_cast<bb::Position2D>(entity->getComponent("Position"));

		if(position){
			position->position.x -= speed*deltaTime;

			if(position->position.x < -(x-10.0f)){ // 5px overlapping
				position->position.x = x;
			}
		}
	}
}
