#include "RetryButton.h"
#include "../states/Playing.h"

RetryButton::RetryButton(const std::shared_ptr<Playing> playing){
	this->playing = playing;
}

void RetryButton::addSound(const std::shared_ptr<bb::Sound> sound){
	this->sound = std::shared_ptr<bb::SoundSource>(new bb::SoundSource(sound, bb::vec3(), false));
}

void RetryButton::call(const std::shared_ptr<bb::Entity> entity){
	if(sound){
		sound->play();
	}

	playing->retry();
}
