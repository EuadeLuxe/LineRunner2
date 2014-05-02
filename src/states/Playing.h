#ifndef PLAYING_H_
#define PLAYING_H_

#include <memory>
#include <math.h>
#include <iostream>
#include <GL/gl3w.h>
#include "../BurningByte/state/State.h"
#include "../BurningByte/res/Shader.h"
#include "../BurningByte/render/Camera.h"
#include "../BurningByte/res/Texture.h"
#include "../BurningByte/res/buffer/Sound.h"
#include "../BurningByte/sound/Listener.h"
#include "../BurningByte/sound/SoundSource.h"
#include "../systems/Renderer2D.h"

class Playing:public bb::State{
	private:
		unsigned int wndSize[2];

	public:
		std::vector<std::shared_ptr<bb::Texture>> textures;
		std::vector<std::shared_ptr<bb::Sound>> sounds;

		std::shared_ptr<bb::Camera> camera;
		std::unique_ptr<bb::Listener> listener;
		std::unique_ptr<Renderer2D> renderer2D;

		Playing(const unsigned int width, const unsigned int height);

		void setViewport(const unsigned int wndWidth, const unsigned int wndHeight);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
