#include "Renderer.h"

Renderer::Renderer(const std::shared_ptr<bb::Shader> shader, const std::shared_ptr<bb::Camera> camera){
	spriteMesh = bb::Mesh::createSprite("index0", "vertex0", "texCoord0");
	this->shader = shader;
	this->camera = camera;
}

void Renderer::update(const float deltaTime){
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
		auto duration = std::static_pointer_cast<Duration>(entity->getComponent("Duration"));
		auto animation = std::static_pointer_cast<Animation>(entity->getComponent("Animation"));

		if(texture && position && object && object->visible){
			object->calculateModelMatrix(position);

			texture->bind();
			shader->sendUniform3x3("pm", (camera->orthoMatrix3*object->modelMatrix).getArray());
			shader->sendUniform("alpha", 1.0f);
			shader->sendUniform("texScale", 1.0f, 1.0f);
			shader->sendUniform("texOffset", 0.0f, 0.0f);

			if(duration){
				shader->sendUniform("alpha", duration->alpha);
			}

			if(animation && animation->current()){
				shader->sendUniform("texScale", animation->current()->scale.x, animation->current()->scale.y);
				shader->sendUniform("texOffset", animation->current()->offset.x, animation->current()->offset.y);
			}

			glDrawElements(GL_TRIANGLES, spriteMesh->indexBuffer->size(), GL_UNSIGNED_INT, 0);

			texture->unbind();
		}
	}

	shader->disableVertexAttribArrays();
	shader->unbind();
}
