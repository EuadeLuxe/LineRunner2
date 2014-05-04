#include <GL/gl3w.h>
#include <GL/freeglut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <iostream>
#include <string>
#include <memory>

#include "LineRunner2.h"

// window
std::string wndTitle = "LineRunner 2";
unsigned int wndPosition[] = {50, 50};
unsigned int wndSize[] = {1920, 1080};

float fps = 0.0f, fps_frame = 0.0f, fps_time = 0.0f, fps_timebase = 0.0f, deltaTime = 0.0f; // fps

// game
std::shared_ptr<LineRunner2> game;

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
	game = std::shared_ptr<LineRunner2>(new LineRunner2(wndSize[0], wndSize[1]));
	game->load();

	return true;
}

/*
 * main loop
 * */

void render(){
	game->render(deltaTime);

	glutSwapBuffers();
}

void mainLoop(){
	deltaTime = 1.0f/fps;

	render();
	game->logic(deltaTime);
	getFPS();
}

/*
 * window
 * */

void reshape(const int w, const int h){
	wndSize[0] = w;
	wndSize[1] = h;

	game->setViewport(w, h);
}

/*
 * input
 * */

void keyPressed(unsigned char key, int x, int y){
	y = wndSize[1]-y;

	game->input->keyPressed(key, x, y);
}

void keyReleased(unsigned char key, int x, int y){
	y = wndSize[1]-y;

	game->input->keyReleased(key, x, y);
	game->input->keyTyped(key, x, y);
}

void mousePressed(int key, int state, int x, int y){
	bb::Device::BUTTON button;

	y = wndSize[1]-y;

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
		game->input->mousePressed(button, x, y);
	}
	else{
		game->input->mouseReleased(button, x, y);
		game->input->mouseClicked(button, x, y);
	}
}

void mouseMoved(int x, int y){
	y = wndSize[1]-y;

	game->input->mouseMoved(x, y);
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

	if(config.getRoot()->get("fullscreen")->toString() == "true"){
		glutFullScreen();
	}

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
