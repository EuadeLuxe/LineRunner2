#include "Credits.h"

Credits::Credits(const std::shared_ptr<LineRunner2> game){
	this->game = game;
}

void Credits::load(){
	//// entities
	backButton = std::shared_ptr<SwitchStateButton>(new SwitchStateButton(game->stateManager, "mainmenu"));
	backButton->addSound(game->sounds["button_click"]);

	auto texture = game->textures["logo"];
	auto obj = std::shared_ptr<bb::Object2D>(new bb::Object2D());

	auto logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	logo->addComponent("Texture", texture);
	logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(60, game->wndSize[1]-texture->height()/2-60), bb::vec2(400.0f, 150.0f))));
	logo->addComponent("Object2D", obj);

	texture = game->textures["back"];

	auto back = std::shared_ptr<Button>(new Button("back", backButton));
	back->addComponent("Texture", texture);
	back->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+222, 60), texture->getSize())));
	back->addComponent("Object2D", obj);

	auto title = std::shared_ptr<bb::Text>(new bb::Text());
	title->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(140, game->wndSize[1]-240), bb::vec2(60.0f))));
	title->addComponent("Object2D", obj);
	title->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	title->addComponent("Font", game->font);
	title->setText("Credits");

	auto content0 = std::shared_ptr<bb::Text>(new bb::Text());
	content0->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(200, game->wndSize[1]/2+200), bb::vec2(40.0f))));
	content0->addComponent("Object2D", obj);
	content0->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	content0->addComponent("Font", game->font);

	content0->setText("This game was created by Marvin Blum.\nGet the game and source code on GitHub:\n\n\t\thttps://github.com/DeKugelschieber/LineRunner2\n\nMain menu music: \"Revolve\" by cinematrik:\n\t\thttp://ccmixter.org/files/hisboyelroy/430\nIngame music: \"TONTURA\" by URB:\n\t\thttp://freemusicarchive.org/music/URB/U_END/09_urb_-_tontura\n\nPlayer animation by BlueCobold\nWindows port by EuadeLuxe");

	//// systems
	input = std::shared_ptr<bb::Input>(new bb::Input());
	game->input = input;

	game->input->add(back);

	renderer = std::unique_ptr<Renderer>(new Renderer(game->shader, game->camera));

	renderer->addEntity(logo);
	renderer->addEntity(back);

	textRenderer = std::unique_ptr<TextRenderer>(new TextRenderer(game->shader, game->camera, game->font->texture));

	textRenderer->addEntity(title);
	textRenderer->addEntity(content0);

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
