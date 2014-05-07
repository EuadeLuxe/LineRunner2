#ifndef MAINMENU_H_
#define MAINMENU_H_

#include <memory>
#include <functional>
#include <vector>
#include <GL/gl3w.h>
#include "../BurningByte/state/State.h"
#include "../BurningByte/res/Shader.h"
#include "../LineRunner2.h"
#include "../systems/Renderer.h"
#include "../entities/Button.h"
#include "../gui/SwitchStateButton.h"
#include "../gui/ExitButton.h"

class MainMenu:public bb::State{
	private:
		std::shared_ptr<LineRunner2> game;
		std::shared_ptr<bb::Input> input;
		std::unique_ptr<Renderer> renderer;
		std::shared_ptr<SwitchStateButton> startButton, settingsButton, creditsButton;
		std::shared_ptr<ExitButton> exitButton;

	public:
		MainMenu(const std::shared_ptr<LineRunner2> game);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
