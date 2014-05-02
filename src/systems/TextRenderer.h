#ifndef TEXTRENDERER_H_
#define TEXTRENDERER_H_

#include <memory>
#include "../BurningByte/System.h"
#include "../BurningByte/res/Shader.h"
#include "../BurningByte/render/Camera.h"
#include "../BurningByte/res/Mesh.h"
#include "../BurningByte/res/Texture.h"
#include "../BurningByte/render/util/Position2D.h"
#include "../BurningByte/render/util/Object2D.h"

class TextRenderer:public bb::System{
	private:
		std::shared_ptr<bb::Texture> font;

	public:
		std::shared_ptr<bb::Shader> shader;
		std::shared_ptr<bb::Camera> camera;

		TextRenderer(const std::shared_ptr<bb::Shader> shader, const std::shared_ptr<bb::Camera> camera, const std::shared_ptr<bb::Texture> font);

		void update(const float deltaTime);
};

#endif
