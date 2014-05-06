#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <memory>
#include <vector>
#include "../BurningByte/Component.h"
#include "../BurningByte/math/Vector.h"

class Animation:public bb::Component{
	public:
		class Keyframe{
			public:
				bb::vec2 scale, offset;

				Keyframe(const bb::vec2 &scale, const bb::vec2 &offset);
		};

	private:
		std::vector<std::shared_ptr<Keyframe>> frames;
		unsigned int currentFrame;
		float speed, interpolation;
		bool loop;

	public:
		Animation(const float speed, const bool loop);

		void add(const std::shared_ptr<Keyframe> keyframe);
		void setCurrent(const unsigned int i);
		void update(const float deltaTime);

		std::shared_ptr<Keyframe> current();
};

#endif
