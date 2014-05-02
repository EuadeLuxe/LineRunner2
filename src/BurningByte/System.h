/*
 * System
 * Author: Marvin Blum
 * Last Update: 2014/04/09 20:57
 * */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <list>
#include <string>
#include "Entity.h"

namespace bb{

class System{
	protected:
		std::list<std::shared_ptr<Entity>> entities;

	public:
		virtual ~System();
		virtual void update(const float deltaTime) = 0;

		void addEntity(const std::shared_ptr<Entity> entity);
		bool removeEntity(const unsigned int id);
		bool removeEntity(const std::string &name);
		void removeEntity(const std::shared_ptr<Entity> entity);
		void clearEntities();

		std::shared_ptr<Entity> getEntity(const unsigned int id);
		std::shared_ptr<Entity> getEntity(const std::string &name);
};

};

#endif
