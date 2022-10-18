#ifndef Included_MainListener
#define Included_MainListener
#include "translatedGraphicsFunction.h"

namespace Main {
		extern static void create(const TranslateGraphicsFunction*);
		extern static void resume();
		extern static void resize(unsigned int, unsigned int);
		extern static void render(float);
		extern static void pause();
		extern static void destroy();
};

#endif // Included_MainListener

