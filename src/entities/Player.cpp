#include "Player.h"

Player::Player(const std::string &name, const unsigned char jumpKey, const unsigned char rollKey):Entity(name){
	jump = false;
	jumping = false;
	roll = false;
	rolling = false;
	this->jumpKey = std::toupper(jumpKey);
	this->rollKey = std::toupper(rollKey);
}

void Player::keyPressed(unsigned char key, int x, int y){
	unsigned char c = std::toupper(key);

	if(c == jumpKey){
		jump = true;
	}
	else if(c == rollKey){
		roll = true;
	}
}

void Player::keyReleased(unsigned char key, int x, int y){
	unsigned char c = std::toupper(key);

	if(c == jumpKey){
		jump = false;
	}
	else if(c == rollKey){
		roll = false;
	}
}
