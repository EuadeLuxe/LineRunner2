#include "TextRenderer.h"

TextRenderer::TextRenderer(const std::shared_ptr<bb::Shader> shader, const std::shared_ptr<bb::Camera> camera, const std::shared_ptr<bb::Texture> font){
	this->shader = shader;
	this->camera = camera;
	this->font = font;
}

void TextRenderer::update(const float deltaTime){
	shader->bind();
	shader->enableVertexAttribArrays();

	shader->sendUniform("texture0", 0);

	camera->calculateOrthoMatrix3x3();

	font->bind();

	for(auto entity : entities){
		auto mesh = std::static_pointer_cast<bb::Mesh>(entity->getComponent("Mesh"));
		auto position = std::static_pointer_cast<bb::Position2D>(entity->getComponent("Position"));
		auto object = std::static_pointer_cast<bb::Object2D>(entity->getComponent("Object2D"));

		if(position && object && object->visible){
			object->calculateModelMatrix(position);

			shader->sendUniform3x3("pm", (camera->orthoMatrix3*object->modelMatrix).getArray());

			mesh->indexBuffer->bind();
			mesh->vertex2Buffer->bind();
			mesh->vertex2Buffer->vertexAttribPointer(shader->getAttribLocation("vertex0"), 2, GL_FLOAT, false, 0, 0);
			mesh->texCoordBuffer->bind();
			mesh->texCoordBuffer->vertexAttribPointer(shader->getAttribLocation("texCoord0"), 2, GL_FLOAT, false, 0, 0);

			glDrawElements(GL_TRIANGLES, mesh->indexBuffer->size(), GL_UNSIGNED_INT, 0);
		}
	}

	font->unbind();

	shader->disableVertexAttribArrays();
	shader->unbind();
}
