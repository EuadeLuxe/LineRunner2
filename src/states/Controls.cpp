#include "Controls.h"

Controls::Controls(const std::shared_ptr<bb::Camera> camera, const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
	this->camera = camera;
}

void Controls::setViewport(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
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
		glClear(GL_COLOR_BUFFER_BIT);

		//renderer2D->update(deltaTime);
	}
}
