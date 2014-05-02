#include "LightSource.h"

namespace bb {

LightSource::LightSource(const vec3 &position, const vec3 &direction, const vec4 &diffuse, const vec4 &specular, const float cA, const float lA, const float qA, const float cutoff, const float spot){
	this->position = position;
	this->diffuse = direction;
	this->diffuse = diffuse;
	this->specular = specular;

	constantAttenuation = cA;
	linearAttenuation = lA;
	quadraticAttenuation = qA;

	this->cutoff = cutoff;
	this->spot = spot;
}

LightSource::LightSource(const vec3 &position, const vec4 &diffuse, const vec4 &specular, const float cA, const float lA, const float qA){
	this->position = position;
	this->diffuse = vec3();
	this->diffuse = diffuse;
	this->specular = specular;

	constantAttenuation = cA;
	linearAttenuation = lA;
	quadraticAttenuation = qA;

	this->cutoff = 0.0f;
	this->spot = 0.0f;
}

LightSource::LightSource(const vec3 &direction, const vec4 &diffuse, const vec4 &specular){
	this->position = vec3();
	this->diffuse = direction;
	this->diffuse = diffuse;
	this->specular = specular;

	constantAttenuation = 0.0f;
	linearAttenuation = 0.0f;
	quadraticAttenuation = 0.0f;

	this->cutoff = 0.0f;
	this->spot = 0.0f;
}

LightSource::LightSource(){
	this->position = vec3();
	this->diffuse = vec3();
	this->diffuse = vec3();
	this->specular = vec4();

	constantAttenuation = 0.0f;
	linearAttenuation = 0.0f;
	quadraticAttenuation = 0.0f;

	this->cutoff = 0.0f;
	this->spot = 0.0f;
}

};
