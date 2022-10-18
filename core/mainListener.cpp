#include "mainListener.h"

static TranslatedGraphicsFunction *tgf = nullptr;

static void Main::create(const TranslatedGraphicsFunction *t) {
	tgf = t;
}
void Main::resume() {
	
}
void Main::resize(unsigned int width, unsigned int height) {
	
}
void Main::render(float delta) {
	
}
void Main::pause() {
	
}
void Main::destroy() {
	delete tgf;
	tgf = nullptr;
}