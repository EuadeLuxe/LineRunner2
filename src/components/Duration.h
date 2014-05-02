#ifndef DURATION_H_
#define DURATION_H_

#include "../BurningByte/Component.h"

class Duration:public bb::Component{
	public:
		enum STAGE{
			WAIT,
			IN,
			HOLD,
			OUT
		};

		STAGE stage;
		bool finished;
		float alpha, wait, in, hold, out; // alpha color channel, in secounds

		Duration(const float wait, const float in, const float hold, const float out);
};

#endif
