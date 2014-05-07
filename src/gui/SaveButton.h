#ifndef SAVEBUTTON_H_
#define SAVEBUTTON_H_

#include <memory>
#include "../BurningByte/res/buffer/Sound.h"
#include "../BurningByte/sound/SoundSource.h"
#include "../components/Command.h"

class SaveButton:public Command{
	private:
		std::shared_ptr<bb::SoundSource> sound;

	public:
		SaveButton();

		void addSound(const std::shared_ptr<bb::Sound> sound);

		void call(const std::shared_ptr<bb::Entity> entity);
};

#endif
