/*
 * Device
 * Author: Marvin Blum
 * Last Update: 2014/05/03 18:31
 * */

#ifndef DEVICE_H_
#define DEVICE_H_

#include "../Component.h"

namespace bb{

class Device:public Component{
	public:
		enum class BUTTON{
			NONE,
			LEFT,
			MIDDLE,
			RIGHT
		};

		virtual ~Device(){}

		virtual void mouseMoved(int x, int y, int oldX, int oldY){}
		virtual void mousePressed(BUTTON button, int x, int y){}
		virtual void mouseReleased(BUTTON button, int x, int y){}
		virtual void mouseClicked(BUTTON button, int x, int y){}

		virtual void keyPressed(unsigned char c, int x, int y){}
		virtual void keyReleased(unsigned char c, int x, int y){}
		virtual	void keyTyped(unsigned char c, int x, int y){}
};

};

#endif
