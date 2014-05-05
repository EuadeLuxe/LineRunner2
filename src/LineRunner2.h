#ifndef LINERUNNER2_H_
#define LINERUNNER2_H_

#include <memory>
#include <map>
#include <GL/gl3w.h>
#include "BurningByte/res/files/cfgFile.h"
#include "BurningByte/state/StateManager.h"
#include "BurningByte/render/Camera.h"
#include "BurningByte/res/Shader.h"
#include "BurningByte/res/Texture.h"
#include "BurningByte/res/buffer/Sound.h"
#include "BurningByte/sound/Listener.h"
#include "BurningByte/sound/SoundSource.h"
#include "BurningByte/input/Input.h"
#include "BurningByte/input/Device.h"
#include "systems/Renderer.h"
#include "systems/Background.h"

class LineRunner2:public std::enable_shared_from_this<LineRunner2>{
	private:
		std::unique_ptr<bb::Listener> listener;

		void loadTexture(const std::string &name, const std::string &path);

	public:
		unsigned int wndSize[2];

		std::shared_ptr<bb::StateManager> stateManager;
		std::shared_ptr<bb::Input> input;
		std::shared_ptr<bb::Shader> shader;
		std::shared_ptr<bb::Camera> camera;

		std::map<std::string, std::shared_ptr<bb::Texture>> textures;
		std::unique_ptr<Renderer> bgrenderer;
		std::unique_ptr<Background> background;

		LineRunner2(const unsigned int width, const unsigned int height);

		void load();

		void setViewport(const unsigned int width, const unsigned int height);

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
