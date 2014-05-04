#include "MainMenu.h"

MainMenu::MainMenu(const std::shared_ptr<LineRunner2> game){
	this->game = game;
}

void MainMenu::load(){
	//// entities
	startButton = std::shared_ptr<SwitchStateButton>(new SwitchStateButton(game->stateManager, "playing"));
	settingsButton = std::shared_ptr<SwitchStateButton>(new SwitchStateButton(game->stateManager, "settings"));
	creditsButton = std::shared_ptr<SwitchStateButton>(new SwitchStateButton(game->stateManager, "credits"));
	exitButton = std::shared_ptr<ExitButton>(new ExitButton());

	auto texture = game->textures["start"];

	auto start = std::shared_ptr<Button>(new Button(startButton));
	start->addComponent("Texture", texture);
	start->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400, 60), texture->getSize())));
	start->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	texture = game->textures["settings"];

	auto settings = std::shared_ptr<Button>(new Button(settingsButton));
	settings->addComponent("Texture", texture);
	settings->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+74, 60), texture->getSize())));
	settings->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	texture = game->textures["credits"];

	auto credits = std::shared_ptr<Button>(new Button(creditsButton));
	credits->addComponent("Texture", texture);
	credits->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+148, 60), texture->getSize())));
	credits->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	texture = game->textures["exit"];

	auto exit = std::shared_ptr<Button>(new Button(exitButton));
	exit->addComponent("Texture", texture);
	exit->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+222, 60), texture->getSize())));
	exit->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	game->input->add(start);
	game->input->add(settings);
	game->input->add(credits);
	game->input->add(exit);

	texture = game->textures["logo"];

	auto logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	logo->addComponent("Texture", texture);
	logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(60, game->wndSize[1]-texture->height()-60), texture->getSize())));
	logo->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	//// systems
	renderer = std::unique_ptr<Renderer>(new Renderer(game->shader, game->camera));

	renderer->addEntity(start);
	renderer->addEntity(settings);
	renderer->addEntity(credits);
	renderer->addEntity(exit);
	renderer->addEntity(logo);

	hasStarted = true;
}

void MainMenu::pause(){

}

void MainMenu::resume(){

}

void MainMenu::logic(const float deltaTime){

}

void MainMenu::render(const float deltaTime){
	if(hasStarted){
		glClear(GL_COLOR_BUFFER_BIT);

		renderer->update(deltaTime);
	}
}
