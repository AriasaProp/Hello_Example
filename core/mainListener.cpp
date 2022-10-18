#include "mainListener.h"

static TranslatedGraphicsFunction *tgf = nullptr;

static void Main::create(const TranslatedGraphicsFunction *t) {
	tgf = t;
}
static void Main::resume() {
	
}
static void Main::resize(unsigned int width, unsigned int height) {
	
}
static void Main::render(float delta) {
	
}
static void Main::pause() {
	
}
static void Main::destroy() {
	delete tgf;
	tgf = nullptr;
}