/*
 * Sound
 * Author: Marvin Blum
 * Last Update: 2014/05/02 15:47
 * */

#ifndef SOUND_H_
#define SOUND_H_

#include <string>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include "../../Component.h"

namespace bb{

class Sound:public Component{
	private:
		unsigned int id;
		bool loaded;

	public:
		Sound();
		virtual ~Sound();

		void drop();

		void load(const std::string &path);

		bool good();
		unsigned int getID();
};

};

#endif
