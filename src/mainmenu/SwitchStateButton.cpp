#include "SwitchStateButton.h"

SwitchStateButton::SwitchStateButton(const std::shared_ptr<bb::StateManager> states, const std::string &switchTo){
	this->states = states;
	this->switchTo = switchTo;
}

void SwitchStateButton::call(){
	states->switchTo(switchTo);
}
