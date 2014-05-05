#include "Intro.h"

Intro::Intro(const std::shared_ptr<LineRunner2> game){
	this->game = game;
}

void Intro::load(){
	//// entities
	auto halfScreen = bb::vec2(game->wndSize[0]/2, game->wndSize[1]/2);
	auto texture = game->textures["dk_games"];

	auto dk_logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	dk_logo->addComponent("Texture", texture);
	dk_logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(halfScreen.x-texture->width()/2, halfScreen.y-texture->height()/2), texture->getSize())));
	dk_logo->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));
	dk_logo->addComponent("Duration", std::shared_ptr<Duration>(new Duration(2, 2, 2, 2)));

	texture = game->textures["bb_logo"];

	auto bb_logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	bb_logo->addComponent("Texture", texture);
	bb_logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(halfScreen.x-texture->width()/2, halfScreen.y-texture->height()/2), texture->getSize())));
	bb_logo->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));
	bb_logo->addComponent("Duration", std::shared_ptr<Duration>(new Duration(8, 2, 2, 2)));

	texture = game->textures["logo"];

	auto logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	logo->addComponent("Texture", texture);
	logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(halfScreen.x-texture->width()/2, halfScreen.y-texture->height()/2), texture->getSize())));
	logo->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));
	logo->addComponent("Duration", std::shared_ptr<Duration>(new Duration(14, 2, 2, 2)));

	//// systems
	input = std::shared_ptr<bb::Input>(new bb::Input());
	input->add(shared_from_this());
	game->input = input;

	duration = std::unique_ptr<DurationManager>(new DurationManager());

	duration->addEntity(dk_logo);
	duration->addEntity(bb_logo);
	duration->addEntity(logo);

	renderer = std::unique_ptr<Renderer>(new Renderer(std::unique_ptr<bb::Shader>(new bb::Shader("res/shader/renderer.vertex", "res/shader/renderer.fragment")), game->camera));
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
			//states->remove("intro");
			game->stateManager->switchTo("mainmenu");
		}
	}
}

void Intro::render(const float deltaTime){
	if(hasStarted){
		renderer->update(deltaTime);
	}
}

void Intro::keyPressed(unsigned char c, int x, int y){
	if(hasStarted){
		//states->remove("intro");
		game->stateManager->switchTo("mainmenu");
	}
}
