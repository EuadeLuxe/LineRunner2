#include "Level.h"

Level::Level(const std::shared_ptr<LineRunner2> game, const std::shared_ptr<bb::Position2D> player, const float speed){
	this->game = game;
	this->player = player;
	this->speed = speed;

	last = std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]), bb::vec2()));
}

void Level::update(const float deltaTime){
	for(auto entity : entities){
		auto position = std::static_pointer_cast<bb::Position2D>(entity->getComponent("Position"));

		if(position){
			// move
			position->position.x -= speed*deltaTime;

			// repositioning
			if(position->position.x < -position->size.x){
				position->position.x = last->position.x+last->size.x-2; // 2px overlap

				if(rand()%100 < 30){ // 30% chance for a gap
					position->position.x += 100+rand()%100;
				}

				position->size.x = game->wndSize[1]/5+rand()%(game->wndSize[1]/4);
				position->size.y = game->wndSize[1]/3+rand()%100;

				last = position;

				continue;
			}

			// collision with player
			if(player->position.x < position->position.x+position->size.x && player->position.x+player->size.x > position->position.x){
				player->position.y = position->size.y;
			}
		}
	}
}
