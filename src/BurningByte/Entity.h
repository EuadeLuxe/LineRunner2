/*
 * Entity
 * Author: Marvin Blum
 * Last Update: 2014/04/09 20:51
 * */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <memory>
#include <map>
#include <string>
#include "Component.h"

namespace bb{

class Entity{
	private:
		static unsigned int ID;
		unsigned int id;

	protected:
		std::map<const std::string, std::shared_ptr<Component>> components;

	public:
		std::string name;

		Entity();
		Entity(const std::string &name);

		const unsigned int getID();

		void addComponent(const std::string &name, const std::shared_ptr<Component> component);
		bool removeComponent(const std::string &name);
		bool removeComponent(const std::shared_ptr<Component> component);
		void clearComponents();
		std::shared_ptr<Component> getComponent(const std::string &name);
};

};

#endif
