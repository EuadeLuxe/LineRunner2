/*
 * SoundSource
 * Author: Marvin Blum
 * Last Update: 2014/05/05 19:53
 * */

#ifndef SOUNDSOURCE_H_
#define SOUNDSOURCE_H_

#include <memory>
#include <AL/al.h>
#include "../res/buffer/Sound.h"
#include "../math/Vector.h"

namespace bb{

class SoundSource:public Component{
	private:
		unsigned int id;
		std::shared_ptr<Sound> sound;

	public:
		struct int3{
			int x, y, z;
		};

		SoundSource(const std::shared_ptr<Sound> sound, const vec3 &position, const bool loop);
		virtual ~SoundSource();

		void play();
		void pause();
		void rewind();
		void stop();

		void setSound(const std::shared_ptr<Sound> sound);
		void setPosition(const vec3 &position);
		void setVelocity(const vec3 &velocity);
		void setDirection(const vec3 &direction);
		void setGain(const float gain);
		void setPitch(const float pitch);
		void setRange(const float range);
		void setLoop(const bool loop);

		void set(const unsigned int param, const float value);
		void set(const unsigned int param, const float v0, const float v1, const float v2);
		void set(const unsigned int param, const float* value);
		void set(const unsigned int param, const int value);
		void set(const unsigned int param, const int v0, const int v1, const int v2);
		void set(const unsigned int param, const int* value);

		float getf(const unsigned int param);
		vec3 get3f(const unsigned int param);
		float* getfv(const unsigned int param);
		int geti(const unsigned int param);
		int3 get3i(const unsigned int param);
		int* getiv(const unsigned int param);

		unsigned int getID();
		int status();
};

};

#endif
