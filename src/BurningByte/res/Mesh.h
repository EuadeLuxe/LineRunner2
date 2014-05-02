/*
 * Mesh
 * Author: Marvin Blum
 * Last Update: 2014/03/31 17:52
 * */

#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <memory>
#include "../Component.h"
#include "buffer/VBO.h"
#include "files/plyFile.h"
#include "../math/Vector.h"

namespace bb{

class Mesh:public Component{
	private:
		bool loaded; // for file loading

	public:
		std::shared_ptr<VBO<unsigned int>> indexBuffer;
		std::shared_ptr<VBO<vec3>> vertexBuffer, normalBuffer;
		std::shared_ptr<VBO<vec2>> vertex2Buffer, texCoordBuffer;

		vec3 center, boundingBox[2];
		float radius;

		static std::shared_ptr<Mesh> createSprite(const std::string &index, const std::string &vertex, const std::string &texCoord); // 2D plane, pass buffer names

		Mesh();

		bool good();

		bool loadPLY(const std::string &path, const std::string &index = "index0", const std::string &vertex = "vertex0", const std::string &texCoord = "texCoord0", const std::string& normal = "normal0");
};

};

#endif
