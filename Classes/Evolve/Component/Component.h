#ifndef COMPONENT_H
#define COMPONENT_H

namespace evolve2d {

		class Component {
			public:
				virtual ~Component() = 0;
			protected:
				Component() {};
		};

};

#endif
