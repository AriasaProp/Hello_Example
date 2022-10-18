#include "mainListener.h"

static TranslatedGraphicsFunction *tgf = nullptr;

void Main::create(TranslatedGraphicsFunction *t) {
	tgf = t;
	tgf->clearcolormask(TGF::GL_COLOR_BUFFER_BIT|TGF::GL_DEPTH_BUFFER_BIT|TGF::GL_STENCIL_BUFFER_BIT, 1.f, 0.f, 0.f, 1.f)
}
void Main::resume() {
	
}
void Main::resize(unsigned int width, unsigned int height) {
	
}
void Main::render(float delta) {
	
}
void Main::pause() {
	tgf->clearcolormask(TGF::GL_COLOR_BUFFER_BIT|TGF::GL_DEPTH_BUFFER_BIT|TGF::GL_STENCIL_BUFFER_BIT, 1.f, 0.f, 0.f, 1.f)
}
void Main::destroy() {
	delete tgf;
	tgf = nullptr;
}