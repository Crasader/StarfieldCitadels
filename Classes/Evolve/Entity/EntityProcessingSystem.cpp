#include "../Entity/EntityProcessingSystem.h"

#ifdef _DEBUG
#include <debug_new.h>
#endif

namespace evolve2d {
	
	bool EntityProcessingSystem::checkProcessing() {
		return true;
	}

	void EntityProcessingSystem::processEntities(ImmutableBag<Entity*>& bag) {
		for(int i=0; i < bag.getCount(); i++) 
			{processEntity(*bag.get(i));}
	}

};
