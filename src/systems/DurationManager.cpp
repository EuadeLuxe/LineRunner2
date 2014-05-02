#include "DurationManager.h"

DurationManager::DurationManager(){
	screen = 0;
}

void DurationManager::update(const float deltaTime){
	std::shared_ptr<Duration> duration;

	for(auto entity : entities){
		duration = std::static_pointer_cast<Duration>(entity->getComponent("Duration"));

		if(duration && !duration->finished){
			if(duration->stage == Duration::STAGE::WAIT){
				if(duration->wait > 0){
					duration->wait -= deltaTime;
				}
				else{
					duration->stage = Duration::STAGE::IN;
					continue;
				}
			}
			else if(duration->stage == Duration::STAGE::IN){
				if(duration->alpha < 1){
					duration->alpha += deltaTime*(1.0f/duration->in);
				}
				else{
					duration->alpha = 1.0f;
					duration->stage = Duration::STAGE::HOLD;
					continue;
				}
			}
			else if(duration->stage == Duration::STAGE::HOLD){
				if(duration->hold > 0){
					duration->hold -= deltaTime;
				}
				else{
					duration->stage = Duration::STAGE::OUT;
					continue;
				}
			}
			else{
				if(duration->alpha > 0){
					duration->alpha -= deltaTime*(1.0f/duration->out);
				}
				else{
					duration->alpha = 0.0f;
					duration->finished = true;
					screen++;
				}
			}
		}
	}
}
