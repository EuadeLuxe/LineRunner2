#include "System.h"

namespace bb{

System::~System(){

}

void System::addEntity(const std::shared_ptr<Entity> entity){
	entities.push_back(entity);
}

bool System::removeEntity(const unsigned int id){
	for(auto i = entities.begin(); i != entities.end(); i++){ // we still need iterators here...
		if(id == (*i)->getID()){
			entities.erase(i);

			return true;
		}
	}

	return false;
}

bool System::removeEntity(const std::string &name){
	for(auto i = entities.begin(); i != entities.end(); i++){
		if(name == (*i)->name){
			entities.erase(i);

			return true;
		}
	}

	return false;
}

void System::removeEntity(const std::shared_ptr<Entity> entity){
	entities.remove(entity);
}

void System::clearEntities(){
	entities.clear();
}

std::shared_ptr<Entity> System::getEntity(const unsigned int id){
	for(auto i = entities.begin(); i != entities.end(); i++){
		if(id == (*i)->getID()){
			return *i;
		}
	}

	return 0;
}

std::shared_ptr<Entity> System::getEntity(const std::string &name){
	for(auto i = entities.begin(); i != entities.end(); i++){
		if(name == (*i)->name){
			return *i;
		}
	}

	return 0;
}

};
