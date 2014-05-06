#ifndef PLAYING_H_
#define PLAYING_H_

#include <memory>
#include "../BurningByte/input/Input.h"
#include "../BurningByte/input/Device.h"
#include "../LineRunner2.h"
#include "../systems/Renderer.h"
#include "../entities/Button.h"
#include "../components/Animation.h"
#include "../buttons/SwitchStateButton.h"
#include "../buttons/RetryButton.h"

class Playing:public std::enable_shared_from_this<Playing>, public bb::State, public bb::Device{
	private:
		std::shared_ptr<LineRunner2> game;
		std::shared_ptr<bb::Input> input;
		std::unique_ptr<Renderer> renderer;

		bool paused;

		std::shared_ptr<RetryButton> retryButton;
		std::shared_ptr<SwitchStateButton> backButton;
		std::unique_ptr<bb::SoundSource> music;

	public:
		Playing(const std::shared_ptr<LineRunner2> game);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);

		void retry();
		void keyTyped(unsigned char c, int x, int y);
};

#endif
