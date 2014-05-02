/*
 * Font
 * Author: Marvin Blum
 * Last Update: 2014/03/19 17:47
 * */

#ifndef FONT_H_
#define FONT_H_

#include <memory>
#include <map>
#include "../math/Vector.h"
#include "../Component.h"
#include "Texture.h"

namespace bb{

class Font:public Component{
	public:
		struct character{
			vec2 min, max; // UV texture coordinates
			vec2 size, offset;
		};

		std::shared_ptr<Texture> texture;
		std::map<const unsigned char, character> letters;

		unsigned int partSize; // in pixel
		vec2 space, padding;
		float spaceBar, tab;

		Font();
		Font(std::shared_ptr<Texture> texture, const unsigned int partSize);

		void addCharacter(const unsigned char letter, unsigned int x, unsigned int y, const vec2 &offset = vec2(), bool cutSpaces = true); // lower left corner
		void removeCharacter(const unsigned char letter);

		character getCharacter(const unsigned char letter);
};

};

#endif
