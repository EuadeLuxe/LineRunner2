#include "FXAA.h"

namespace bb{

const float FXAA::NONE = 0.0f;
const float FXAA::LOW = 2.0f;
const float FXAA::MID = 4.0f;
const float FXAA::HIGH = 8.0f;

std::shared_ptr<Texture> FXAA::createScreen(const unsigned int width, const unsigned int height){
	auto screen = std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D));
	screen->bind();
	screen->texture2D(0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	screen->parameterf(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	screen->parameterf(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	screen->parameterf(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	screen->parameterf(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	screen->unbind();

	return screen;
}

FXAA::FXAA(const std::shared_ptr<Texture> screen){
	shader = std::unique_ptr<bb::Shader>(new bb::Shader("src/BurningByte/shader/fxaa.vertex", "src/BurningByte/shader/fxaa.fragment"));
	shader->bindAttrib("vertex0");

	mesh = Mesh::createSprite("index0", "vertex0", "");
	mesh->texCoordBuffer->drop();

	this->screen = screen;
	quality = 0.0f;
}

FXAA::FXAA(const unsigned int width, const unsigned int height):FXAA(createScreen(width, height)){

}

void FXAA::render(){
	shader->bind();
	shader->enableVertexAttribArrays();

	screen->bind();

	shader->sendUniform("quality", quality);
	shader->sendUniform("screen", 0);
	shader->sendUniform("fboSize", float(screen->width()), float(screen->height()));

	mesh->indexBuffer->bind();
	mesh->vertex2Buffer->bind();
	mesh->vertex2Buffer->vertexAttribPointer(shader->getAttribLocation("vertex0"), 2, GL_FLOAT, false, 0, 0);

	glDrawElements(GL_TRIANGLES, mesh->indexBuffer->size(), GL_UNSIGNED_INT, 0);

	screen->unbind();

	shader->disableVertexAttribArrays();
	shader->unbind();
}

void FXAA::setQuality(const float quality){
	this->quality = quality;
}

};
