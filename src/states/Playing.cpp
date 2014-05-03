#include "Playing.h"

Playing::Playing(const std::shared_ptr<bb::StateManager> states, const std::shared_ptr<bb::Camera> camera, const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
	this->states = states;
	this->camera = camera;
}

void Playing::setViewport(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
}

void Playing::load(){
	//// res
	textures.push_back(std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D)));

	if(!textures[0]->loadTGA("res/textures/dk_games.tga")){
		std::cerr<<"Could not load res/textures/dk_games.tga!"<<std::endl;
	}

	//// entities
	auto halfScreen = bb::vec2(wndSize[0]/2, wndSize[1]/2);

	auto sprite = std::shared_ptr<bb::Entity>(new bb::Entity());
	sprite->addComponent("Texture", textures[0]);
	sprite->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(halfScreen.x-textures[0]->width()/2, halfScreen.y-textures[0]->height()/2), textures[0]->getSize())));
	sprite->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	//// systems
	renderer = std::unique_ptr<Renderer>(new Renderer(std::unique_ptr<bb::Shader>(new bb::Shader("src/BurningByte/shader/basic2D.vertex", "src/BurningByte/shader/basic2D.fragment")), camera));
	renderer->shader->bindAttrib("vertex0");
	renderer->shader->bindAttrib("texCoord0");

	renderer->addEntity(sprite);

	hasStarted = true;
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
		glClear(GL_COLOR_BUFFER_BIT);

		renderer->update(deltaTime);
	}
}
