#ifndef ZSSCENE
#include "../includes/zs-scene.h"
#endif

namespace ZSpire {

	namespace DefferedRender {
		void setDefferedShaders(Shader* obj_shader, Shader* lighting_shader);
		void RenderSceneDeffered(Scene* scene);
		void Init_gBuffer();
		void set_gBufferSize(unsigned int WIDTH, unsigned int HEIGHT);
	}
}
