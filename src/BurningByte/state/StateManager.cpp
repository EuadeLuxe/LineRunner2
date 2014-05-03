#include "StateManager.h"

namespace bb {

StateManager::StateManager(){
	currentState = 0;
	currentStateName = "";
}

void StateManager::add(const std::string &name, const std::shared_ptr<State> state){
	states.insert(std::pair<std::string, std::shared_ptr<State>>(name, state));

	if(!currentState){
		currentState = state;
		currentStateName = name;
		currentState->load();
	}
}

void StateManager::remove(const std::string &name){
	auto i = states.find(name);

	if(i != states.end()){
		states.erase(i);
	}
}

void StateManager::remove(const std::shared_ptr<State> state){
	for(auto i : states){
		if(i.second == state){
			remove(i.first);
			return;
		}
	}
}

bool StateManager::switchTo(const std::string &name){
	auto i = states.find(name);

	if(i == states.end()){
		return false;
	}

	// switch
	if(currentState){
		currentState->pause();
	}

	currentState = i->second;
	currentStateName = name;

	if(!currentState->started()){
		currentState->load();
	}
	else{
		currentState->resume();
	}

	return true;
}

std::shared_ptr<State> StateManager::get(const std::string &name){
	auto i = states.find(name);

	if(i != states.end()){
		return i->second;
	}

	return 0;
}

std::shared_ptr<State> StateManager::current(){
	return currentState;
}

const std::string& StateManager::currentName(){
	return currentStateName;
}

};
