#include "Playing.h"

Playing::Playing(const std::shared_ptr<LineRunner2> game){
	this->game = game;
	paused = false;
	countdown = 3.0f;
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

	// countdown
	auto countdownText = std::shared_ptr<bb::Text>(new bb::Text("countdown"));
	countdownText->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]/2, game->wndSize[1]/2), bb::vec2(120.0f))));
	countdownText->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));
	countdownText->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	countdownText->addComponent("Font", game->font);
	countdownText->setText("3");

	// player
	auto obj = std::shared_ptr<bb::Object2D>(new bb::Object2D());
	texture = game->textures["player"];

	auto frameTile = bb::vec2(1.0f/16.0f, 1.0f/8.0f);

	auto idle = std::shared_ptr<Animation::Set>(new Animation::Set(true));
	auto run = std::shared_ptr<Animation::Set>(new Animation::Set(true));
	auto jump = std::shared_ptr<Animation::Set>(new Animation::Set(false));
	auto roll = std::shared_ptr<Animation::Set>(new Animation::Set(false));

	for(float i = 0.0f; i < 8.0f; i++){
		idle->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(i, 7.0f))));
		run->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(i, 6.0f))));
		jump->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(i, 5.0f))));
		roll->add(std::shared_ptr<Animation::Keyframe>(new Animation::Keyframe(frameTile, frameTile*bb::vec2(i, 4.0f))));
	}

	auto animation = std::shared_ptr<Animation>(new Animation(16.0f));
	animation->add("idle", idle);
	animation->add("run", run);
	animation->add("jump", jump);
	animation->add("roll", roll);

	auto player = std::shared_ptr<Player>(new Player("player"));
	player->addComponent("Texture", texture);
	player->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]/4, game->wndSize[1]/3), bb::vec2(texture->width()/16, texture->height()/8))));
	player->addComponent("Object2D", obj);
	player->addComponent("Animation", animation);

	//// systems
	input = std::shared_ptr<bb::Input>(new bb::Input());
	game->input = input;

	input->add(shared_from_this());
	input->add(player);

	renderer = std::unique_ptr<Renderer>(new Renderer(game->shader, game->camera));
	level = std::unique_ptr<Level>(new Level(game, player, 500.0f));

	// fill in 20 blocks (or "buildings")
	auto color = std::shared_ptr<Color>(new Color(bb::vec3(97.0f/256.0f, 131.0f/256.0f, 96.0f/256.0f)));

	for(int i = 0; i < 20; i++){
		auto box = std::shared_ptr<bb::Entity>(new bb::Entity());
		box->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(i*10, 0.0f), bb::vec2(10.0f))));
		box->addComponent("Object2D", obj);
		box->addComponent("Color", color);

		renderer->addEntity(box);
		level->addEntity(box);
	}

	level->reset();

	renderer->addEntity(pauseIcon);
	renderer->addEntity(retry);
	renderer->addEntity(back);
	renderer->addEntity(player);

	textRenderer = std::unique_ptr<TextRenderer>(new TextRenderer(game->shader, game->camera, game->font->texture));

	textRenderer->addEntity(countdownText);

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

	// reset?
}

void Playing::logic(const float deltaTime){
	if(hasStarted && deltaTime < 1.0f && !paused){
		game->background->update(deltaTime);

		auto player = std::static_pointer_cast<Player>(renderer->getEntity("player"));

		// update player animation
		auto animation = std::static_pointer_cast<Animation>(player->getComponent("Animation"));
		animation->update(deltaTime);

		if(countdown < 0.0f){
			// update level
			level->update(deltaTime);

			// jump/fall
			auto position = std::static_pointer_cast<bb::Position2D>(player->getComponent("Position"));

			if(!player->rolling && player->jump && !player->jumping){
				position->direction.y = fallSpeed;
				player->jumping = true;
				animation->set("jump");
			}

			position->position.y += position->direction.y*deltaTime;

			if(position->direction.y > -fallSpeed){
				position->direction.y -= deltaTime*fallFactor;
			}

			// roll
			if(player->roll && !player->rolling){
				if(player->jumping){
					player->jumping = false;
					position->direction.y = -fallSpeed;
				}

				player->rolling = true;
				animation->set("roll");
			}

			if(player->rolling && animation->current()->currentIndex() == 7){ // last frame
				player->rolling = false;
				animation->set("run");
			}
		}
		else{
			auto countdownText = std::static_pointer_cast<bb::Text>(textRenderer->getEntity("countdown"));
			countdown -= deltaTime;

			if(countdown < 0.0f){
				auto obj = std::static_pointer_cast<bb::Object2D>(countdownText->getComponent("Object2D"));
				obj->visible = false;
				animation->set("run");
			}
			else if(countdown < 1.0f){
				countdownText->setText("1");
			}
			else if(countdown < 2.0f){
				countdownText->setText("2");
			}
		}
	}
}

void Playing::render(const float deltaTime){
	if(hasStarted){
		game->bgrenderer->update(deltaTime);
		renderer->update(deltaTime);
		textRenderer->update(deltaTime);
	}
}

void Playing::retry(){
	paused = false;
	countdown = 3.0f;
	music->play();

	auto countdownText = std::static_pointer_cast<bb::Text>(textRenderer->getEntity("countdown"));
	countdownText->setText("3");

	std::static_pointer_cast<bb::Object2D>(countdownText->getComponent("Object2D"))->visible = true;
	std::static_pointer_cast<bb::Object2D>(renderer->getEntity("paused")->getComponent("Object2D"))->visible = false;

	// reset player
	auto player = renderer->getEntity("player");

	std::static_pointer_cast<Animation>(player->getComponent("Animation"))->set("idle");
	std::static_pointer_cast<bb::Position2D>(player->getComponent("Position"))->position.y = game->wndSize[1]/3;

	level->reset();
}

void Playing::keyTyped(unsigned char key, int x, int y){
	if(key == 27){ // ESC
		auto obj = std::static_pointer_cast<bb::Object2D>(renderer->getEntity("paused")->getComponent("Object2D"));

		if(!paused){
			paused = true;
			music->pause();
			input->add(std::static_pointer_cast<Button>(renderer->getEntity("retry")));
			input->add(std::static_pointer_cast<Button>(renderer->getEntity("back")));
		}
		else{
			paused = false;
			music->play();
			input->remove(std::static_pointer_cast<Button>(renderer->getEntity("retry")));
			input->remove(std::static_pointer_cast<Button>(renderer->getEntity("back")));
		}

		obj->visible = paused;
	}
}
