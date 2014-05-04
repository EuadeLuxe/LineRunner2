#include "Button.h"

Button::Button(const std::shared_ptr<Command> command){
	this->command = command;
}

void Button::mouseClicked(BUTTON button, int x, int y){
	auto position = std::static_pointer_cast<bb::Position2D>(getComponent("Position"));

	if(position && x > position->position.x && x < position->position.x+position->size.x && y > position->position.y && y < position->position.y+position->size.y){
		command->call();
	}
}
