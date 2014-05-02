#include "Vector.h"

namespace bb{

// 4D vector
vec4::vec4(float x, float y, float z, float w):
	x(x),
	y(y),
	z(z),
	w(w){}

vec4::vec4():
	x(0.0f),
	y(0.0f),
	z(0.0f),
	w(0.0f){}

vec4::vec4(float f):
	x(f),
	y(f),
	z(f),
	w(f){}

vec4::vec4(const vec2 &v):
	x(v.x),
	y(v.y),
	z(0.0f),
	w(0.0f){}

vec4::vec4(const vec3 &v):
	x(v.x),
	y(v.y),
	z(v.z),
	w(0.0f){}

vec4::vec4(const vec4 &v):
	x(v.x),
	y(v.y),
	z(v.z),
	w(v.w){}

float vec4::operator[](const int &i){
	if(i == 0){
		return x;
	}
	else if(i == 1){
		return y;
	}
	else if(i == 2){
		return z;
	}
	else{
		return w;
	}
}

vec4 vec4::operator=(const vec4 &v){
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;

	return *this;
}

vec4 vec4::operator+(const vec4 &v){
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
}

vec4 vec4::operator+(const float &s){
	x += s;
	y += s;
	z += s;
	w += s;

	return *this;
}

vec4 vec4::operator-(const vec4 &v){
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;

	return *this;
}

vec4 vec4::operator-(const float &s){
	x -= s;
	y -= s;
	z -= s;
	w -= s;

	return *this;
}

vec4 vec4::operator-(){
	x = -x;
	y = -y;
	z = -z;
	w = -w;

	return *this;
}

vec4 vec4::operator*(const vec4 &v){
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;

	return *this;
}

vec4 vec4::operator*(const float &s){
	x *= s;
	y *= s;
	z *= s;
	w *= s;

	return *this;
}

vec4 vec4::operator/(const vec4 &v){
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;

	return *this;
}

vec4 vec4::operator/(const float &s){
	x /= s;
	y /= s;
	z /= s;
	w /= s;

	return *this;
}

vec4 vec4::operator+=(const vec4 &v){
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
}

vec4 vec4::operator+=(const float &s){
	x += s;
	y += s;
	z += s;
	w += s;

	return *this;
}

vec4 vec4::operator-=(const vec4 &v){
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;

	return *this;
}

vec4 vec4::operator-=(const float &s){
	x -= s;
	y -= s;
	z -= s;
	w -= s;

	return *this;
}

vec4 vec4::operator*=(const vec4 &v){
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;

	return *this;
}

vec4 vec4::operator*=(const float &s){
	x *= s;
	y *= s;
	z *= s;
	w *= s;

	return *this;
}

vec4 vec4::operator/=(const vec4 &v){
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;

	return *this;
}

vec4 vec4::operator/=(const float &s){
	x /= s;
	y /= s;
	z /= s;
	w /= s;

	return *this;
}

bool vec4::operator==(const vec4 &v){
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool vec4::operator!=(const vec4 &v){
	return x != v.x || y != v.y || z != v.z || w != v.w;
}

bool vec4::operator<(const vec4 &v){
	return x < v.x && y < v.y && z < v.z && w < v.w;
}

bool vec4::operator>(const vec4 &v){
	return x > v.x && y > v.y && z > v.z && w > v.w;
}

float vec4::length(){
	return sqrt(dot());
}

vec4 vec4::abs(){
	return vec4(fabs(x), fabs(y), fabs(z), fabs(w));
}

float vec4::dot(){
	return x*x+y*y+z*z+w*w;
}

float vec4::dot(const vec4 v){
	return x*v.x+y*v.y+z*v.z+w*v.w;
}

vec4 vec4::normalize(){
	float l = length();

	x /= l;
	y /= l;
	z /= l;
	w /= l;

	return *this;
}

// 3D vector
vec3::vec3(float x, float y, float z):
	x(x),
	y(y),
	z(z){}

vec3::vec3():
	x(0.0f),
	y(0.0f),
	z(0.0f){}

vec3::vec3(float f):
	x(f),
	y(f),
	z(f){}

vec3::vec3(const vec2 &v):
	x(v.x),
	y(v.y),
	z(0.0f){}

vec3::vec3(const vec3 &v):
	x(v.x),
	y(v.y),
	z(v.z){}

vec3::vec3(const vec4 &v):
	x(v.x),
	y(v.y),
	z(v.z){}

vec3::vec3(float a, float b): // Vektor aus Winkeln
	x(float(sin(a))),
	y(float(tan((b-(floor(b/M_PI))*M_PI-M_PI/2)))),
	z(float(cos(a))){}

float vec3::operator[](const int &i){
	if(i == 0){
		return x;
	}
	else if(i == 1){
		return y;
	}
	else{
		return z;
	}
}
	
vec3 vec3::operator=(const vec3 &v){
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}
	
vec3 vec3::operator+(const vec3 &v){
	return vec3(x+v.x, y+v.y, z+v.z);
}

vec3 vec3::operator+(const float &s){
	return vec3(x+s, y+s, z+s);
}

vec3 vec3::operator-(const vec3 &v){
    return vec3(x-v.x, y-v.y, z-v.z);
}

vec3 vec3::operator-(const float &s){
	return vec3(x-s, y-s, z-s);
}

vec3 vec3::operator-(){
	return vec3(-x, -y, -z);
}

vec3 vec3::operator*(const vec3 &v){
    return vec3(x*v.x, y*v.y, z*v.z);
}

vec3 vec3::operator*(const float &s){
	return vec3(x*s, y*s, z*s);
}
	
vec3 vec3::operator/(const vec3 &v){
	return vec3(x/v.x, y/v.y, z/v.z);
}

vec3 vec3::operator/(const float &s){
	return vec3(x/s, y/s, z/s);
}
	
vec3 vec3::operator+=(const vec3 &v){
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}
	
vec3 vec3::operator+=(const float &s){
    x += s;
    y += s;
    z += s;

    return *this;
}

vec3 vec3::operator-=(const vec3 &v){
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

vec3 vec3::operator-=(const float &s){
    x -= s;
    y -= s;
    z -= s;

    return *this;
}

vec3 vec3::operator*=(const vec3 &v){
    x *= v.x;
	y *= v.y;
	z *= v.z;

    return *this;
}
	
vec3 vec3::operator*=(const float &s){
	x *= s;
	y *= s;
	z *= s;

    return *this;
}

vec3 vec3::operator/=(const vec3 &v){
	x /= v.x;
	y /= v.y;
	z /= v.z;

    return *this;
}

vec3 vec3::operator/=(const float &s){
    x /= s;
	y /= s;
	z /= s;

    return *this;
}

bool vec3::operator==(const vec3 &v){
	return v.x == x && v.y == y && v.z == z;
}

bool vec3::operator!=(const vec3 &v){
	return v.x != x || v.y != y || v.z != z;
}

bool vec3::operator<(const vec3 &v){
	return x < v.x && y < v.y && z < v.z;
}

bool vec3::operator>(const vec3 &v){
	return x > v.x && y > v.y && z > v.z;
}

float vec3::length(){
    return sqrtf(dot());
}

vec3 vec3::abs(){
	return vec3(fabs(x), fabs(y), fabs(z));
}

float vec3::dot(){
	return x*x+y*y+z*z;
}

float vec3::dot(const vec3 &v){
	return x*v.x+y*v.y+z*v.z;
}

vec3 vec3::normalize(){
    float l = length();
		
    x /= l;
    y /= l;
    z /= l;

    return *this;
}

vec3 vec3::cross(const vec3 &v){
	x = (y*v.z)-(z*v.y);
	y = (z*v.x)-(x*v.z);
	z = (x*v.y)-(y*v.x);

	return *this;
}

vec3 vec3::cross(const vec3 &a, const vec3 &b){
	x = (a.y*b.z)-(a.z*b.y);
	y = (a.z*b.x)-(a.x*b.z);
	z = (a.x*b.y)-(a.y*b.x);

	return *this;
}

// 2D vector
vec2::vec2(float x, float y):
	x(x),
	y(y){}

vec2::vec2():
	x(0.0f),
	y(0.0f){}

vec2::vec2(float f):
	x(f),
	y(f){}

vec2::vec2(const vec2 &v):
	x(v.x),
	y(v.y){}

vec2::vec2(const vec3 &v):
	x(v.x),
	y(v.y){}

vec2::vec2(const vec4 &v):
	x(v.x),
	y(v.y){}

float vec2::operator[](const int &i){
	if(i == 0){
		return x;
	}
	else{
		return y;
	}
}

vec2 vec2::operator=(const vec2 &v){
    if (this == &v) {
        return *this;
    }

    x = v.x;
    y = v.y;

    return *this;
}
	
vec2 vec2::operator+(const vec2 &v){
	return vec2(x+v.x, y+v.y);
}

vec2 vec2::operator+(const float &s){
	return vec2(x+s, y+s);
}

vec2 vec2::operator-(const vec2 &v){
    return vec2(x-v.x, y-v.y);
}

vec2 vec2::operator-(const float &s){
	return vec2(x-s, y-s);
}
	
vec2 vec2::operator*(const vec2 &v){
    return vec2(x*v.x, y*v.y);
}

vec2 vec2::operator*(const float &s){
	return vec2(x*s, y*s);
}
	
vec2 vec2::operator/(const vec2 &v){
	return vec2(x/v.x, y/v.y);
}

vec2 vec2::operator/(const float &s){
	return vec2(x/s, y/s);
}    

vec2 vec2::operator+=(const vec2 &v){
    x += v.x;
    y += v.y;

    return *this;
}
	
vec2 vec2::operator+=(const float &s){
    x += s;
    y += s;

    return *this;
}

vec2 vec2::operator-=(const vec2 &v){
    x -= v.x;
    y -= v.y;

    return *this;
}

vec2 vec2::operator-=(const float &s){
    x -= s;
    y -= s;

    return *this;
}
	
vec2 vec2::operator*=(const vec2 &v){
    x *= v.x;
	y *= v.y;

    return *this;
}
	
vec2 vec2::operator*=(const float &s){
	x *= s;
	y *= s;

    return *this;
}

vec2 vec2::operator/=(const vec2 &v){
	x /= v.x;
	y /= v.y;

    return *this;
}	

vec2 vec2::operator/=(const float &s){
    x /= s;
	y /= s;

    return *this;
}

bool vec2::operator==(const vec2 &v){
	return v.x == x && v.y == y;
}
	
bool vec2::operator!=(const vec2 &v){
	return v.x != x || v.y != y;
}

bool vec2::operator<(const vec2 &v){
	return x < v.x && y < v.y;
}

bool vec2::operator>(const vec2 &v){
	return x > v.x && y > v.y;
}

float vec2::length(){
    return sqrtf(dot());
}

vec2 vec2::abs(){
	return vec2(fabs(x), fabs(y));
}

float vec2::dot(){
	return x*x+y*y;
}

float vec2::dot(const vec2 &v){
	return x*v.x+y*v.y;
}

vec2 vec2::normalize(){
    float l = length();
		
    x /= l;
    y /= l;

    return *this;
}

};
