#include "Playing.h"

Playing::Playing(const unsigned int width, const unsigned int height){
	fps = 0.0f;
	wndSize[0] = width;
	wndSize[1] = height;
}

void Playing::setViewport(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;

	camera->setViewport(width, height);
}

void Playing::load(){
	//// camera
	camera = std::shared_ptr<bb::Camera>(new bb::Camera());
	camera->zNear = -1.0f;
	camera->zFar = 1.0f;
	camera->setViewport(wndSize[0], wndSize[1]);

	listener = std::unique_ptr<bb::Listener>(new bb::Listener(bb::vec3()));

	//// res
	textures.push_back(std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D)));

	sounds.push_back(std::shared_ptr<bb::Sound>(new bb::Sound()));

	if(!textures[0]->loadTGA("res/textures/dk_games.tga")){
		std::cerr<<"Could not load res/textures/dk_games.tga!"<<std::endl;
	}

	sounds[0]->load("res/sounds/piano.wav");

	//// entities
	auto sprite = std::shared_ptr<bb::Entity>(new bb::Entity());
	sprite->addComponent("Texture", textures[0]);
	sprite->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(400.0f))));
	sprite->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	//// systems
	renderer2D = std::unique_ptr<Renderer2D>(new Renderer2D(std::unique_ptr<bb::Shader>(new bb::Shader("src/BurningByte/shader/basic2D.vertex", "src/BurningByte/shader/basic2D.fragment")), camera));
	renderer2D->shader->bindAttrib("vertex0");
	renderer2D->shader->bindAttrib("texCoord0");

	renderer2D->addEntity(sprite);

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

		renderer2D->update(deltaTime);
	}
}
