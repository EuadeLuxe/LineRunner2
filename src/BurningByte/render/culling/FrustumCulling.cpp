#include "FrustumCulling.h"

namespace bb{

FrustumCulling::FrustumCulling(std::shared_ptr<Camera> camera){
	this->camera = camera;
}

FrustumCulling::FrustumCulling(){
	camera = 0;
}

void FrustumCulling::update(const float deltaTime){
	if(camera){
		std::shared_ptr<Position3D> position = 0;
		std::shared_ptr<Mesh> mesh = 0;

		frustum.getFrustum(camera->projectionMatrix*camera->viewMatrix);

		for(auto entity : entities){
			position = std::static_pointer_cast<Position3D>(entity->getComponent("Positionable"));
			mesh = std::static_pointer_cast<Mesh>(entity->getComponent("Mesh"));

			if(position && mesh){
				if(frustum.sphereIn(position->position, mesh->radius)){
					position->visible = true;
				}
				else{
					position->visible = false;
				}
			}
		}
	}
}

void FrustumCulling::Frustum::getFrustum(const mat4 &m){
	m_frustum[0].getLeft(m);
	m_frustum[1].getRight(m);
	m_frustum[2].getTop(m);
	m_frustum[3].getBottom(m);
	m_frustum[4].getNear(m);
	m_frustum[5].getFar(m);
}

bool FrustumCulling::Frustum::pointIn(const vec3 &v){
	for(unsigned int i = 0; i < 6; i++){
		if(!m_frustum[i].pointIn(v)){
			return false;
		}
	}

	return true;
}

bool FrustumCulling::Frustum::sphereIn(const vec3 &v, const float r){
	for(unsigned int i = 0; i < 6; i++){
		if(!m_frustum[i].sphereIn(v, r)){
			return false;
		}
	}

	return true;
}

bool FrustumCulling::Frustum::boxIn(const vec3 &min, const vec3 &max){
	for(unsigned int i = 0; i < 6; i++){
		if(!m_frustum[i].boxIn(min, max)){
			return false;
		}
	}

	return true;
}

};
