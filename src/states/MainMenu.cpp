#include "MainMenu.h"

MainMenu::MainMenu(const std::shared_ptr<bb::StateManager> states, const std::shared_ptr<bb::Camera> camera, const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
	this->states = states;
	this->camera = camera;
}

void MainMenu::setViewport(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
}

void MainMenu::load(){
	//// res
	textures.push_back(std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D)));
	textures.push_back(std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D)));
	textures.push_back(std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D)));
	textures.push_back(std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D)));

	textures[0]->loadTGA("res/textures/exit.tga");
	textures[1]->loadTGA("res/textures/settings.tga");
	textures[2]->loadTGA("res/textures/start.tga");
	textures[3]->loadTGA("res/textures/logo.tga");

	//// entities
	auto exit = std::shared_ptr<bb::Entity>(new bb::Entity());
	exit->addComponent("Texture", textures[0]);
	exit->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(wndSize[0]-300+148, 40), textures[0]->getSize())));
	exit->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	auto settings = std::shared_ptr<bb::Entity>(new bb::Entity());
	settings->addComponent("Texture", textures[1]);
	settings->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(wndSize[0]-300+74, 40), textures[1]->getSize())));
	settings->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	auto start = std::shared_ptr<bb::Entity>(new bb::Entity());
	start->addComponent("Texture", textures[2]);
	start->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(wndSize[0]-300, 40), textures[2]->getSize())));
	start->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	auto logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	logo->addComponent("Texture", textures[3]);
	logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(40, wndSize[1]-textures[3]->height()-40), textures[3]->getSize())));
	logo->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	//// systems
	renderer = std::unique_ptr<Renderer>(new Renderer(std::unique_ptr<bb::Shader>(new bb::Shader("res/shader/renderer.vertex", "res/shader/renderer.fragment")), camera));
	renderer->shader->bindAttrib("vertex0");
	renderer->shader->bindAttrib("texCoord0");

	renderer->addEntity(exit);
	renderer->addEntity(settings);
	renderer->addEntity(start);
	renderer->addEntity(logo);

	hasStarted = true;
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

		renderer->update(deltaTime);
	}
}
