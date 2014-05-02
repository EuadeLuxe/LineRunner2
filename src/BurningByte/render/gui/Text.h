/*
 * Text
 * Author: Marvin Blum
 * Last Update: 2014/04/08 15:40
 * */

#ifndef TEXT_H_
#define TEXT_H_

#include <string>
#include <vector>
#include <memory>
#include "../../Entity.h"
#include "../../res/Mesh.h"
#include "../../res/Font.h"

namespace bb{

class Text:public Entity{
	public:
		std::string text;
		vec2 size;

		Text();
		Text(const std::string &name);

		void setText(const std::string &text);
};

};

#endif
