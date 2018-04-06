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
			void setTexture(Texture* texture);

			void setSize(ZSVECTOR2 size);
			void setPosition(ZSVECTOR2 pos);

			SpriteUI() {
				setSize(ZSVECTOR2(100, 100));
				setPosition(ZSVECTOR2(0,0));
			}
		};

		class ButtonUI {
		protected:
			wchar_t text[128];
			SpriteUI sprite;
			ZSRGBCOLOR text_color;

			ZSVECTOR2 pos;
			ZSVECTOR2 size;

			float text_len;
			float text_max_h;

		public:
			void setText(const wchar_t* text);
			void setTextColor(ZSRGBCOLOR text_color);

			void Draw();

			void setTexture(Texture* texture);

			void setSize(ZSVECTOR2 size);
			void setPosition(ZSVECTOR2 pos);

			ButtonUI() {
				text[0] = L'\0';
				setSize(ZSVECTOR2(100, 50));
			}

		};

		void setShaderText(Shader* _text_shader);
		void setShader(Shader* shader);
		void ToggleUI();
	}
}

#define ZSUI
#endif