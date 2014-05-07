#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "../BurningByte/Component.h"
#include "../BurningByte/math/Vector.h"

class Animation:public bb::Component{
	public:
		class Keyframe{
			public:
				bb::vec2 scale, offset;

				Keyframe(const bb::vec2 &scale, const bb::vec2 &offset);
		};

		class Set{
			private:
				std::vector<std::shared_ptr<Keyframe>> frames;
				unsigned int currentFrame;
				bool loop;

			public:
				Set(const bool loop);

				void add(const std::shared_ptr<Keyframe> frame);
				void set(const unsigned int i);
				void reset();
				void next();

				std::shared_ptr<Keyframe> current();
				unsigned int currentIndex();
		};

	private:
		std::map<std::string, std::shared_ptr<Set>> sets;
		std::shared_ptr<Set> currentSet;
		float speed, interpolation;

	public:
		Animation(const float speed);

		void add(const std::string &name, const std::shared_ptr<Set> set);
		void set(const std::string &name);

		void update(const float deltaTime);

		std::shared_ptr<Set> current();
};

#endif
