#ifndef FSCHECKBOX_H_
#define FSCHECKBOX_H_


#include <iostream>


#include <memory>
#include "../BurningByte/Entity.h"
#include "../BurningByte/res/Texture.h"
#include "../components/Command.h"
#include "../entities/Checkbox.h"

class FsCheckbox:public Command{
	private:
		std::shared_ptr<bb::Texture> checked, unchecked;

	public:
		FsCheckbox(const std::shared_ptr<bb::Texture> checked, const std::shared_ptr<bb::Texture> unchecked);

		void call(const std::shared_ptr<bb::Entity> entity);
};

#endif
