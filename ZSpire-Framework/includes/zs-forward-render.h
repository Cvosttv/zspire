#ifndef ZSSCENE
#include "zs-scene.h"
#endif

#ifndef ZSUI
#include "zs-ui.h"
#endif

#ifndef ZSBASESTRUCTS
#include "zs-base-structs.h"
#endif

namespace ZSpire {
	
	namespace ForwardRender {
		void setForwardObjectShader(Shader* shader);

		void RenderScene(Scene* scene);

		void setRenderRule(ZSRENDERRULE rule);
	}
}