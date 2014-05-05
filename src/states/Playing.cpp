#include "Playing.h"

Playing::Playing(const std::shared_ptr<LineRunner2> game){
	this->game = game;
}

void Playing::load(){

}

void Playing::pause(){

}

void Playing::resume(){

}

void Playing::logic(const float deltaTime){
	if(hasStarted && deltaTime < 0.1){

	}
}

void Playing::render(const float deltaTime){
	if(hasStarted){
		//renderer->update(deltaTime);
	}
}
