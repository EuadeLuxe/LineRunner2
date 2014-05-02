/*
 * StateManager
 * Author: Marvin Blum
 * Last Update: 2014/04/08 15:40
 * */

#ifndef STATEMANAGER_H_
#define STATEMANAGER_H_

#include <memory>
#include <map>
#include <string>
#include "State.h"

namespace bb{

class StateManager{
	private:
		std::map<std::string, std::shared_ptr<State>> states;
		std::shared_ptr<State> currentState;
		std::string currentStateName;

	public:
		StateManager();

		void add(const std::string name, const std::shared_ptr<State> state);
		bool switchTo(const std::string name);

		std::shared_ptr<State> get(const std::string name);
		std::shared_ptr<State> current();
		const std::string& currentName();
};

};

#endif
