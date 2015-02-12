#ifndef ENT_PROCESS_SYS_H
#define ENT_PROCESS_SYS_H

#include "../Entity/EntitySystem.h"
#include "../Utils/ImmutableBag.h"

namespace evolve2d {

	class Entity;

	class EntityProcessingSystem : public EntitySystem {

		protected:
			EntityProcessingSystem() {};
			virtual void processEntity(Entity &e) = 0;
			void processEntities(ImmutableBag<Entity*> & bag);
			virtual bool checkProcessing();
	};
};

#endif // $(Guard token)
