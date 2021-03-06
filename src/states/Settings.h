#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <memory>
#include <string>
#include "../BurningByte/render/gui/Text.h"
#include "../BurningByte/res/files/cfgFile.h"
#include "../LineRunner2.h"
#include "../systems/Renderer.h"
#include "../systems/TextRenderer.h"
#include "../entities/Button.h"
#include "../entities/Checkbox.h"
#include "../gui/SwitchStateButton.h"
#include "../gui/SaveButton.h"
#include "../gui/FsCheckbox.h"
#include "../gui/ResolutionButton.h"
#include "../gui/SetKeyButton.h"

/*
 * EuadeLuxe
 * 10/05/2014 12:43
 * Moved resolutions declaration into .cpp file.
 */

class Settings:public std::enable_shared_from_this<Settings>, public bb::State, public bb::Device{
	private:
		std::shared_ptr<LineRunner2> game;
		std::shared_ptr<bb::Input> input;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<TextRenderer> textRenderer;

		std::shared_ptr<SwitchStateButton> backButton;
		std::shared_ptr<SaveButton> saveButton;
		std::shared_ptr<FsCheckbox> fsCheckbox;
		std::shared_ptr<ResolutionButton> nextButton, previousButton;
		std::shared_ptr<SetKeyButton> jumpButton, rollButton, pauseButton, retryButton;

		static const unsigned int maxResolutions;
		static const unsigned int resolutions[6][2];

		int resolution;
		SetKeyButton::CONTROL acceptKey;

	public:
		static const std::string saveFile;

		Settings(const std::shared_ptr<LineRunner2> game);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);

		void keyTyped(unsigned char c, int x, int y);

		void nextRes();
		void previousRes();
		void setButton(const SetKeyButton::CONTROL control);
		void save();
};

#endif
