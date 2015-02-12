#include "../Entity/EntitySystem.h"
#include "../Entity/Entity.h"
#include "../World/World.h"

using namespace std;

namespace evolve2d {

	EntitySystem::~EntitySystem() {
		world = nullptr;
	}

	int EntitySystem::getEntityCount(){
		return actives.getCount();
	}

	/*
	 * Add an active entity to a system if it uses the same components
	 * as the system affects. Done using bitwise operations. If an entity
	 * no longer contains the components needed to be affected by a
	 * particular system then remove it from active.
	 */
	void EntitySystem::change(Entity& e) {
		bool contains = (systemBit & e.getSystemBits()) == systemBit;
		bool interest = (typeFlags & e.getTypeBits()) == typeFlags;

		if(interest && !contains && typeFlags.any()) {
			actives.add(&e);
			e.addSystemBit(systemBit);
			added(e);
		} else if(!interest && contains && typeFlags.any()) {
			this->remove(e);
		}
	}

	void EntitySystem::process() {
		if(checkProcessing()) {
			begin();
			processEntities(actives);
			end();
		}
	};

	void EntitySystem::setWorld(World *world) {
		this->world = world;
	};

	void EntitySystem::remove(Entity &e) {
		actives.remove(&e);
		e.removeSystemBit(systemBit);
		removed(e);
	};

	void  EntitySystem::setSystemBit(bitset<BITSIZE> bit) {
		systemBit = bit;
	}

};
