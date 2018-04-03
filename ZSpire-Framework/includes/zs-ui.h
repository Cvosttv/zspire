#ifndef ZSTRANSFORM
#include "zs-transform.h"
#endif

#ifndef ZSTEXTURE
#include "zs-texture.h"
#endif

#ifndef ZSSHADER
#include "zs-shader.h"
#endif

#ifndef ZSUI

namespace ZSpire {

	namespace UI {

		class SpriteUI {
		protected:
			Transform transform;
			Texture* texture;
		public:
			void Draw();
			Transform* getTransform();
		};

	}
}

#define ZSUI
#endif