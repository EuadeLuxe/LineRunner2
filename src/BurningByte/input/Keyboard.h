/*
 * Keyboard
 * Author: Marvin Blum
 * Last Update: 2014/05/02 19:16
 * */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "../Component.h"

namespace bb{

class Keyboard:public Component{
	public:
		virtual ~Keyboard(){}

		virtual void pressed(const unsigned char c){}
		virtual void released(const unsigned char c){}
		virtual	void typed(const unsigned char c){}
};

};

#endif
