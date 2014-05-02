/*
 * Camera
 * Author: Marvin Blum
 * Last Update: 2014/04/07 17:00
 * */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "../math/Matrix.h"

namespace bb{

class Camera{
	public:
		unsigned int viewport[4];
		vec3 position, lookAt, up;
		float fov, ratio, zNear, zFar;

		mat4 projectionMatrix, orthoMatrix, viewMatrix; // 3D
		mat3 orthoMatrix3; // 2D

		Camera();

		void setViewport(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height);
		void setViewport(const unsigned int width, const unsigned int height);

		void calculateRatio();
		void calculateProjectionMatrix();
		void calculateOrthoMatrix();
		void calculateOrthoMatrix3x3();
		void calculateViewMatrix();
};

};

#endif
