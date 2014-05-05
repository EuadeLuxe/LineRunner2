#include "SwitchStateButton.h"

SwitchStateButton::SwitchStateButton(const std::shared_ptr<bb::StateManager> states, const std::string &switchTo){
	this->states = states;
	this->switchTo = switchTo;
}

void SwitchStateButton::addSound(const std::shared_ptr<bb::Sound> sound){
	this->sound = std::shared_ptr<bb::SoundSource>(new bb::SoundSource(sound, bb::vec3(), false));
}

void SwitchStateButton::call(){
	if(sound){
		sound->play();
	}

	states->switchTo(switchTo);
}
