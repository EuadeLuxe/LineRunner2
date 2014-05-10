/*
 * Matrix
 * Author: Marvin Blum
 * Last Update: 2014/05/10 12:10
 *	- Made include of <math.h> compatible with Visual Studio
 * */

#ifndef MATRIX_H_
#define MATRIX_H_

// Necessary since M_PI will only be defined in VS if _USE_MATH_DEFINES is defined
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif //_USE_MATH_DEFINES
#include <math.h>
#include "Vector.h"

namespace bb{

struct mat4{
	float values[16];

	mat4();
	mat4(const mat4 &m);
	mat4(const float m[16]);
	mat4(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i, const float j, const float k, const float l, const float m, const float n, const float o, const float p);

	float operator[](const unsigned int v);
	void operator=(const mat4 &m);
	void operator=(float m[16]);
	mat4 operator*(float v);
	mat4 operator*(const mat4 &m);
	mat4 operator/(float v);
	mat4 operator/(const mat4 &m);
	mat4 operator+(float v);
	mat4 operator+(const mat4 &m);
	mat4 operator-(float v);
	mat4 operator-(const mat4 &m);
	mat4 operator*=(float v);
	mat4 operator*=(const mat4 &m);
	mat4 operator/=(float v);
	mat4 operator/=(const mat4 &m);
	mat4 operator+=(float v);
	mat4 operator+=(const mat4 &m);
	mat4 operator-=(float v);
	mat4 operator-=(const mat4 &m);
	bool operator==(const mat4 &m);
	bool operator!=(const mat4 &m);
	
	vec4 operator*(const vec4 &v);
	vec3 operator*(const vec3 &v);

	float* getArray();
	void clear();
	float determinate();
	mat4 normalize();
	mat4 inverse();
	mat4 transpose();

	void setIdentity();
	void translate(const float x, const float y, const float z);
	void translate(const vec3 &v);
	void translate(const vec2 &v);
	void scale(const float x, const float y, const float z);
	void scale(const vec3 &v);
	void scale(const vec2 &v);
	void rotate(float angle, const float x, const float y, const float z);
	void rotate(float angle, const vec3 &v);
	void lookAt(const float x, const float y, const float z, const float xlook, const float ylook, const float zlook, const float xup, const float yup, const float zup);
	void lookAt(const vec3 &pos, const vec3 &look, const vec3 &up);
	void perspective(const float fov, const float ratio, const float nearp, const float farp);
	void ortho(const int left, const int right, const int bottom, const int top, const float nearp, const float farp);
};

struct mat3{
	float values[9];

	mat3();
	mat3(const mat3 &m);
	mat3(const float m[9]);
	mat3(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i);

	float operator[](const unsigned int v);
	void operator=(const mat3 &m);
	void operator=(float m[9]);
	mat3 operator*(float v);
	mat3 operator*(const mat3 &m);
	mat3 operator/(float v);
	mat3 operator/(const mat3 &m);
	mat3 operator+(float v);
	mat3 operator+(const mat3 &m);
	mat3 operator-(float v);
	mat3 operator-(const mat3 &m);
	mat3 operator*=(float v);
	mat3 operator*=(const mat3 &m);
	mat3 operator/=(float v);
	mat3 operator/=(const mat3 &m);
	mat3 operator+=(float v);
	mat3 operator+=(const mat3 &m);
	mat3 operator-=(float v);
	mat3 operator-=(const mat3 &m);
	bool operator==(const mat3 &m);
	bool operator!=(const mat3 &m);

	vec3 operator*(const vec3 &v);
	vec2 operator*(const vec2 &v);

	float* getArray();
	void clear();
	float determinate();
	mat3 inverse();
	mat3 transpose();

	void setIdentity();
	void translate(const float x, const float y);
	void translate(const vec2 &v);
	void scale(const float x, const float y);
	void scale(const vec2 &v);
	void rotate(float angle);
	void ortho(const int left, const int right, const int bottom, const int top);
};

};

#endif
