/*
 * State
 * Author: Marvin Blum
 * Last Update: 25/12/2013 22:43
 * */

#ifndef STATE_H_
#define STATE_H_

namespace bb{

class State{
	protected:
		bool hasStarted;

	public:
		State();
		virtual ~State();

		virtual void load() = 0;

		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void logic(const float deltaTime) = 0;
		virtual void render(const float deltaTime) = 0;

		bool started();
};

};

#endif
