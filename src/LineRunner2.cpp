#include "LineRunner2.h"
#include "states/Intro.h"
#include "states/MainMenu.h"
#include "states/Settings.h"
#include "states/Credits.h"
#include "states/Playing.h"

LineRunner2::LineRunner2(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;
}

void LineRunner2::loadTexture(const std::string &name, const std::string &path){
	auto texture = std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D));

	if(texture->loadTGA(path)){
		textures.insert(std::make_pair(name, texture));
	}
}

void LineRunner2::loadSound(const std::string &name, const std::string &path){
	auto sound = std::shared_ptr<bb::Sound>(new bb::Sound());
	sound->load(path);
	sounds.insert(std::make_pair(name, sound));
}

void LineRunner2::load(){
	// set up shader, camera and listener
	shader = std::shared_ptr<bb::Shader>(new bb::Shader("res/shader/renderer.vertex", "res/shader/renderer.fragment"));
	shader->bindAttrib("vertex0");
	shader->bindAttrib("texCoord0");

	camera = std::shared_ptr<bb::Camera>(new bb::Camera());
	camera->zNear = -1.0f;
	camera->zFar = 1.0f;
	camera->setViewport(wndSize[0], wndSize[1]);

	listener = std::unique_ptr<bb::Listener>(new bb::Listener(bb::vec3()));

	// we render 2D, everywhere...
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	// load assets
	loadTexture("dk_games", "res/textures/dk_games.tga");
	loadTexture("bb_logo", "res/textures/bb_logo.tga");
	loadTexture("logo", "res/textures/logo.tga");

	loadTexture("start", "res/textures/buttons/start.tga");
	loadTexture("settings", "res/textures/buttons/settings.tga");
	loadTexture("credits", "res/textures/buttons/credits.tga");
	loadTexture("exit", "res/textures/buttons/exit.tga");
	loadTexture("back", "res/textures/buttons/back.tga");
	loadTexture("retry", "res/textures/buttons/retry.tga");

	loadTexture("bg", "res/textures/bg/bg.tga");
	loadTexture("bg0", "res/textures/bg/bg0.tga");
	loadTexture("bg1", "res/textures/bg/bg1.tga");
	loadTexture("cloud0", "res/textures/bg/cloud0.tga");
	loadTexture("cloud1", "res/textures/bg/cloud1.tga");
	loadTexture("cloud2", "res/textures/bg/cloud2.tga");
	loadTexture("cloud3", "res/textures/bg/cloud3.tga");

	loadTexture("paused", "res/textures/paused.tga");

	loadSound("button_click", "res/sounds/button_click.wav");
	loadSound("menu_bg", "res/sounds/menu_bg.wav");
	loadSound("ingame", "res/sounds/ingame.wav");

	// background music
	bgMusic = std::unique_ptr<bb::SoundSource>(new bb::SoundSource(sounds["menu_bg"], bb::vec3(), true));

	// font
	auto fontTex = std::shared_ptr<bb::Texture>(new bb::Texture(GL_TEXTURE_2D));
	bb::cfgFile info;

	if(fontTex->loadTGA("res/textures/font.tga", true) && info.read("res/font.cfg")){
		font = std::shared_ptr<bb::Font>(new bb::Font(fontTex, 128));
		font->padding = bb::vec2(5.0f);

		std::list<std::shared_ptr<bb::cfgFile::Node>> chars;
		info.getRoot()->getClasses("Character", chars);

		for(auto c : chars){
			if(c->get("char")->value.size() == 1 && c->get("pos")->value.size() == 2){
				if(c->get("offset")->value.size() != 2){
					font->addCharacter(c->get("char")->toString().at(0), c->get("pos")->toInt(0), c->get("pos")->toInt(1));
				}
				else{
					font->addCharacter(c->get("char")->toString().at(0), c->get("pos")->toInt(0), c->get("pos")->toInt(1), bb::vec2(c->get("offset")->toFloat(0), c->get("offset")->toFloat(1)));
				}
			}
		}
	}

	// entities
	auto texture = textures["bg"];

	auto bg = std::shared_ptr<bb::Entity>(new bb::Entity());
	bg->addComponent("Texture", texture);
	bg->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(), bb::vec2(wndSize[0], wndSize[1]))));
	bg->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	texture = textures["bg0"];

	auto bg0 = std::shared_ptr<bb::Entity>(new bb::Entity("bg"));
	bg0->addComponent("Texture", texture);
	bg0->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(), bb::vec2(wndSize[0], wndSize[1]))));
	bg0->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	texture = textures["bg1"];

	auto bg1 = std::shared_ptr<bb::Entity>(new bb::Entity("bg"));
	bg1->addComponent("Texture", texture);
	bg1->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(wndSize[0]-5, 0), bb::vec2(wndSize[0], wndSize[1]))));
	bg1->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	texture = textures["cloud0"];

	auto cloud0 = std::shared_ptr<bb::Entity>(new bb::Entity("cloud"));
	cloud0->addComponent("Texture", texture);
	cloud0->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(100.0f, wndSize[1]-80-texture->height()), bb::vec2(texture->getSize()))));
	cloud0->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	texture = textures["cloud1"];

	auto cloud1 = std::shared_ptr<bb::Entity>(new bb::Entity("cloud"));
	cloud1->addComponent("Texture", texture);
	cloud1->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(800.0f, wndSize[1]-50-texture->height()), bb::vec2(texture->getSize()))));
	cloud1->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	texture = textures["cloud2"];

	auto cloud2 = std::shared_ptr<bb::Entity>(new bb::Entity("cloud"));
	cloud2->addComponent("Texture", texture);
	cloud2->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(1100.0f, wndSize[1]-60-texture->height()), bb::vec2(texture->getSize()))));
	cloud2->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	texture = textures["cloud3"];

	auto cloud3 = std::shared_ptr<bb::Entity>(new bb::Entity("cloud"));
	cloud3->addComponent("Texture", texture);
	cloud3->addComponent("Position", std::shared_ptr<bb::Position2D>(new bb::Position2D(bb::vec2(2400.0f, wndSize[1]-120-texture->height()), bb::vec2(texture->getSize()))));
	cloud3->addComponent("Object2D", std::shared_ptr<bb::Object2D>(new bb::Object2D()));

	// systems
	bgrenderer = std::unique_ptr<Renderer>(new Renderer(shader, camera));
	bgrenderer->addEntity(bg);
	bgrenderer->addEntity(cloud0);
	bgrenderer->addEntity(cloud1);
	bgrenderer->addEntity(cloud2);
	bgrenderer->addEntity(cloud3);
	bgrenderer->addEntity(bg0);
	bgrenderer->addEntity(bg1);

	background = std::unique_ptr<Background>(new Background(100.0f, 20.0f, wndSize[0]));
	background->addEntity(bg0);
	background->addEntity(bg1);
	background->addEntity(cloud0);
	background->addEntity(cloud1);
	background->addEntity(cloud2);
	background->addEntity(cloud3);

	// add and load states
	stateManager = std::shared_ptr<bb::StateManager>(new bb::StateManager());
	stateManager->add("intro", std::shared_ptr<bb::State>(new Intro(shared_from_this())));
	stateManager->add("mainmenu", std::shared_ptr<bb::State>(new MainMenu(shared_from_this())));
	stateManager->add("settings", std::shared_ptr<bb::State>(new Settings(shared_from_this())));
	stateManager->add("credits", std::shared_ptr<bb::State>(new Credits(shared_from_this())));
	stateManager->add("playing", std::shared_ptr<bb::State>(new Playing(shared_from_this())));
}

void LineRunner2::setViewport(const unsigned int width, const unsigned int height){
	wndSize[0] = width;
	wndSize[1] = height;

	glViewport(0, 0, width, height);
}

void LineRunner2::logic(const float deltaTime){
	stateManager->current()->logic(deltaTime);
}

void LineRunner2::render(const float deltaTime){
	glClear(GL_COLOR_BUFFER_BIT);

	stateManager->current()->render(deltaTime);
}
