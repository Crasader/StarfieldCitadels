#ifndef D_E_PROCESSING_SYSTEM_H
#define D_E_PROCESSING_SYSTEM_H

#include "../Entity/DelayedEntitySystem.h"

namespace evolve2d{
	class DelayedEntityProcessingSystem : public DelayedEntitySystem
	{
		protected:
		virtual void processEntities(ImmutableBag<Entity*>& bag, float accumulatedDelta);
		virtual void processEntity(Entity& e, float accumulatedDelta) = 0;
	};
};

#endif // $(Guard token)
