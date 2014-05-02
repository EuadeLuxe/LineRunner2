/*
 * FrustumCulling
 * Author: Marvin Blum
 * Last Update: 2014/03/31 18:00
 * */

#ifndef FRUSTUMCULLING_H_
#define FRUSTUMCULLING_H_

#include "../../System.h"
#include "../Camera.h"
#include "../util/Position3D.h"
#include "../../res/Mesh.h"

namespace bb{

class FrustumCulling:public System{
	public:
		class Frustum{
			public:
				struct frustum{
					vec3 n;
					float d;

					frustum():
						n(vec3()),
						d(0.0f){}

					void getLeft(const mat4 &m){
						n.x = m.values[3]+m.values[0];
						n.y = m.values[7]+m.values[4];
						n.z = m.values[11]+m.values[8];
						d = m.values[15]+m.values[12];

						normalize();
					}

					void getRight(const mat4 &m){
						n.x = m.values[3]-m.values[0];
						n.y = m.values[7]-m.values[4];
						n.z = m.values[11]-m.values[8];
						d = m.values[15]-m.values[12];

						normalize();
					}

					void getBottom(const mat4 &m){
						n.x = m.values[3]+m.values[1];
						n.y = m.values[7]+m.values[5];
						n.z = m.values[11]+m.values[9];
						d = m.values[15]+m.values[13];

						normalize();
					}

					void getTop(const mat4 &m){
						n.x = m.values[3]-m.values[1];
						n.y = m.values[7]-m.values[5];
						n.z = m.values[11]-m.values[9];
						d = m.values[15]-m.values[13];

						normalize();
					}

					void getNear(const mat4 &m){
						n.x = m.values[3]+m.values[2];
						n.y = m.values[7]+m.values[6];
						n.z = m.values[11]+m.values[10];
						d = m.values[15]+m.values[14];

						normalize();
					}

					void getFar(const mat4 &m){
						n.x = m.values[3]-m.values[2];
						n.y = m.values[7]-m.values[6];
						n.z = m.values[11]-m.values[10];
						d = m.values[15]-m.values[14];

						normalize();
					}

					void normalize(){
						float l = n.length();

						n.x /= l;
						n.y /= l;
						n.z /= l;
						d /= l;
					}

					bool pointIn(const vec3 &v){
						if(n.x*v.x+n.y*v.y+n.z*v.z+d <= 0){
							return false;
						}

						return true;
					}

					bool sphereIn(const vec3 &v, const float r){
						if(n.x*v.x+n.y*v.y+n.z*v.z+d <= -r){
							return false;
						}

						return true;
					}

					bool boxIn(const vec3 &min, const vec3 &max){
						vec3 test;

						if(n.x < 0){
							test.x = min.x;
						}
						else{
							test.x = max.x;
						}

						if(n.y < 0){
							test.y = min.y;
						}
						else{
							test.y = max.y;
						}

						if(n.z < 0){
							test.z = min.z;
						}
						else{
							test.z = max.z;
						}

						return pointIn(test);
					}
				};

				frustum m_frustum[6];

				void getFrustum(const mat4 &m);

				bool pointIn(const vec3 &v);
				bool sphereIn(const vec3 &v, const float r);
				bool boxIn(const vec3 &min, const vec3 &max);
		};

	private:
		Frustum frustum;

	public:
		std::shared_ptr<Camera> camera;

		FrustumCulling(std::shared_ptr<Camera> camera);
		FrustumCulling();

		void update(const float deltaTime);
};

};

#endif
