#include "Input.h"

namespace bb{

void Input::add(const std::shared_ptr<Mouse> device){
	mouse.push_back(device);
}

void Input::add(const std::shared_ptr<Keyboard> device){
	keyboard.push_back(device);
}

void Input::remove(const std::shared_ptr<Mouse> device){
	mouse.remove(device);
}

void Input::remove(const std::shared_ptr<Keyboard> device){
	keyboard.remove(device);
}

void Input::mouseMoved(const int x, const int y){
	for(auto device : mouse){
		device->moved(x, y, oldX, oldY);
	}

	oldX = x;
	oldY = y;
}

void Input::mousePressed(const int x, const int y, const Mouse::BUTTON button){
	for(auto device : mouse){
		device->pressed(x, y, button);
	}

	oldX = x;
	oldY = y;
}

void Input::mouseReleased(const int x, const int y, const Mouse::BUTTON button){
	for(auto device : mouse){
		device->released(x, y, button);
	}

	oldX = x;
	oldY = y;
}

void Input::mouseClicked(const int x, const int y, const Mouse::BUTTON button){
	for(auto device : mouse){
		device->clicked(x, y, button);
	}

	oldX = x;
	oldY = y;
}

void Input::keyPressed(const unsigned char key){
	for(auto device : keyboard){
		device->pressed(key);
	}
}

void Input::keyReleased(const unsigned char key){
	for(auto device : keyboard){
		device->released(key);
	}
}

void Input::keyTyped(const unsigned char key){
	for(auto device : keyboard){
		device->typed(key);
	}
}

};
