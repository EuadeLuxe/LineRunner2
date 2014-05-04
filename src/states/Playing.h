#ifndef PLAYING_H_
#define PLAYING_H_

#include <memory>
#include "../LineRunner2.h"

class Playing:public bb::State{
	private:
		std::shared_ptr<LineRunner2> game;

	public:
		Playing(const std::shared_ptr<LineRunner2> game);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
