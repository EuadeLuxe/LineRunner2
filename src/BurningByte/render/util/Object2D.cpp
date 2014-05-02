#include "Object2D.h"

namespace bb{

Object2D::Object2D(){
	modelMatrix = mat3();
	visible = true;
}

void Object2D::calculateModelMatrix(const std::shared_ptr<Component> positionable){
	std::shared_ptr<Position2D> position = std::static_pointer_cast<Position2D>(positionable);

	if(position){
		modelMatrix.setIdentity();
		modelMatrix.translate(position->position+position->rotationPoint);
		modelMatrix.rotate(position->rotation);
		modelMatrix.translate(-position->rotationPoint.x, -position->rotationPoint.y);
		modelMatrix.scale(position->size);
		modelMatrix.scale(position->scale);
	}
}

};
