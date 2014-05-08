#include "SetKeyButton.h"
#include "../states/Settings.h"

SetKeyButton::SetKeyButton(const std::shared_ptr<Settings> settings, const CONTROL control){
	this->settings = settings;
	this->control = control;
}

void SetKeyButton::call(const std::shared_ptr<bb::Entity> entity){
	settings->setButton(control);
}
