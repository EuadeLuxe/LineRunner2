/*
 * Vector
 * Author: Marvin Blum
 * Last Update: 23/12/2013 00:24
 * */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <math.h>
#include <stdlib.h>

namespace bb{

struct vec4;
struct vec3;
struct vec2;

// 4D vector
struct vec4{
	float x, y, z, w;

	vec4(float x, float y, float z, float w);
	vec4();
	vec4(float f);
	vec4(const vec2 &v);
	vec4(const vec3 &v);
	vec4(const vec4 &v);

	float operator[](const int &i);
	vec4 operator=(const vec4 &v);
	vec4 operator+(const vec4 &v);
	vec4 operator+(const float &s);
	vec4 operator-(const vec4 &v);
	vec4 operator-(const float &s);
	vec4 operator-();
	vec4 operator*(const vec4 &v);
	vec4 operator*(const float &s);
	vec4 operator/(const vec4 &v);
	vec4 operator/(const float &s);
	vec4 operator+=(const vec4 &v);
	vec4 operator+=(const float &s);
	vec4 operator-=(const vec4 &v);
	vec4 operator-=(const float &s);
	vec4 operator*=(const vec4 &v);
	vec4 operator*=(const float &s);
	vec4 operator/=(const vec4 &v);
	vec4 operator/=(const float &s);
	bool operator==(const vec4 &v);
	bool operator!=(const vec4 &v);
	bool operator<(const vec4 &v);
	bool operator>(const vec4 &v);

	float length();
	vec4 abs();
	float dot();
	float dot(const vec4 v);
	vec4 normalize();
};

// 3D vector
struct vec3{
    float x, y, z;
	
    vec3(float x, float y, float z);
    vec3();
	vec3(float f);
	vec3(const vec2 &v);
    vec3(const vec3 &v);
    vec3(const vec4 &v);
	vec3(float a, float b); // vector from angles

	float operator[](const int &i);
	vec3 operator=(const vec3 &v);
	vec3 operator+(const vec3 &v);
	vec3 operator+(const float &s);
    vec3 operator-(const vec3 &v);
	vec3 operator-(const float &s);
	vec3 operator-();
	vec3 operator*(const vec3 &v);
	vec3 operator*(const float &s);
	vec3 operator/(const vec3 &v);
	vec3 operator/(const float &s);
	vec3 operator+=(const vec3 &v);
	vec3 operator+=(const float &s);
	vec3 operator-=(const vec3 &v);
	vec3 operator-=(const float &s);
	vec3 operator*=(const vec3 &v);
	vec3 operator*=(const float &s);
	vec3 operator/=(const vec3 &v);
	vec3 operator/=(const float &s);
	bool operator==(const vec3 &v);
	bool operator!=(const vec3 &v);
	bool operator<(const vec3 &v);
	bool operator>(const vec3 &v);

    float length();
    vec3 abs();
	float dot();
	float dot(const vec3 &v);
    vec3 normalize();
	vec3 cross(const vec3 &v);
	vec3 cross(const vec3 &a, const vec3 &b);
};

// 2D vector
struct vec2{
	float x, y;

	vec2(float x, float y);
    vec2();
	vec2(float f);
    vec2(const vec2 &v);
    vec2(const vec3 &v);
    vec2(const vec4 &v);
	
	float operator[](const int &i);
	vec2 operator=(const vec2 &v);
	vec2 operator+(const vec2 &v);
	vec2 operator+(const float &s);
    vec2 operator-(const vec2 &v);
	vec2 operator-(const float &s);
	vec2 operator*(const vec2 &v);
	vec2 operator*(const float &s);
	vec2 operator/(const vec2 &v);
	vec2 operator/(const float &s);
	vec2 operator+=(const vec2 &v);
	vec2 operator+=(const float &s);
	vec2 operator-=(const vec2 &v);
	vec2 operator-=(const float &s);
	vec2 operator*=(const vec2 &v);
	vec2 operator*=(const float &s);
	vec2 operator/=(const vec2 &v);
	vec2 operator/=(const float &s);
	bool operator==(const vec2 &v);
	bool operator!=(const vec2 &v);
	bool operator<(const vec2 &v);
	bool operator>(const vec2 &v);

    float length();
    vec2 abs();
	float dot();
	float dot(const vec2 &v);
    vec2 normalize();
};

};

#endif
