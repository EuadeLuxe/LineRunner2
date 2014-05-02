#include "Text.h"

namespace bb{

Text::Text():Entity(){
	size = vec2();
}

Text::Text(const std::string &name):Entity(name){
	size = vec2();
}

void Text::setText(const std::string &text){
	std::shared_ptr<Font> font = std::static_pointer_cast<Font>(getComponent("Font"));
	std::shared_ptr<Mesh> mesh = std::static_pointer_cast<Mesh>(getComponent("Mesh"));

	if(!font || !mesh){
		return;
	}

	this->text = text;
	size = vec2(0.0f, -1.0f);

	// generate buffer
	std::vector<unsigned int> indices;
	std::vector<vec2> vertices;
	std::vector<vec2> texCoords;

	indices.resize(text.length()*6);
	vertices.resize(text.length()*4);
	texCoords.resize(text.length()*4);

	vec2 offset = vec2();
	Font::character c;
	unsigned int index = 0;

	for(unsigned int i = 0; i < text.length()*6; i += 6){
		// indices
		indices[i] = index;
		indices[i+1] = index+1;
		indices[i+2] = index+2;
		indices[i+3] = index;
		indices[i+4] = index+2;
		indices[i+5] = index+3;

		index += 4;
	}

	index = 0;

	for(unsigned int i = 0; i < text.length()*4; i += 4){
		// special characters
		if(text.at(index) == ' '){ // space
			offset.x += font->spaceBar+font->space.x;
			index++;

			continue;
		}
		else if(text.at(index) == '\t'){ // tab
			offset.x += font->tab+font->space.x;
			index++;

			continue;
		}
		else if(text.at(index) == '\n'){ // new line
			offset.y -= 1.0f+font->space.y;
			offset.x = 0.0f;
			index++;

			continue;
		}

		c = font->getCharacter(text.at(index));

		// vertices
		vertices[i] = vec2(offset.x+c.offset.x, offset.y+c.offset.y);
		vertices[i+1] = vec2(offset.x+c.size.x+c.offset.x, offset.y+c.offset.y);
		vertices[i+2] = vec2(offset.x+c.size.x+c.offset.x, offset.y+c.size.y+c.offset.y);
		vertices[i+3] = vec2(offset.x+c.offset.x, offset.y+c.size.y+c.offset.y);

		// texture coordinates
		texCoords[i] = vec2(c.min.x, c.min.y);
		texCoords[i+1] = vec2(c.max.x, c.min.y);
		texCoords[i+2] = vec2(c.max.x, c.max.y);
		texCoords[i+3] = vec2(c.min.x, c.max.y);

		// string size
		if(offset.x > size.x){
			size.x = offset.x;
		}

		if(offset.y-1.0f < size.y){
			size.y = offset.y-1.0f;
		}

		offset.x += c.size.x+font->space.x;
		index++;
	}

	this->size = size;
	this->size.abs();

	std::shared_ptr<VBO<unsigned int>> indexBuffer = std::shared_ptr<VBO<unsigned int>>(new VBO<unsigned int>("index0", GL_ELEMENT_ARRAY_BUFFER));
	indexBuffer->fill(indices, sizeof(unsigned int), GL_STATIC_DRAW);

	std::shared_ptr<VBO<vec2>> vertexBuffer = std::shared_ptr<VBO<vec2>>(new VBO<vec2>("vertex0", GL_ARRAY_BUFFER));
	vertexBuffer->fill(vertices, sizeof(vec2), GL_STATIC_DRAW);

	std::shared_ptr<VBO<vec2>> texCoordBuffer = std::shared_ptr<VBO<vec2>>(new VBO<vec2>("texCoord0", GL_ARRAY_BUFFER));
	texCoordBuffer->fill(texCoords, sizeof(vec2), GL_STATIC_DRAW);

	mesh->indexBuffer = indexBuffer;
	mesh->vertex2Buffer = vertexBuffer;
	mesh->texCoordBuffer = texCoordBuffer;
}

};
