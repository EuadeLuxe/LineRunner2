#include "Entity.h"

namespace bb{

unsigned int Entity::ID = 1;

Entity::Entity(){
	id = ID;
	ID++;

	name = "";
}

Entity::Entity(const std::string &name){
	id = ID;
	ID++;

	this->name = name;
}

const unsigned int Entity::getID(){
	return id;
}

void Entity::addComponent(const std::string &name, const std::shared_ptr<Component> component){
	components.insert(std::make_pair(name, component));
}

bool Entity::removeComponent(const std::string &name){
	auto i = components.find(name);

	if(i != components.end()){
		components.erase(i);

		return true;
	}

	return false;
}

bool Entity::removeComponent(const std::shared_ptr<Component> component){
	for(auto c : components){
		if(c.second == component){
			components.erase(c.first);

			return true;
		}
	}

	return false;
}

void Entity::clearComponents(){
	components.clear();
}

std::shared_ptr<Component> Entity::getComponent(const std::string &name){
	auto i = components.find(name);

	if(i != components.end()){
		return i->second;
	}

	return 0;
}

};
