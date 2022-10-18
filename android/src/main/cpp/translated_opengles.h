#ifndef Included_TGLES
#define Included_TGLES

#include "translatedGraphicsFunction.h"

class tgf_gles : public TranslatedGraphicsFunction {
public:
	~tgf_gles() override {}
	void clearcolormask(unsigned int, float, float, float, float);
	void viewport(unsigned int, unsigned int, unsigned int, unsigned int);
};

#endif // Included_TGLES
