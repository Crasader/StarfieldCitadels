#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include <bitset>
#include <iostream>
#include <assert.h>
#include <typeinfo>
#include <bitset>

#include "../Component/Component.h"
#include "../Manager/ComponentTypeManager.h"
#include "../Utils/BitSize.h"
#include "../Utils/ImmutableBag.h"
//#include "Entity.h"


namespace evolve2d {

	class Entity;
	class World;
	
	/*
	 * Class abstract, cannot be instantiated. Create a new system using a system manager method: setSystem.
	 */
	class EntitySystem {
		public:
			void printTypeFlag() {
				std::cout << typeFlags;
			}
			std::bitset<BITSIZE> getSystemBit() {
				return systemBit;
			}
			void setSystemBit(std::bitset<BITSIZE> bit);
			virtual ~EntitySystem(); // Meant to be overridden in inherited custom systems.
			virtual void initialize() {}; // Meant to be overridden in inherited custom systems. Called from System Manager.
			void setWorld(World *world);
			void change(Entity &e);
			void process();
			int getEntityCount();
		protected:
			EntitySystem() { this->world = nullptr; };
			World * world;
			/**
			* Call this in the constructor of the derived system
			*/
			template<typename...components>
			void setComponentTypes() {
				addToTypeFlag(typelist<components...>());
			}
			/*override these functions*/
			virtual void begin() {}; // Event function: begin. Targets event prior to entity processing.
			virtual void end() {}; // Event function: end. Targets event immediately after entity processing.
			virtual void removed(Entity &e) {}; // Event function: removed. Targets event immediately after an entity is removed from active on a system.
			virtual void added(Entity &e) {}; // Event function: added. Targets event immediately after an entity is added as active on a system.
			//Abstracts. Must be overridden by inherited classes or else become abstract themselves.
			virtual void processEntities(ImmutableBag<Entity*> & bag) = 0; // Called in EntityProcessingSystem and DelayedEntityProcessingSystem.
			virtual bool checkProcessing() = 0;
		private:
			std::bitset<BITSIZE> systemBit;
			std::bitset<BITSIZE> typeFlags;
			Bag<Entity*> actives;
			void remove(Entity &e); // Remove an entity from active on a particular system
			//============================================================
			//Meta templates. Helps with passing each type from the variadic template
			/*
			 *Struct to pass rest the types
			 */
			template<typename...>
			struct typelist {};
			/*
			 * Recursively called. On each iteration  "component" is set to the next "typename" from rest pack set. .
			 * We pass this component into our ComponentManager.
			 */
			template<typename component, typename ... Rest>
			void addToTypeFlag(typelist<component,Rest...>) {
				//Add Bits to typeflags
				typeFlags |= ComponentTypeManager::getBit<component>();
				addToTypeFlag(typelist<Rest...>());
			};
			/**
			 * addToTypeFlag is called recursively. This defines the end condition.
			 * When our typelist has no types left from the pack, the call will end.
			 */
			void addToTypeFlag(typelist<>) { };
	};

};


#endif
