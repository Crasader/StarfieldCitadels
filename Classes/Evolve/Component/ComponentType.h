#ifndef COMPTYPE_H
#define COMPTYPE_H

#include <bitset>

#include "../Utils/BitSize.h"

namespace evolve2d {
	class ComponentType {
			/**
			 * Identifies a bitset and id for a component object
			 * Do not instantiate a ComponentType, instead use the ComponentTypeManager.
			 * */

		public:
			ComponentType();
			//==================================
			std::bitset<BITSIZE> getBit() const;
			int getId() const;
		private:
			//
			static std::bitset<BITSIZE> nextBit;
			static int nextId;
			//==================================
			std::bitset<BITSIZE> bit;
			int id;
			void init();


	};
};
#endif // $(Guard token)
