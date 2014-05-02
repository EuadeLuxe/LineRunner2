#include "State.h"

namespace bb{

State::State(){
	hasStarted = false;
}

State::~State(){

}

bool State::started(){
	return hasStarted;
}

};
