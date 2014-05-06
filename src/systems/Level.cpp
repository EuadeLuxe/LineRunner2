#include "Level.h"

Level::Level(const std::shared_ptr<LineRunner2> game, const float speed){
	this->game = game;
	this->speed = speed;
}

void Level::update(const float deltaTime){
	for(auto entity : entities){
		auto position = std::static_pointer_cast<bb::Position2D>(entity->getComponent("Position"));

		if(position){
			position->position.x -= speed*deltaTime;

			if(position->position.x < -position->size.x){
				position->position.x = game->wndSize[0];
				position->size.x = 100+rand()%200;
				position->size.y = game->wndSize[1]/4+rand()%200;
			}
		}
	}
}
