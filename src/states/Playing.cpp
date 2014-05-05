#include "Playing.h"

Playing::Playing(const std::shared_ptr<LineRunner2> game){
	this->game = game;
	paused = false;
}

void Playing::load(){
	game->bgMusic->pause();

	//// entities
	auto texture = game->textures["paused"];
	auto invObj = std::shared_ptr<bb::Object2D>(new bb::Object2D());
	invObj->visible = false;

	auto pauseIcon = std::shared_ptr<bb::Entity>(new bb::Entity("paused"));
	pauseIcon->addComponent("Texture", texture);
	pauseIcon->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2((game->wndSize[0]-texture->width())/2.0f, (game->wndSize[1]-texture->height())/2.0f), texture->getSize())));
	pauseIcon->addComponent("Object2D", invObj);

	// buttons
	backButton = std::shared_ptr<SwitchStateButton>(new SwitchStateButton(game->stateManager, "mainmenu"));
	backButton->addSound(game->sounds["button_click"]);

	texture = game->textures["back"];

	auto back = std::shared_ptr<Button>(new Button("back", backButton));
	back->addComponent("Texture", texture);
	back->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+222, 60), texture->getSize())));
	back->addComponent("Object2D", invObj);

	//// systems
	input = std::shared_ptr<bb::Input>(new bb::Input());
	game->input = input;

	input->add(shared_from_this());
	input->add(back);

	renderer = std::unique_ptr<Renderer>(new Renderer(game->shader, game->camera));

	renderer->addEntity(pauseIcon);
	renderer->addEntity(back);

	hasStarted = true;
}

void Playing::pause(){
	game->bgMusic->play();
}

void Playing::resume(){
	game->input = input;
	game->bgMusic->pause();
	paused = false;

	auto obj = std::static_pointer_cast<bb::Object2D>(renderer->getEntity("paused")->getComponent("Object2D"));
	obj->visible = false;

	// reset game
	// ...
}

void Playing::logic(const float deltaTime){
	if(hasStarted && deltaTime < 1.0f && !paused){
		game->background->update(deltaTime);
	}
}

void Playing::render(const float deltaTime){
	if(hasStarted){
		game->bgrenderer->update(deltaTime);
		renderer->update(deltaTime);
	}
}

void Playing::keyTyped(unsigned char c, int x, int y){
	if(c == 27){ // ESC
		auto obj = std::static_pointer_cast<bb::Object2D>(renderer->getEntity("paused")->getComponent("Object2D"));

		if(!paused){
			paused = true;
		}
		else{
			paused = false;
		}

		obj->visible = paused;
	}
}
