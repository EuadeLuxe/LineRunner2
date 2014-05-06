#include "Playing.h"

Playing::Playing(const std::shared_ptr<LineRunner2> game){
	this->game = game;
	paused = false;
}

void Playing::load(){
	game->bgMusic->pause();

	// music
	music = std::unique_ptr<bb::SoundSource>(new bb::SoundSource(game->sounds["ingame"], bb::vec3(), true));
	music->play();

	//// entities
	auto texture = game->textures["paused"];
	auto invObj = std::shared_ptr<bb::Object2D>(new bb::Object2D());
	invObj->visible = false;

	auto pauseIcon = std::shared_ptr<bb::Entity>(new bb::Entity("paused"));
	pauseIcon->addComponent("Texture", texture);
	pauseIcon->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2((game->wndSize[0]-texture->width())/2.0f, (game->wndSize[1]-texture->height())/2.0f), texture->getSize())));
	pauseIcon->addComponent("Object2D", invObj);

	// buttons
	retryButton = std::shared_ptr<RetryButton>(new RetryButton(shared_from_this()));
	retryButton->addSound(game->sounds["button_click"]);

	backButton = std::shared_ptr<SwitchStateButton>(new SwitchStateButton(game->stateManager, "mainmenu"));
	backButton->addSound(game->sounds["button_click"]);

	texture = game->textures["retry"];

	auto retry = std::shared_ptr<Button>(new Button("retry", retryButton));
	retry->addComponent("Texture", texture);
	retry->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+148, 60), texture->getSize())));
	retry->addComponent("Object2D", invObj);

	texture = game->textures["back"];

	auto back = std::shared_ptr<Button>(new Button("back", backButton));
	back->addComponent("Texture", texture);
	back->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+222, 60), texture->getSize())));
	back->addComponent("Object2D", invObj);

	// player
	auto obj = std::shared_ptr<bb::Object2D>(new bb::Object2D());
	texture = game->textures["player"];

	auto frameTile = bb::vec2(1.0f/16.0f, 1.0f/8.0f);

	auto animation = std::shared_ptr<Animation>(new Animation(8.0f, true));
	animation->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(0.0f, 7.0f))));
	animation->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(1.0f, 7.0f))));
	animation->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(2.0f, 7.0f))));
	animation->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(3.0f, 7.0f))));
	animation->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(4.0f, 7.0f))));
	animation->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(5.0f, 7.0f))));
	animation->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(6.0f, 7.0f))));
	animation->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(7.0f, 7.0f))));
	animation->setCurrent(0);

	auto player = std::shared_ptr<bb::Entity>(new bb::Entity("player"));
	player->addComponent("Texture", texture);
	player->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(), bb::vec2(texture->width()/16, texture->height()/8))));
	player->addComponent("Object2D", obj);
	player->addComponent("Animation", animation);

	//// systems
	input = std::shared_ptr<bb::Input>(new bb::Input());
	game->input = input;

	input->add(shared_from_this());
	input->add(retry);
	input->add(back);

	renderer = std::unique_ptr<Renderer>(new Renderer(game->shader, game->camera));

	renderer->addEntity(pauseIcon);
	renderer->addEntity(retry);
	renderer->addEntity(back);
	renderer->addEntity(player);

	hasStarted = true;
}

void Playing::pause(){
	game->bgMusic->play();
	music->pause();
}

void Playing::resume(){
	game->input = input;
	game->bgMusic->pause();
	music->play();
	paused = false;

	auto obj = std::static_pointer_cast<bb::Object2D>(renderer->getEntity("paused")->getComponent("Object2D"));
	obj->visible = false;

	// reset game
	// ...
}

void Playing::logic(const float deltaTime){
	if(hasStarted && deltaTime < 1.0f && !paused){
		game->background->update(deltaTime);

		// update player animation
		auto animation = std::static_pointer_cast<Animation>(renderer->getEntity("player")->getComponent("Animation"));
		animation->update(deltaTime);
	}
}

void Playing::render(const float deltaTime){
	if(hasStarted){
		game->bgrenderer->update(deltaTime);
		renderer->update(deltaTime);
	}
}

void Playing::retry(){
	paused = false;
	music->play();
}

void Playing::keyTyped(unsigned char c, int x, int y){
	if(c == 27){ // ESC
		auto obj = std::static_pointer_cast<bb::Object2D>(renderer->getEntity("paused")->getComponent("Object2D"));

		if(!paused){
			paused = true;
			music->pause();
		}
		else{
			paused = false;
			music->play();
		}

		obj->visible = paused;
	}
}
