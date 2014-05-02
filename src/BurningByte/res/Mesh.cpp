#include "Mesh.h"

namespace bb{

std::shared_ptr<Mesh> Mesh::createSprite(const std::string &index, const std::string &vertex, const std::string &texCoord){
	std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>(new Mesh());

	unsigned int indices[] = {0, 1, 2, 0, 2, 3};
	bb::vec2 vertices[] = {bb::vec2(), bb::vec2(1, 0), bb::vec2(1, 1), bb::vec2(0, 1)};
	bb::vec2 texCoords[] = {bb::vec2(), bb::vec2(1, 0), bb::vec2(1, 1), bb::vec2(0, 1)};

	mesh->indexBuffer = std::unique_ptr<bb::VBO<unsigned int>>(new bb::VBO<unsigned int>(index, GL_ELEMENT_ARRAY_BUFFER));
	mesh->indexBuffer->fill(indices, 6, sizeof(unsigned int), GL_STATIC_DRAW);

	mesh->vertex2Buffer = std::unique_ptr<bb::VBO<bb::vec2>>(new bb::VBO<bb::vec2>(vertex, GL_ARRAY_BUFFER));
	mesh->vertex2Buffer->fill(vertices, 4, sizeof(bb::vec2), GL_STATIC_DRAW);

	mesh->texCoordBuffer = std::unique_ptr<bb::VBO<bb::vec2>>(new bb::VBO<bb::vec2>(texCoord, GL_ARRAY_BUFFER));
	mesh->texCoordBuffer->fill(texCoords, 4, sizeof(bb::vec2), GL_STATIC_DRAW);

	return mesh;
}

Mesh::Mesh(){
	loaded = false;

	indexBuffer = 0;
	vertexBuffer = 0;
	vertex2Buffer = 0;
	texCoordBuffer = 0;

	center = vec3();
	boundingBox[0] = vec3();
	boundingBox[1] = vec3();
	radius = 0;
}

bool Mesh::good(){
	return loaded;
}

bool Mesh::loadPLY(const std::string &path, const std::string &index, const std::string &vertex, const std::string &texCoord, const std::string& normal){
	plyFile ply;

	if(!ply.load(path)){
		return false;
	}

	if(ply.indices.size()){
		indexBuffer = std::shared_ptr<VBO<unsigned int>>(new VBO<unsigned int>(index, GL_ELEMENT_ARRAY_BUFFER));
		indexBuffer->fill(ply.indices, sizeof(unsigned int), GL_STATIC_DRAW);
	}

	if(ply.vertices.size()){
		vertexBuffer = std::shared_ptr<VBO<vec3>>(new VBO<vec3>(vertex, GL_ARRAY_BUFFER));
		vertexBuffer->fill(ply.vertices, sizeof(vec3), GL_STATIC_DRAW);
	}

	if(ply.texCoords.size()){
		texCoordBuffer = std::shared_ptr<VBO<vec2>>(new VBO<vec2>(texCoord, GL_ARRAY_BUFFER));
		texCoordBuffer->fill(ply.texCoords, sizeof(vec2), GL_STATIC_DRAW);
	}

	if(ply.normals.size()){
		normalBuffer = std::shared_ptr<VBO<vec3>>(new VBO<vec3>(normal, GL_ARRAY_BUFFER));
		normalBuffer->fill(ply.normals, sizeof(vec3), GL_STATIC_DRAW);
	}

	// bounding volume
	center = ply.center;
	boundingBox[0] = ply.boundingBox[0];
	boundingBox[1] = ply.boundingBox[1];
	radius = ply.radius;

	return true;
}

};
