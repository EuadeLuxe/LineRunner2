#include "Skip.h"

Skip::Skip(const std::shared_ptr<bb::StateManager> states){
	this->states = states;
}

void Skip::typed(const unsigned char c){
	states->remove("intro");
	states->switchTo("mainmenu");
}
