#ifndef CREDITS_H_
#define CREDITS_H_

#include <memory>
#include <string>
#include "../LineRunner2.h"
#include "../systems/Renderer.h"
#include "../entities/Button.h"
#include "../buttons/SwitchStateButton.h"

class Credits:public bb::State{
	private:
		std::shared_ptr<LineRunner2> game;
		std::unique_ptr<Renderer> renderer;
		std::shared_ptr<SwitchStateButton> backButton;

	public:
		Credits(const std::shared_ptr<LineRunner2> game);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
