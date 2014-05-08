#include "Settings.h"

const unsigned int Settings::maxResolutions = 6;
const std::string saveFile = "settings.cfg";

Settings::Settings(const std::shared_ptr<LineRunner2> game){
	this->game = game;
	resolution = 0;

	unsigned int i = 0;

	for(auto res : resolutions){
		if(game->wndSize[0] == res[0] && game->wndSize[1] == res[1]){
			resolution = i;
			break;
		}

		i++;
	}
}

void Settings::load(){
	// read settings (if possible)
	bool check = false;

	bb::cfgFile file;

	if(file.read("settings.cfg")){
		auto fs = file.getRoot()->get("fullscreen");

		if(!fs->getName().empty()){
			check = fs->toInt();
		}
	}

	//// entities
	backButton = std::shared_ptr<SwitchStateButton>(new SwitchStateButton(game->stateManager, "mainmenu"));
	backButton->addSound(game->sounds["button_click"]);

	saveButton = std::shared_ptr<SaveButton>(new SaveButton(shared_from_this()));
	saveButton->addSound(game->sounds["button_click"]);

	nextButton = std::shared_ptr<ResolutionButton>(new ResolutionButton(shared_from_this(), ResolutionButton::ACTION::NEXT));
	previousButton = std::shared_ptr<ResolutionButton>(new ResolutionButton(shared_from_this(), ResolutionButton::ACTION::PREVIOUS));

	fsCheckbox = std::shared_ptr<FsCheckbox>(new FsCheckbox(game->textures["checkbox_checked"], game->textures["checkbox"]));

	auto texture = game->textures["logo"];
	auto obj = std::shared_ptr<bb::Object2D>(new bb::Object2D());

	auto logo = std::shared_ptr<bb::Entity>(new bb::Entity());
	logo->addComponent("Texture", texture);
	logo->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(60, game->wndSize[1]-texture->height()/2-60), bb::vec2(400.0f, 150.0f))));
	logo->addComponent("Object2D", obj);

	texture = game->textures["back"];

	auto back = std::shared_ptr<Button>(new Button("back", backButton));
	back->addComponent("Texture", texture);
	back->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+222, 60), texture->getSize())));
	back->addComponent("Object2D", obj);

	texture = game->textures["save"];

	auto save = std::shared_ptr<Button>(new Button("save", saveButton));
	save->addComponent("Texture", texture);
	save->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]-400+148, 60), texture->getSize())));
	save->addComponent("Object2D", obj);

	if(check){
		texture = game->textures["checkbox_checked"];
	}
	else{
		texture = game->textures["checkbox"];
	}

	auto fs = std::shared_ptr<Checkbox>(new Checkbox("checkbox", fsCheckbox, check));
	fs->addComponent("Texture", texture);
	fs->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]/2, game->wndSize[1]/2+190), texture->getSize())));
	fs->addComponent("Object2D", obj);

	auto resolutionSize = std::shared_ptr<bb::Text>(new bb::Text("resolution"));
	resolutionSize->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]/2+50, game->wndSize[1]/2+140), bb::vec2(30.0f))));
	resolutionSize->addComponent("Object2D", obj);
	resolutionSize->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	resolutionSize->addComponent("Font", game->font);
	resolutionSize->setText(std::to_string(resolutions[resolution][0])+"x"+std::to_string(resolutions[resolution][1]));

	texture = game->textures["right"];

	auto next = std::shared_ptr<Button>(new Button(nextButton));
	next->addComponent("Texture", texture);
	next->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]/2+200, game->wndSize[1]/2+130), texture->getSize())));
	next->addComponent("Object2D", obj);

	texture = game->textures["left"];

	auto previous = std::shared_ptr<Button>(new Button(previousButton));
	previous->addComponent("Texture", texture);
	previous->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(game->wndSize[0]/2, game->wndSize[1]/2+130), texture->getSize())));
	previous->addComponent("Object2D", obj);

	auto title = std::shared_ptr<bb::Text>(new bb::Text());
	title->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(140, game->wndSize[1]-240), bb::vec2(60.0f))));
	title->addComponent("Object2D", obj);
	title->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	title->addComponent("Font", game->font);
	title->setText("Settings");

	auto fullscreen = std::shared_ptr<bb::Text>(new bb::Text());
	fullscreen->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(200, game->wndSize[1]/2+200), bb::vec2(30.0f))));
	fullscreen->addComponent("Object2D", obj);
	fullscreen->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	fullscreen->addComponent("Font", game->font);
	fullscreen->setText("Fullscreen:");

	auto resolutionText = std::shared_ptr<bb::Text>(new bb::Text());
	resolutionText->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(200, game->wndSize[1]/2+140), bb::vec2(30.0f))));
	resolutionText->addComponent("Object2D", obj);
	resolutionText->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	resolutionText->addComponent("Font", game->font);
	resolutionText->setText("Resolution:");

	auto jump = std::shared_ptr<bb::Text>(new bb::Text());
	jump->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(200, game->wndSize[1]/2+80), bb::vec2(30.0f))));
	jump->addComponent("Object2D", obj);
	jump->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	jump->addComponent("Font", game->font);
	jump->setText("Jump:");

	auto roll = std::shared_ptr<bb::Text>(new bb::Text());
	roll->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(200, game->wndSize[1]/2+20), bb::vec2(30.0f))));
	roll->addComponent("Object2D", obj);
	roll->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	roll->addComponent("Font", game->font);
	roll->setText("Roll:");

	auto pause = std::shared_ptr<bb::Text>(new bb::Text());
	pause->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(200, game->wndSize[1]/2-40), bb::vec2(30.0f))));
	pause->addComponent("Object2D", obj);
	pause->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	pause->addComponent("Font", game->font);
	pause->setText("Pause:");

	auto info = std::shared_ptr<bb::Text>(new bb::Text());
	info->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(200, game->wndSize[1]/2-160), bb::vec2(30.0f))));
	info->addComponent("Object2D", obj);
	info->addComponent("Mesh", std::shared_ptr<bb::Mesh>(new bb::Mesh()));
	info->addComponent("Font", game->font);
	info->setText("Left-click on a key in order to bind it to another key.\nYou have to restart the game in order to adopt the settings.");

	//// systems
	input = std::shared_ptr<bb::Input>(new bb::Input());
	game->input = input;

	game->input->add(back);
	game->input->add(save);
	game->input->add(fs);
	game->input->add(next);
	game->input->add(previous);

	renderer = std::unique_ptr<Renderer>(new Renderer(game->shader, game->camera));

	renderer->addEntity(logo);
	renderer->addEntity(back);
	renderer->addEntity(save);
	renderer->addEntity(fs);
	renderer->addEntity(next);
	renderer->addEntity(previous);

	textRenderer = std::unique_ptr<TextRenderer>(new TextRenderer(game->shader, game->camera, game->font->texture));

	textRenderer->addEntity(title);
	textRenderer->addEntity(fullscreen);
	textRenderer->addEntity(resolutionText);
	textRenderer->addEntity(jump);
	textRenderer->addEntity(roll);
	textRenderer->addEntity(pause);
	textRenderer->addEntity(info);
	textRenderer->addEntity(resolutionSize);

	hasStarted = true;
}

