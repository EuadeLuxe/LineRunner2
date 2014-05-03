#include "Intro.h"

Intro::Intro(const std::shared_ptr<bb::StateManager> states, const std::shared_ptr<bb::Camera> camera, const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
	this->states = states;
	this->camera = camera;
}

void Intro::setViewport(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
}

void Intro::load(){
	//// res
	textures.push_back(std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D)));
	textures.push_back(std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D)));
	textures.push_back(std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D)));

	if(!textures[0]->loadTGA("res/textures/dk_games.tga")){
		std::cerr<<"Could not load res/textures/dk_games.tga!"<<std::endl;
	}

	if(!textures[1]->loadTGA("res/textures/bb_logo.tga")){
		std::cerr<<"Could not load res/textures/bb_logo.tga!"<<std::endl;
	}

	if(!textures[2]->loadTGA("res/textures/logo.tga")){
		std::cerr<<"Could not load res/textures/logo.tga!"<<std::endl;
	}

	//// entities
	auto halfScreen = bb::vec2(wndSize[0]/2, wndSize[1]/2);

	auto dk_logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	dk_logo->addComponent("Texture", textures[0]);
	dk_logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(halfScreen.x-textures[0]->width()/2, halfScreen.y-textures[0]->height()/2), textures[0]->getSize())));
	dk_logo->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));
	dk_logo->addComponent("Duration", std::shared_ptr<Duration>(new Duration(2, 2, 2, 2)));

	auto bb_logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	bb_logo->addComponent("Texture", textures[1]);
	bb_logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(halfScreen.x-textures[1]->width()/2, halfScreen.y-textures[1]->height()/2), textures[1]->getSize())));
	bb_logo->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));
	bb_logo->addComponent("Duration", std::shared_ptr<Duration>(new Duration(8, 2, 2, 2)));

	auto logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	logo->addComponent("Texture", textures[2]);
	logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(halfScreen.x-textures[2]->width()/2, halfScreen.y-textures[2]->height()/2), textures[2]->getSize())));
	logo->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));
	logo->addComponent("Duration", std::shared_ptr<Duration>(new Duration(14, 2, 2, 2)));

	//// systems
	duration = std::unique_ptr<DurationManager>(new DurationManager());

	duration->addEntity(dk_logo);
	duration->addEntity(bb_logo);
	duration->addEntity(logo);

	renderer = std::unique_ptr<Renderer>(new Renderer(std::unique_ptr<bb::Shader>(new bb::Shader("res/shader/renderer.vertex", "res/shader/renderer.fragment")), camera));
	renderer->shader->bindAttrib("vertex0");
	renderer->shader->bindAttrib("texCoord0");

	renderer->addEntity(dk_logo);
	renderer->addEntity(bb_logo);
	renderer->addEntity(logo);

	hasStarted = true;
}

void Intro::pause(){

}

void Intro::resume(){

}

void Intro::logic(const float deltaTime){
	if(hasStarted && deltaTime < 0.1){
		duration->update(deltaTime);

		if(duration->screen == 3){
			states->switchTo("playing");
		}
	}
}

void Intro::render(const float deltaTime){
	if(hasStarted){
		glClear(GL_COLOR_BUFFER_BIT);

		renderer->update(deltaTime);
	}
}
