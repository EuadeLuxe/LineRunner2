#include "Credits.h"

Credits::Credits(const std::shared_ptr<LineRunner2> game){
	this->game = game;
}

void Credits::load(){

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
		glClear(GL_COLOR_BUFFER_BIT);

		//renderer2D->update(deltaTime);
	}
}
