#include "Player.h"

/*
* ------------------------------
* EuadeLuxe
* 10/05/2014 12:23
* Removed std:: in front of toupper.
*/

Player::Player(const std::string &name, const unsigned char jumpKey, const unsigned char rollKey):Entity(name){
	jump = false;
	jumping = false;
	roll = false;
	rolling = false;
	this->jumpKey = toupper(jumpKey);
	this->rollKey = toupper(rollKey);
}

void Player::keyPressed(unsigned char key, int x, int y){
	unsigned char c =  toupper(key);

	if(c == jumpKey){
		jump = true;
	}
	else if(c == rollKey){
		roll = true;
	}
}

void Player::keyReleased(unsigned char key, int x, int y){
	unsigned char c =  toupper(key);

	if(c == jumpKey){
		jump = false;
	}
	else if(c == rollKey){
		roll = false;
	}
}
