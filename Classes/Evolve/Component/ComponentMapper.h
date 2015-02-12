#ifndef COMPONENTMAPPER_H
#define COMPONENTMAPPER_H

#include "../Manager/EntityManager.h"
#include "../World/World.h"

namespace evolve2d {
	
		template<typename c>
		class ComponentMapper {

			private:
				
				EntityManager * em;

			public:
			
				~ComponentMapper() {
					//Not the owner. Only a pointer to.
					em = nullptr;
				}
				
				void init(World& world){
					em = world.getEntityManager();
				}
				
				/**
				 *Returns the component mapped to the Entity.
				 *If there is no such component associated with the entity
				 *nullptr is returned.
				 */
				c * get(Entity & e) {
					//ATTN perhaps pointing to the component bag is faster.
					return (c*)em->getComponent<c>(e);
				}

		};
};
#endif // $(Guard token)
