#ifndef RESOLUTIONBUTTON_H_
#define RESOLUTIONBUTTON_H_

#include "../components/Command.h"

class Settings;

class ResolutionButton:public Command{
	public:
		enum ACTION{
			NEXT,
			PREVIOUS
		};

	private:
		std::shared_ptr<Settings> settings;
		unsigned int action;

	public:
		ResolutionButton(const std::shared_ptr<Settings> settings, const ACTION action);

		void call(const std::shared_ptr<bb::Entity> entity);
};

#endif
