#ifndef BGRENDERER_H_
#define BGRENDERER_H_

#include <memory>
#include "../BurningByte/System.h"
#include "../BurningByte/res/Shader.h"
#include "../BurningByte/render/Camera.h"
#include "../BurningByte/res/Mesh.h"
#include "../BurningByte/res/Texture.h"
#include "../BurningByte/render/util/Position2D.h"
#include "../BurningByte/render/util/Object2D.h"
#include "../components/Duration.h"

class bgRenderer:public bb::System{
	private:
		std::shared_ptr<bb::Mesh> spriteMesh;

	public:
		std::shared_ptr<bb::Shader> shader;
		std::shared_ptr<bb::Camera> camera;

		bgRenderer(const std::shared_ptr<bb::Shader> shader, const std::shared_ptr<bb::Camera> camera);

		void update(const float deltaTime);
};

#endif
