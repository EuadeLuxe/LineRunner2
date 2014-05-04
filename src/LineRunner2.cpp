#include "LineRunner2.h"
#include "states/Intro.h"
#include "states/MainMenu.h"
#include "states/Controls.h"
#include "states/Credits.h"
#include "states/Playing.h"

LineRunner2::LineRunner2(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
}

void LineRunner2::loadTexture(const std::string &name, const std::string &path){
	auto texture = std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D));
	texture->loadTGA(path);
	textures.insert(std::make_pair(name, texture));
}

void LineRunner2::load(){
	// input system
	input = std::shared_ptr<bb::Input>(new bb::Input());

	// set up shader, camera and listener
	shader = std::shared_ptr<bb::Shader>(new bb::Shader("res/shader/renderer.vertex", "res/shader/renderer.fragment"));
	shader->bindAttrib("vertex0");
	shader->bindAttrib("texCoord0");

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

	// load assets
	loadTexture("dk_games", "res/textures/dk_games.tga");
	loadTexture("bb_logo", "res/textures/bb_logo.tga");
	loadTexture("logo", "res/textures/logo.tga");

	loadTexture("start", "res/textures/buttons/start.tga");
	loadTexture("settings", "res/textures/buttons/settings.tga");
	loadTexture("credits", "res/textures/buttons/credits.tga");
	loadTexture("exit", "res/textures/buttons/exit.tga");
	loadTexture("logo", "res/textures/logo.tga");
	loadTexture("bg0", "res/textures/bg/bg0.tga");
	loadTexture("bg1", "res/textures/bg/bg1.tga");

	// add and load states
	stateManager = std::shared_ptr<bb::StateManager>(new bb::StateManager());
	stateManager->add("intro", std::shared_ptr<bb::State>(new Intro(shared_from_this())));
	stateManager->add("mainmenu", std::shared_ptr<bb::State>(new MainMenu(shared_from_this())));
	stateManager->add("controls", std::shared_ptr<bb::State>(new Controls(shared_from_this())));
	stateManager->add("credits", std::shared_ptr<bb::State>(new Credits(shared_from_this())));
	stateManager->add("playing", std::shared_ptr<bb::State>(new Playing(shared_from_this())));
}

void LineRunner2::setViewport(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
}

void LineRunner2::logic(const float deltaTime){
	stateManager->current()->logic(deltaTime);
}

void LineRunner2::render(const float deltaTime){
	stateManager->current()->render(deltaTime);
}
