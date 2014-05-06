#include "Player.h"

Player::Player(const std::string &name):Entity(name){
	jump = false;
	jumping = false;
	roll = false;
	rolling = false;
}

void Player::keyPressed(unsigned char key, int x, int y){
	if(key == 'w'){
		jump = true;
	}
	else if(key == 's'){
		roll = true;
	}
}

void Player::keyReleased(unsigned char key, int x, int y){
	if(key == 'w'){
		jump = false;
	}
	else if(key == 's'){
		roll = false;
	}
}
