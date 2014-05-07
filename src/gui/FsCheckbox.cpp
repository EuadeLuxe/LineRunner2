#include "FsCheckbox.h"

FsCheckbox::FsCheckbox(const std::shared_ptr<bb::Texture> checked, const std::shared_ptr<bb::Texture> unchecked){
	this->checked = checked;
	this->unchecked = unchecked;
}

void FsCheckbox::call(const std::shared_ptr<bb::Entity> entity){
	auto checkbox = std::static_pointer_cast<Checkbox>(entity);

	if(checkbox){
		checkbox->removeComponent("Texture");

		if(checkbox->checked()){
			checkbox->addComponent("Texture", checked);
		}
		else{
			checkbox->addComponent("Texture", unchecked);
		}
	}
}
