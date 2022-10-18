#ifndef Included_TGF
#define Included_TGF

class TranslatedGraphicsFunction {
public:
	virtual ~TranslatedGraphicsFunction() {};
	virtual void clearcolormask(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int) = 0;
};

#endif //Included_TGF