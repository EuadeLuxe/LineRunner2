#include "Duration.h"

Duration::Duration(const float wait, const float in, const float hold, const float out){
	stage = WAIT;
	finished = false;
	alpha = 0.0f;

	this->wait = wait;
	this->in = in;
	this->hold = hold;
	this->out = out;
}
