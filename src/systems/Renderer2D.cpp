#include "Renderer2D.h"

Renderer2D::Renderer2D(const std::shared_ptr<bb::Shader> shader, const std::shared_ptr<bb::Camera> camera){
	spriteMesh = bb::Mesh::createSprite("index0", "vertex0", "texCoord0");
	this->shader = shader;
	this->camera = camera;
}

void Renderer2D::update(const float deltaTime){
	shader->bind();
	shader->enableVertexAttribArrays();

	shader->sendUniform("texture0", 0);

	spriteMesh->indexBuffer->bind();
	spriteMesh->vertex2Buffer->bind();
	spriteMesh->vertex2Buffer->vertexAttribPointer(shader->getAttribLocation("vertex0"), 2, GL_FLOAT, false, 0, 0);
	spriteMesh->texCoordBuffer->bind();
	spriteMesh->texCoordBuffer->vertexAttribPointer(shader->getAttribLocation("texCoord0"), 2, GL_FLOAT, false, 0, 0);

	camera->calculateOrthoMatrix3x3();

	for(auto entity : entities){
		auto texture = std::static_pointer_cast<bb::Texture>(entity->getComponent("Texture"));
		auto position = std::static_pointer_cast<bb::Position2D>(entity->getComponent("Position"));
		auto object = std::static_pointer_cast<bb::Object2D>(entity->getComponent("Object2D"));

		if(texture && position && object && object->visible){
			object->calculateModelMatrix(position);

			texture->bind();
			shader->sendUniform3x3("pm", (camera->orthoMatrix3*object->modelMatrix).getArray());

			glDrawElements(GL_TRIANGLES, spriteMesh->indexBuffer->size(), GL_UNSIGNED_INT, 0);

			texture->unbind();
		}
	}

	shader->disableVertexAttribArrays();
	shader->unbind();
}
