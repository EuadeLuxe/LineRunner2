#include "Font.h"

namespace bb{

Font::Font(){
	texture = 0;
	partSize = 0.0f;
	padding = vec2(2.0f);
	space = vec2();
	spaceBar = 0.2f;
	tab = 0.8f;
}

Font::Font(std::shared_ptr<Texture> texture, const unsigned int partSize){
	this->texture = texture;
	this->partSize = partSize;
	padding = vec2(2.0f);
	space = vec2();
	spaceBar = 0.2f;
	tab = 0.8f;
}

void Font::addCharacter(const unsigned char letter, unsigned int x, unsigned int y, const vec2 &offset, bool cutSpaces){
	vec2 min = vec2(float(x*partSize), float(y*partSize));
	vec2 max = vec2(float(x*partSize+partSize), float(y*partSize+partSize));
	vec2 size = vec2(float(texture->width()), float(texture->height()));

	if(cutSpaces && texture && texture->data.size() && texture->getBytesPerPixel() == 4){
		unsigned char* data = &texture->data[0];
		float width = float(texture->width());
		min = max;
		max = vec2(float(x*partSize), float(y*partSize));

		for(float ty = float(y*partSize); ty < float(y*partSize+partSize); ty++){
			for(float tx = float(x*partSize); tx < float(x*partSize+partSize); tx++){
				unsigned int i = ty*width*4.0f+tx*4.0f+3;

				if(int(data[i]) >= 100){
					if(tx < min.x){
						min.x = tx;
					}
					else if(tx > max.x){
						max.x = tx;
					}

					if(ty < min.y){
						min.y = ty;
					}
					else if(ty > max.y){
						max.y = ty;
					}
				}
			}
		}
	}

	min -= padding;
	max += padding;

	letters[letter] = character();
	letters[letter].min = (min)/size;
	letters[letter].max = (max)/size;
	letters[letter].size = (max-min)/float(partSize);
	letters[letter].offset = offset;
}

void Font::removeCharacter(const unsigned char letter){
	letters.erase(letter);
}

Font::character Font::getCharacter(const unsigned char letter){
	if(letters.find(letter) != letters.end()){
		return letters.at(letter);
	}

	return character();
}

};
