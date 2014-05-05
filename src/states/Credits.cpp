#include "Credits.h"

Credits::Credits(const std::shared_ptr<LineRunner2> game){
	this->game = game;
}

void Credits::load(){
	//// entities

	//// systems
	renderer = std::unique_ptr<Renderer>(new Renderer(game->shader, game->camera));

	hasStarted = true;
}

void Credits::pause(){

}

void Credits::resume(){

}

void Credits::logic(const float deltaTime){
	if(hasStarted && deltaTime < 0.1){

	}
}

void Credits::render(const float deltaTime){
	if(hasStarted){
		renderer->update(deltaTime);
	}
}
