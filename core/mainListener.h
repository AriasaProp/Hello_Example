#ifndef Included_MainListener
#define Included_MainListener
#include "translatedGraphicsFunction.h"

namespace Main {
		void create(const TranslatedGraphicsFunction*);
		void resume();
		void resize(unsigned int, unsigned int);
		void render(float);
		void pause();
		void destroy();
};

#endif // Included_MainListener

