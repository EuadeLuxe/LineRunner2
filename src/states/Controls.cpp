#include "Controls.h"

Controls::Controls(const std::shared_ptr<LineRunner2> game){
	this->game = game;
}

void Controls::load(){

}

void Controls::pause(){

}

void Controls::resume(){

}

void Controls::logic(const float deltaTime){
	if(hasStarted && deltaTime < 0.1){

	}
}

void Controls::render(const float deltaTime){
	if(hasStarted){
		//renderer->update(deltaTime);
	}
}
