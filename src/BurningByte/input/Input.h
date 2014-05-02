/*
 * Input
 * Author: Marvin Blum
 * Last Update: 2014/05/02 19:16
 * */

#ifndef INPUT_H_
#define INPUT_H_

#include <memory>
#include <list>
#include "Mouse.h"
#include "Keyboard.h"

namespace bb{

class Input{
	private:
		std::list<std::shared_ptr<Mouse>> mouse;
		std::list<std::shared_ptr<Keyboard>> keyboard;

		int oldX, oldY; // mouse position

	public:
		void add(const std::shared_ptr<Mouse> device);
		void add(const std::shared_ptr<Keyboard> device);
		void remove(const std::shared_ptr<Mouse> device);
		void remove(const std::shared_ptr<Keyboard> device);

		void mouseMoved(const int x, const int y);
		void mousePressed(const int x, const int y, const Mouse::BUTTON button);
		void mouseReleased(const int x, const int y, const Mouse::BUTTON button);
		void mouseClicked(const int x, const int y, const Mouse::BUTTON button);

		void keyPressed(const unsigned char key);
		void keyReleased(const unsigned char key);
		void keyTyped(const unsigned char key);
};

};

#endif
