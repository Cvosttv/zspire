#ifndef ZSSCENE
#include "zs-scene.h"
#endif

namespace ZSpire {

	namespace DefferedRender {
		void setDefferedShaders(Shader* obj_shader, Shader* lighting_shader);
		void RenderScene(Scene* scene);
		void Init_gBuffer();
		void set_gBufferSize(unsigned int WIDTH, unsigned int HEIGHT);

		void destroy_gBuffer();
		void resize_gBuffer(unsigned int W, unsigned int H);
	}
}
