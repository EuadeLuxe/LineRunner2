#include "SaveButton.h"

SaveButton::SaveButton(){

}

void SaveButton::addSound(const std::shared_ptr<bb::Sound> sound){
	this->sound = std::shared_ptr<bb::SoundSource>(new bb::SoundSource(sound, bb::vec3(), false));
}

void SaveButton::call(const std::shared_ptr<bb::Entity> entity){
	if(sound){
		sound->play();
	}

	// ...
}
