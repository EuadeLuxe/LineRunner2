/*
 * FXAA
 * Author: Marvin Blum
 * Last Update: 2014/05/05 14:59
 * */

#ifndef FXAA_H_
#define FXAA_H_

#include <memory>
#include <GL/gl3w.h>
#include "../../res/Shader.h"
#include "../../res/Mesh.h"
#include "../../res/Texture.h"

namespace bb{

class FXAA{
	private:
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Mesh> mesh;
		float quality; // default 0 = no AA

	public:
		std::shared_ptr<Texture> screen;

		static const float NONE;
		static const float LOW;
		static const float MID;
		static const float HIGH;

		static std::shared_ptr<Texture> createScreen(const unsigned int width, const unsigned int height);

		FXAA(const std::shared_ptr<Texture> screen, const std::shared_ptr<Shader> shader);
		FXAA(const unsigned int width, const unsigned int height, const std::shared_ptr<Shader> shader);

		void render();

		void setQuality(const float quality);
};

};

#endif
