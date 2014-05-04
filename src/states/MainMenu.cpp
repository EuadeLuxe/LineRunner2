#include "MainMenu.h"

MainMenu::MainMenu(const std::shared_ptr<bb::StateManager> states, const std::shared_ptr<bb::Input> input, const std::shared_ptr<bb::Camera> camera, const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
	this->states = states;
	this->input = input;
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
	textures.push_back(std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D)));

	textures[0]->loadTGA("res/textures/exit.tga");
	textures[1]->loadTGA("res/textures/settings.tga");
	textures[2]->loadTGA("res/textures/start.tga");
	textures[3]->loadTGA("res/textures/logo.tga");
	textures[4]->loadTGA("res/textures/bg/bg0.tga");

	//// entities
	startButton = std::shared_ptr<StartButton>(new StartButton());
	settingsButton = std::shared_ptr<SettingsButton>(new SettingsButton());
	exitButton = std::shared_ptr<ExitButton>(new ExitButton());

	auto start = std::shared_ptr<Button>(new Button(startButton));
	start->addComponent("Texture", textures[2]);
	start->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(wndSize[0]-300, 60), textures[2]->getSize())));
	start->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	auto settings = std::shared_ptr<Button>(new Button(settingsButton));
	settings->addComponent("Texture", textures[1]);
	settings->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(wndSize[0]-300+74, 60), textures[1]->getSize())));
	settings->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	auto exit = std::shared_ptr<Button>(new Button(exitButton));
	exit->addComponent("Texture", textures[0]);
	exit->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(wndSize[0]-300+148, 60), textures[0]->getSize())));
	exit->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	input->add(start);
	input->add(settings);
	input->add(exit);

	auto logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	logo->addComponent("Texture", textures[3]);
	logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(60, wndSize[1]-textures[3]->height()-60), textures[3]->getSize())));
	logo->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	auto bg0 = std::shared_ptr<bb::Entity>(new bb::Entity("bg0"));
	bg0->addComponent("Texture", textures[4]);
	bg0->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(), bb::vec2(wndSize[0], wndSize[1]))));
	bg0->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	auto bg1 = std::shared_ptr<bb::Entity>(new bb::Entity("bg1"));
	bg1->addComponent("Texture", textures[4]);
	bg1->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(wndSize[0]-5, 0), bb::vec2(wndSize[0], wndSize[1]))));
	bg1->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	//// systems
	renderer = std::unique_ptr<Renderer>(new Renderer(std::unique_ptr<bb::Shader>(new bb::Shader("res/shader/renderer.vertex", "res/shader/renderer.fragment")), camera));
	renderer->shader->bindAttrib("vertex0");
	renderer->shader->bindAttrib("texCoord0");

	renderer->addEntity(bg0);
	renderer->addEntity(bg1);
	renderer->addEntity(start);
	renderer->addEntity(settings);
	renderer->addEntity(exit);
	renderer->addEntity(logo);

	hasStarted = true;
}

void MainMenu::pause(){

}

void MainMenu::resume(){

}

void MainMenu::logic(const float deltaTime){
	if(hasStarted && deltaTime < 0.1){
		auto bg0 = renderer->getEntity("bg0");
		auto bg1 = renderer->getEntity("bg1");

		if(bg0 && bg1){
			auto pos0 = std::static_pointer_cast<bb::Position2D>(bg0->getComponent("Position"));
			auto pos1 = std::static_pointer_cast<bb::Position2D>(bg1->getComponent("Position"));

			if(pos0 && pos1){
				pos0->position.x -= 200.0f*deltaTime;
				pos1->position.x -= 200.0f*deltaTime;

				if(pos0->position.x < -float(wndSize[0]-5)){
					pos0->position.x = float(wndSize[0]-5);
				}

				if(pos1->position.x < -float(wndSize[0]-5)){
					pos1->position.x = float(wndSize[0]-5);
				}
			}
		}
	}
}

void MainMenu::render(const float deltaTime){
	if(hasStarted){
		glClear(GL_COLOR_BUFFER_BIT);

		renderer->update(deltaTime);
	}
}
