#include <GL/gl3w.h>
#include <GL/glut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <iostream>
#include <string>
#include <memory>

#include "BurningByte/res/files/cfgFile.h"
#include "BurningByte/state/StateManager.h"
#include "BurningByte/res/buffer/Sound.h"
#include "BurningByte/sound/Listener.h"
#include "BurningByte/sound/SoundSource.h"
#include "BurningByte/input/Input.h"
#include "BurningByte/input/Device.h"
#include "states/Intro.h"
#include "states/MainMenu.h"
#include "states/Controls.h"
#include "states/Playing.h"

// window
std::string wndTitle = "LineRunner 2";
unsigned int wndPosition[] = {50, 50};
unsigned int wndSize[] = {1200, 800};

float fps = 0.0f, fps_frame = 0.0f, fps_time = 0.0f, fps_timebase = 0.0f, deltaTime = 0.0f; // fps

// game
std::shared_ptr<bb::StateManager> stateManager;
std::shared_ptr<bb::Input> input;
std::shared_ptr<bb::Camera> camera;
std::unique_ptr<bb::Listener> listener;

float getFPS(){
	fps_frame++;
	fps_time = float(glutGet(GLUT_ELAPSED_TIME));

	if(fps_time-fps_timebase > 1000){
		fps = fps_frame*1000.0f/(fps_time-fps_timebase);
		fps_timebase = fps_time;
		fps_frame = 0;
	}

	return fps;
}

bool setup(){
	std::cout<<"Loading..."<<std::endl;

	// input system
	input = std::shared_ptr<bb::Input>(new bb::Input());

	// set up camera and listener
	camera = std::shared_ptr<bb::Camera>(new bb::Camera());
	camera->zNear = -1.0f;
	camera->zFar = 1.0f;
	camera->setViewport(wndSize[0], wndSize[1]);

	listener = std::unique_ptr<bb::Listener>(new bb::Listener(bb::vec3()));

	// we render 2D, everywhere...
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	stateManager = std::shared_ptr<bb::StateManager>(new bb::StateManager());
	stateManager->add("intro", std::shared_ptr<bb::State>(new Intro(stateManager, input, camera, wndSize[0], wndSize[1])));
	stateManager->add("mainmenu", std::shared_ptr<bb::State>(new MainMenu(stateManager, camera, wndSize[0], wndSize[1])));
	stateManager->add("controls", std::shared_ptr<bb::State>(new Controls(stateManager, camera, wndSize[0], wndSize[1])));
	stateManager->add("playing", std::shared_ptr<bb::State>(new Playing(stateManager, camera, wndSize[0], wndSize[1])));

	std::cout<<"Loading done!"<<std::endl;

	return true;
}

/*
 * main loop
 * */

void render(){
	stateManager->current()->render(deltaTime);

	glutSwapBuffers();
}

void mainLoop(){
	deltaTime = 1.0f/fps;

	render();

	stateManager->current()->logic(deltaTime);

	getFPS();
}

/*
 * window
 * */

void reshape(const int w, const int h){
	wndSize[0] = w;
	wndSize[1] = h;

	camera->setViewport(w, h);
}

/*
 * input
 * */

void keyPressed(unsigned char key, int x, int y){
	input->keyPressed(key, x, y);
}

void keyReleased(unsigned char key, int x, int y){
	input->keyReleased(key, x, y);
	input->keyTyped(key, x, y);
}

void mousePressed(int key, int state, int x, int y){
	bb::Device::BUTTON button;

	if(key == 0){
		button = bb::Device::BUTTON::LEFT;
	}
	else if(key == 1){
		button = bb::Device::BUTTON::MIDDLE;
	}
	else if(key == 2){
		button = bb::Device::BUTTON::RIGHT;
	}

	if(!state){
		input->mousePressed(button, x, y);
	}
	else{
		input->mouseReleased(button, x, y);
		input->mouseClicked(button, x, y);
	}
}

void mouseMoved(int x, int y){
	input->mouseMoved(x, y);
}

int main(int argc, char** args){
	// read settings
	bb::cfgFile config;

	if(config.read("res/settings.cfg")){
		auto root = config.getRoot();

		if(root->get("wndTitle")){
			wndTitle = root->get("wndTitle")->toString();
		}

		if(root->get("wndPosition")->value.size() == 2){
			wndPosition[0] = root->get("wndPosition")->toInt(0);
			wndPosition[1] = root->get("wndPosition")->toInt(1);
		}

		if(root->get("wndSize")->value.size() == 2){
			wndSize[0] = root->get("wndSize")->toInt(0);
			wndSize[1] = root->get("wndSize")->toInt(1);
		}
	}

	// GLUT init
	glutInit(&argc, args);
	glutInitWindowPosition(wndPosition[0], wndPosition[1]);
	glutInitWindowSize(wndSize[0], wndSize[1]);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE); // rgba, double buffer, NO depth buffer (GL_DEPTH)

	// gl3w init
	if(!gl3wInit()){
		std::cerr<<"Could not initialize gl3w!"<<std::endl;
		return 1;
	}

	// ALUT init
	alutInit(&argc, args);
	alGetError(); // clear error bit

	// GLUT window
	glutCreateWindow((char*)wndTitle.c_str());
	glutReshapeFunc(reshape);
	glutIdleFunc(mainLoop);
	glutDisplayFunc(mainLoop);

	// GLUT input
	glutKeyboardFunc(keyPressed); // (unsigned char key, int x, int y)
	glutKeyboardUpFunc(keyReleased); // (unsigned char key, int x, int y)
	glutMouseFunc(mousePressed); // (int key, int state, int x, int y)
	glutPassiveMotionFunc(mouseMoved); // (int x, int y)
	glutMotionFunc(mouseMoved); // (int x, int y)

	if(!setup()){
		return 2;
	}

	// start
	glutMainLoop();

	// ALUT cleanup
	alutExit();

	return 0;
}
