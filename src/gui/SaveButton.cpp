#include "SaveButton.h"
#include "../states/Settings.h"

SaveButton::SaveButton(const std::shared_ptr<Settings> settings){
	this->settings = settings;
}

void SaveButton::addSound(const std::shared_ptr<bb::Sound> sound){
	this->sound = std::shared_ptr<bb::SoundSource>(new bb::SoundSource(sound, bb::vec3(), false));
}

void SaveButton::call(const std::shared_ptr<bb::Entity> entity){
	if(sound){
		sound->play();
	}

	settings->save();
}
