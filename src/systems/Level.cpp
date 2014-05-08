#include "Level.h"
#include "../states/Playing.h"

const float Level::tolerance = 20.0f;

Level::Level(const std::shared_ptr<LineRunner2> game, const std::shared_ptr<Playing> playing, const std::shared_ptr<Player> player, const float speed){
	this->game = game;
	this->playing = playing;
	this->player = player;
	this->speed = speed;
	way = 0;
}

void Level::reset(){
	last = std::shared_ptr<bb::Position2D>(new bb::Position2D());
	way = 0;
	bool first = true;

	for(auto entity : entities){
		auto position = std::static_pointer_cast<bb::Position2D>(entity->getComponent("Position"));

		if(position){
			position->position.x = last->position.x+last->size.x-10; // 10px overlap

			if(rand()%100 < 30){ // 30% chance for a gap
				position->position.x += 200+rand()%200;
			}

			position->size.x = 600+rand()%1000;

			if(first){
				position->size.x += 1000.0f;
				position->size.y = game->wndSize[1]/3-2;
				first = false;
			}
			else{
				position->size.y = game->wndSize[1]/3+rand()%100;
			}

			last = position;

			continue;
		}
	}
}

void Level::update(const float deltaTime){
	way += speed*deltaTime;

	auto pPos = std::static_pointer_cast<bb::Position2D>(player->getComponent("Position"));

	for(auto entity : entities){
		auto position = std::static_pointer_cast<bb::Position2D>(entity->getComponent("Position"));

		if(position){
			// move
			position->position.x -= speed*deltaTime;

			// repositioning
			if(position->position.x < -position->size.x){
				position->position.x = last->position.x+last->size.x-10;

				if(rand()%100 < 30){
					position->position.x += 200+rand()%200;
				}

				position->size.x = 600+rand()%1000;
				position->size.y = game->wndSize[1]/3+rand()%100;

				last = position;

				continue;
			}

			// collision with player
			if(pPos->position.x < position->position.x+position->size.x && pPos->position.x+pPos->size.x > position->position.x){
				if(pPos->position.y < position->size.y && pPos->position.y > position->size.y-tolerance){
					pPos->direction.y = 0.0f;
					pPos->position.y = position->size.y;

					if(player->jumping){
						std::static_pointer_cast<Animation>(player->getComponent("Animation"))->set("run");
						player->jumping = false;
					}
				}
				else if(pPos->position.y < position->size.y-tolerance){
					playing->lose(way);
				}
			}
		}
	}
}

float Level::getWay(){
	return way;
}
