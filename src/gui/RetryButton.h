#ifndef RETRYBUTTON_H_
#define RETRYBUTTON_H_

#include <memory>
#include <string>
#include "../BurningByte/res/buffer/Sound.h"
#include "../BurningByte/sound/SoundSource.h"
#include "../components/Command.h"

class Playing;

class RetryButton:public Command{
	private:
		std::shared_ptr<Playing> playing;
		std::shared_ptr<bb::SoundSource> sound;

	public:
		RetryButton(const std::shared_ptr<Playing> playing);

		void addSound(const std::shared_ptr<bb::Sound> sound);

		void call(const std::shared_ptr<bb::Entity> entity);
};

#endif
