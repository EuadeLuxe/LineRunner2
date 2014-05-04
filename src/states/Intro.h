#ifndef INTRO_H_
#define INTRO_H_

#include <memory>
#include <GL/gl3w.h>
#include "../BurningByte/state/State.h"
#include "../BurningByte/res/Texture.h"
#include "../components/Duration.h"
#include "../systems/DurationManager.h"
#include "../systems/Renderer.h"
#include "../LineRunner2.h"

class Intro:public std::enable_shared_from_this<Intro>, public bb::State, public bb::Device{
	private:
		std::shared_ptr<LineRunner2> game;
		std::unique_ptr<DurationManager> duration;
		std::unique_ptr<Renderer> renderer;

	public:
		Intro(const std::shared_ptr<LineRunner2> game);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);

		void keyPressed(unsigned char c, int x, int y);
};

#endif
