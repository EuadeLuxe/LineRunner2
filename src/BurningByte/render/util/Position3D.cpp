#include "Position3D.h"

namespace bb{

Position3D::Position3D(const vec3 &position, const vec3 &rotation, const vec3 &scale, const vec3 &direction, const vec3 &rotationPoint){
	visible = true;
	this->position = position;
	this->scale = scale;
	this->direction = direction;
	this->rotationPoint = rotationPoint;
	this->rotation = rotation;
}

Position3D::Position3D(const vec3 &position){
	visible = true;
	this->position = position;
	scale = vec3(1);
	direction = vec3(1, 0, 0);
	rotationPoint = vec3();
	rotation = vec3();
}

Position3D::Position3D(){
	visible = true;
	position = vec3();
	scale = vec3(1);
	direction = vec3(1, 0, 0);
	rotationPoint = vec3();
	rotation = vec3();
}

};
