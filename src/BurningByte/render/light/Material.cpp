#include "Material.h"

namespace bb{

Material::Material(){
	emissive = vec4();
	diffuse = vec4();
	specular = vec4();
	shininess = 0;
}

Material::Material(const vec4 &emissive, const vec4 &diffuse, const vec4 &specular, const float shininess){
	this->emissive = emissive;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

};
