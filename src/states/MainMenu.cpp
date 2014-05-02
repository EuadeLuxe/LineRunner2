#include "MainMenu.h"

MainMenu::MainMenu(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
}

void MainMenu::setViewport(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
}

void MainMenu::load(){

}

void MainMenu::pause(){

}

void MainMenu::resume(){

}

void MainMenu::logic(const float deltaTime){
	if(hasStarted && deltaTime < 0.1){

	}
}

void MainMenu::render(const float deltaTime){
	if(hasStarted){
		glClear(GL_COLOR_BUFFER_BIT);

		//renderer2D->update(deltaTime);
	}
}
