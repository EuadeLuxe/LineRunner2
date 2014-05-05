/*
 * Input
 * Author: Marvin Blum
 * Last Update: 2014/05/05 11:33
 * */

#ifndef INPUT_H_
#define INPUT_H_

#include <memory>
#include <list>
#include "Device.h"

namespace bb{

class Input{
	private:
		std::list<std::shared_ptr<Device>> devices;

		int oldX, oldY; // mouse position

	public:
		void add(const std::shared_ptr<Device> device);
		void remove(const std::shared_ptr<Device> device);
		void clear();

		void mouseMoved(const int x, const int y);
		void mousePressed(const Device::BUTTON button, const int x, const int y);
		void mouseReleased(const Device::BUTTON button, const int x, const int y);
		void mouseClicked(const Device::BUTTON button, const int x, const int y);

		void keyPressed(const unsigned char key, const int x, const int y);
		void keyReleased(const unsigned char key, const int x, const int y);
		void keyTyped(const unsigned char key, const int x, const int y);
};

};

#endif
