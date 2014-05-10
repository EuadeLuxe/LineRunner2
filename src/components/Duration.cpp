#include "Duration.h"

/*
* EuadeLuxe
* 10/05/2014 12:27
* Fixed bug in Duration::STAGE enum. IN and OUT are defined
* macros in minwindef.h (windows-specific)
*/

Duration::Duration(const float wait, const float in, const float hold, const float out){
	stage = STAGE_WAIT;
	finished = false;
	alpha = 0.0f;

	this->wait = wait;
	this->in = in;
	this->hold = hold;
	this->out = out;
}
