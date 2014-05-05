#include "Input.h"

namespace bb{

void Input::add(const std::shared_ptr<Device> device){
	devices.push_back(device);
}

void Input::remove(const std::shared_ptr<Device> device){
	devices.remove(device);
}

void Input::clear(){
	devices.clear();
}

void Input::mouseMoved(const int x, const int y){
	for(auto device : devices){
		device->mouseMoved(x, y, oldX, oldY);
	}

	oldX = x;
	oldY = y;
}

void Input::mousePressed(const Device::BUTTON button, const int x, const int y){
	for(auto device : devices){
		device->mousePressed(button, x, y);
	}

	oldX = x;
	oldY = y;
}

void Input::mouseReleased(const Device::BUTTON button, const int x, const int y){
	for(auto device : devices){
		device->mouseReleased(button, x, y);
	}

	oldX = x;
	oldY = y;
}

void Input::mouseClicked(const Device::BUTTON button, const int x, const int y){
	for(auto device : devices){
		device->mouseClicked(button, x, y);
	}

	oldX = x;
	oldY = y;
}

void Input::keyPressed(const unsigned char key, const int x, const int y){
	for(auto device : devices){
		device->keyPressed(key, x, y);
	}
}

void Input::keyReleased(const unsigned char key, const int x, const int y){
	for(auto device : devices){
		device->keyReleased(key, x, y);
	}
}

void Input::keyTyped(const unsigned char key, const int x, const int y){
	for(auto device : devices){
		device->keyTyped(key, x, y);
	}
}

};
