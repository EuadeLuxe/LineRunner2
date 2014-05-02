#include "Object3D.h"

namespace bb{

Object3D::Object3D(){
	modelMatrix = mat4();
	visible = true;
}

void Object3D::calculateModelMatrix(const std::shared_ptr<Component> positionable){
	std::shared_ptr<Position3D> position = std::static_pointer_cast<Position3D>(positionable);

	if(position){
		modelMatrix.setIdentity();
		modelMatrix.translate(position->position+position->rotationPoint);
		modelMatrix.rotate(position->rotation.x, 1.0f, 0.0f, 0.0f);
		modelMatrix.rotate(position->rotation.y, 0.0f, 1.0f, 0.0f);
		modelMatrix.rotate(position->rotation.z, 0.0f, 0.0f, 1.0f);
		modelMatrix.translate(-(position->rotationPoint+position->rotationPoint));
		modelMatrix.scale(position->scale);
	}
}

};
