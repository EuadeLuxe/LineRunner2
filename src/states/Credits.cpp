#include "Credits.h"

Credits::Credits(const std::shared_ptr<LineRunner2> game){
	this->game = game;
}

void Credits::load(){
	//// entities
	backButton = std::shared_ptr<SwitchStateButton>(new SwitchStateButton(game->stateManager, "mainmenu"));

	auto texture = game->textures["logo"];

	auto logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	logo->addComponent("Texture", texture);
	logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(60, game->wndSize[1]-texture->height()-60), texture->getSize())));
	logo->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	texture = game->textures["back"];

	auto back = std::shared_ptr<Button>(new Button("back", backButton));
	back->addComponent("Texture", texture);
	back->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+222, 60), texture->getSize())));
	back->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	game->input->add(back);

	//// systems
	renderer = std::unique_ptr<Renderer>(new Renderer(game->shader, game->camera));

	renderer->addEntity(logo);
	renderer->addEntity(back);

	hasStarted = true;
}

void Credits::pause(){
	game->input->clear();
}

void Credits::resume(){
	game->input->add(std::static_pointer_cast<Button>(renderer->getEntity("back")));
}

void Credits::logic(const float deltaTime){
	if(hasStarted && deltaTime < 1.0f){
		game->background->update(deltaTime);
	}
}

void Credits::render(const float deltaTime){
	if(hasStarted){
		game->bgrenderer->update(deltaTime);
		renderer->update(deltaTime);
	}
}
