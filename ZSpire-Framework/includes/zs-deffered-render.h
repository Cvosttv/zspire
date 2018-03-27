#ifndef ZSSCENE
#include "../includes/zs-scene.h"
#endif

namespace ZSpire {

	namespace DefferedRender {
		void RenderSceneDeffered(Scene* scene);
		void Init_gBuffer();
		void set_gBufferSize(unsigned int WIDTH, unsigned int HEIGHT);
	}
}
