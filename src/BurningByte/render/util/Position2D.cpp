#include "Position2D.h"

namespace bb{

Position2D::Position2D(const vec2 &position, const float rotation, const vec2 &scale, const vec2 &direction, const vec2 &size){
	visible = true;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->direction = direction;
	this->size = size;

	setRotationPoint(CENTER);
}

Position2D::Position2D(const vec2 &position, const vec2 &size){
	visible = true;
	this->position = position;
	rotation = 0;
	scale = vec2(1.0f);
	direction = vec2();
	this->size = size;

	setRotationPoint(CENTER);
}

Position2D::Position2D(const vec2 &size){
	visible = true;
	position = vec2();
	rotation = 0;
	scale = vec2(1.0f);
	direction = vec2();
	this->size = size;

	setRotationPoint(CENTER);
}

Position2D::Position2D(){
	visible = true;
	position = vec2();
	rotation = 0;
	scale = vec2(1.0f);
	direction = vec2();
	size = vec2();

	setRotationPoint(CENTER);
}

void Position2D::setRotationPoint(const ROTATIONPOINT rotationPoint){
	switch(rotationPoint){
		case BOTTOMLEFT:
			this->rotationPoint = vec2();

			break;
		case BOTTOMRIGHT:
			this->rotationPoint = vec2(size.x, 0.0f);

			break;
		case TOPLEFT:
			this->rotationPoint = vec2(0.0f, size.y);

			break;
		case TOPRIGHT:
			this->rotationPoint = size;

			break;
		default: // center
			this->rotationPoint = size/2.0f;
	}
}

};
