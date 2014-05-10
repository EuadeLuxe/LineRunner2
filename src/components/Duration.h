#ifndef DURATION_H_
#define DURATION_H_

#include "../BurningByte/Component.h"

/*
 * EuadeLuxe
 * 10/05/2014 12:25
 * Fixed bug in Duration::STAGE enum. IN and OUT are defined
 * macros in minwindef.h (windows-specific)
 */

class Duration:public bb::Component{
	public:
		enum STAGE{
			STAGE_WAIT,
			STAGE_IN,
			STAGE_HOLD,
			STAGE_OUT
		};

		STAGE stage;
		bool finished;
		float alpha, wait, in, hold, out; // alpha color channel, in secounds

		Duration(const float wait, const float in, const float hold, const float out);
};

#endif
