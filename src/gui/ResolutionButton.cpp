#include "ResolutionButton.h"
#include "../states/Settings.h"

ResolutionButton::ResolutionButton(const std::shared_ptr<Settings> settings, const ACTION action){
	this->settings = settings;
	this->action = action;
}

void ResolutionButton::call(const std::shared_ptr<bb::Entity> entity){
	if(action == ACTION::NEXT){
		settings->nextRes();
	}
	else{
		settings->previousRes();
	}
}
