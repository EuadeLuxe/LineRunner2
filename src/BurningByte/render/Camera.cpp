#include "Camera.h"

namespace bb{

Camera::Camera(){
	viewport[0] = 0;
	viewport[1] = 0;
	viewport[2] = 0;
	viewport[3] = 0;

	projectionMatrix = mat4();
	orthoMatrix = mat4();
	orthoMatrix3 = mat3();
	viewMatrix = mat4();

	position = vec3();
	lookAt = vec3();
	up = vec3(0, 0, 1);

	fov = 60.0f;
	ratio = 1.0f;
	zNear = 1.0f;
	zFar = 10.0f;
}

void Camera::setViewport(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height){
	viewport[0] = x;
	viewport[1] = y;
	viewport[2] = width;
	viewport[3] = height;
}

void Camera::setViewport(const unsigned int width, const unsigned int height){
	setViewport(0, 0, width, height);
}

void Camera::calculateRatio(){
	ratio = float(viewport[2]-viewport[0])/float(viewport[3]-viewport[1]);
}

void Camera::calculateProjectionMatrix(){
	projectionMatrix.setIdentity();
	projectionMatrix.perspective(fov, ratio, zNear, zFar);
}

void Camera::calculateOrthoMatrix(){
	orthoMatrix.setIdentity();
	orthoMatrix.ortho(viewport[0], viewport[2], viewport[1], viewport[3], zNear, zFar);
}

void Camera::calculateOrthoMatrix3x3(){
	orthoMatrix3.setIdentity();
	orthoMatrix3.ortho(viewport[0], viewport[2], viewport[1], viewport[3]);
}

void Camera::calculateViewMatrix(){
	viewMatrix.setIdentity();
	viewMatrix.lookAt(position, lookAt, up);
}

};