void Settings::pause(){

}

void Settings::resume(){
	game->input = input;
}

void Settings::logic(const float deltaTime){
	if(hasStarted && deltaTime < 0.1){
		game->background->update(deltaTime);
	}
}

void Settings::render(const float deltaTime){
	if(hasStarted){
		game->bgrenderer->update(deltaTime);
		renderer->update(deltaTime);
		textRenderer->update(deltaTime);
	}
}

void Settings::nextRes(){
	do{
		if(resolution++ == maxResolutions-1){
			resolution = 0;
		}
	}while(resolutions[resolution][0] > game->wndMaxRes[0] || resolutions[resolution][1] > game->wndMaxRes[1]);

	auto resolutionSize = std::static_pointer_cast<bb::Text>(textRenderer->getEntity("resolution"));

	if(resolutionSize){
		resolutionSize->setText(std::to_string(resolutions[resolution][0])+"x"+std::to_string(resolutions[resolution][1]));
	}
}

void Settings::previousRes(){
	do{
		if(resolution-- == -1){
			resolution = maxResolutions-1;
		}
	}while(resolutions[resolution][0] > game->wndMaxRes[0] || resolutions[resolution][1] > game->wndMaxRes[1]);

	auto resolutionSize = std::static_pointer_cast<bb::Text>(textRenderer->getEntity("resolution"));

	if(resolutionSize){
		resolutionSize->setText(std::to_string(resolutions[resolution][0])+"x"+std::to_string(resolutions[resolution][1]));
	}
}

void Settings::save(){
	// get GUI status
	auto checkbox = std::static_pointer_cast<Checkbox>(renderer->getEntity("checkbox"));

	// save
	bb::cfgFile file;

	if(!file.read("settings.cfg")){
		return;
	}

	auto root = file.getRoot();

	root->set("fullscreen", checkbox->checked());

	auto size = root->get("wndSize");

	if(!size->getName().empty()){
		size->value.clear();
	}

	size = root->set("wndSize", int(resolutions[resolution][0]));
	size->value.push_back(std::to_string(resolutions[resolution][1]));

	file.write("settings.cfg");
}
