#include "MainMenu.h"

MainMenu::MainMenu(const std::shared_ptr<LineRunner2> game){
	this->game = game;
}

void MainMenu::load(){
	game->bgMusic->play();

	//// entities
	startButton = std::shared_ptr<SwitchStateButton>(new SwitchStateButton(game->stateManager, "playing"));
	startButton->addSound(game->sounds["button_click"]);

	settingsButton = std::shared_ptr<SwitchStateButton>(new SwitchStateButton(game->stateManager, "settings"));
	settingsButton->addSound(game->sounds["button_click"]);

	creditsButton = std::shared_ptr<SwitchStateButton>(new SwitchStateButton(game->stateManager, "credits"));
	creditsButton->addSound(game->sounds["button_click"]);

	exitButton = std::shared_ptr<ExitButton>(new ExitButton());

	auto texture = game->textures["logo"];
	auto obj = std::shared_ptr<bb::Object2D>(new bb::Object2D());

	auto logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	logo->addComponent("Texture", texture);
	logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(60, game->wndSize[1]-texture->height()-60), texture->getSize())));
	logo->addComponent("Object2D", obj);

	texture = game->textures["start"];

	auto start = std::shared_ptr<Button>(new Button("start", startButton));
	start->addComponent("Texture", texture);
	start->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400, 60), texture->getSize())));
	start->addComponent("Object2D", obj);

	texture = game->textures["settings"];

	auto settings = std::shared_ptr<Button>(new Button("settings", settingsButton));
	settings->addComponent("Texture", texture);
	settings->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+74, 60), texture->getSize())));
	settings->addComponent("Object2D", obj);

	texture = game->textures["credits"];

	auto credits = std::shared_ptr<Button>(new Button("credits", creditsButton));
	credits->addComponent("Texture", texture);
	credits->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+148, 60), texture->getSize())));
	credits->addComponent("Object2D", obj);

	texture = game->textures["exit"];

	auto exit = std::shared_ptr<Button>(new Button("exit", exitButton));
	exit->addComponent("Texture", texture);
	exit->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+222, 60), texture->getSize())));
	exit->addComponent("Object2D", obj);

	//// systems
	input = std::shared_ptr<bb::Input>(new bb::Input());
	game->input = input;

	game->input->add(start);
	game->input->add(settings);
	game->input->add(credits);
	game->input->add(exit);

	renderer = std::unique_ptr<Renderer>(new Renderer(game->shader, game->camera));

	renderer->addEntity(logo);
	renderer->addEntity(start);
	renderer->addEntity(settings);
	renderer->addEntity(credits);
	renderer->addEntity(exit);

	hasStarted = true;
}

void MainMenu::pause(){

}

void MainMenu::resume(){
	game->input = input;
}

void MainMenu::logic(const float deltaTime){
	if(hasStarted && deltaTime < 1.0f){
		game->background->update(deltaTime);
	}
}

void MainMenu::render(const float deltaTime){
	if(hasStarted){
		game->bgrenderer->update(deltaTime);
		renderer->update(deltaTime);
	}
}
