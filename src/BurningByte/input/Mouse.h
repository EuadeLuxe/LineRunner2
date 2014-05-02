/*
 * Mouse
 * Author: Marvin Blum
 * Last Update: 2014/05/02 19:16
 * */

#ifndef MOUSE_H_
#define MOUSE_H_

#include "../Component.h"

namespace bb{

class Mouse:public Component{
	public:
		enum class BUTTON{
			NONE,
			LEFT,
			MIDDLE,
			RIGHT
		};

		virtual ~Mouse(){}

		virtual void moved(int x, int y, int oldX, int oldY){}
		virtual void pressed(int x, int y, BUTTON button){}
		virtual void released(int x, int y, BUTTON button){}
		virtual void clicked(int x, int y, BUTTON button){}
};

};

#endif
