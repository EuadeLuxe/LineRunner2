#include "Intro.h"

Intro::Intro(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
}

void Intro::setViewport(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
}

void Intro::load(){

}

void Intro::pause(){

}

void Intro::resume(){

}

void Intro::logic(const float deltaTime){
	if(hasStarted && deltaTime < 0.1){

	}
}

void Intro::render(const float deltaTime){
	if(hasStarted){
		glClear(GL_COLOR_BUFFER_BIT);

		//renderer2D->update(deltaTime);
	}
}
