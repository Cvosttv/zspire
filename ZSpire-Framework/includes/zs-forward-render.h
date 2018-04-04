#ifndef ZSSCENE
#include "zs-scene.h"
#endif

#ifndef ZSUI
#include "zs-ui.h"
#endif

namespace ZSpire {
	
	namespace ForwardRender {
		void setForwardObjectShader(Shader* shader);

		void RenderScene(Scene* scene);

		void RenderSpriteUI(UI::SpriteUI* sprite);
	}
}