#include "Checkbox.h"

Checkbox::Checkbox(const std::string &name, const std::shared_ptr<Command> command, const bool check):Entity(name){
	this->command = command;
	this->check = check;
}

Checkbox::Checkbox(const std::shared_ptr<Command> command, const bool check){
	this->command = command;
	this->check = check;
}

void Checkbox::mouseClicked(BUTTON button, int x, int y){
	if(button != BUTTON::LEFT){
		return;
	}

	auto position = std::static_pointer_cast<bb::Position2D>(getComponent("Position"));

	if(position && x > position->position.x && x < position->position.x+position->size.x && y > position->position.y && y < position->position.y+position->size.y){
		if(check){
			check = false;
		}
		else{
			check = true;
		}

		if(command){
			command->call(shared_from_this());
		}
	}
}

bool Checkbox::checked(){
	return check;
}
