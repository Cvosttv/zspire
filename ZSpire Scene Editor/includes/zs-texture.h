//#ifndef ZSRESOURCES
//#include "Resources.h"
//#endif

#ifndef ZSTEXTURE
#define ZSTEXTURE
#endif

namespace ZSpire {

	struct TextureProperties {
		unsigned int WIDTH;
		unsigned int HEIGHT;
	};

	class Texture {
	protected:
		unsigned int TEXTURE_ID;
		
	
	public:
		TextureProperties properties;
		void Use(unsigned int slot);
		void InitializeTexture();
		bool LoadDDSFromBuffer(unsigned char* buffer);
		bool LoadDDSFromFile(const char* file_path);

		void setAnisotropyValue(float aniso);
		void Release();
		unsigned int getTextureGL_ID();
	};
}