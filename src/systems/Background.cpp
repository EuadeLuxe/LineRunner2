#include "Background.h"

Background::Background(const float speed, const float cloudSpeed, const float x){
	this->speed = speed;
	this->cloudSpeed = cloudSpeed;
	this->x = x;
}

void Background::update(const float deltaTime){
	for(auto entity : entities){
		auto position = std::static_pointer_cast<bb::Position2D>(entity->getComponent("Position"));

		if(position){
			if(entity->name == "bg"){
				position->position.x -= speed*deltaTime;

				if(position->position.x < -(x-10.0f)){ // 5px overlapping
					position->position.x = x;
				}
			}
			else{
				position->position.x -= cloudSpeed*deltaTime;

				if(position->position.x < -position->size.x){
					position->position.x = x;
				}
			}
		}
	}
}
