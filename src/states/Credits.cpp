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

	auto title = std::shared_ptr<bb::Text>(new bb::Text());
	title->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(140, game->wndSize[1]-240), bb::vec2(60.0f))));
	title->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));
	title->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	title->addComponent("Font", game->font);
	title->setText("Credits");

	auto text = std::shared_ptr<bb::Text>(new bb::Text());
	text->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(200.0f), bb::vec2(30.0f))));
	text->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));
	text->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	text->addComponent("Font", game->font);

	text->setText("ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\nƒ÷‹‰ˆ¸\n0123456789\n!\"ß%&/+*~#=?'`(){}[],.-;:_<>|\"'	-> missing backslash");

	//// systems
	input = std::shared_ptr<bb::Input>(new bb::Input());
	game->input = input;

	game->input->add(back);

	renderer = std::unique_ptr<Renderer>(new Renderer(game->shader, game->camera));

	renderer->addEntity(logo);
	renderer->addEntity(back);

	textRenderer = std::unique_ptr<TextRenderer>(new TextRenderer(game->shader, game->camera, game->font->texture));

	textRenderer->addEntity(title);
	textRenderer->addEntity(text);

	hasStarted = true;
}

void Credits::pause(){

}

void Credits::resume(){
	game->input = input;
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
		textRenderer->update(deltaTime);
	}
}
