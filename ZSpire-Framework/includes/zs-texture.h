//#ifndef ZSMATH
//#include "../includes/zs-math.h"
//#endif

#ifndef ZSRESOURCE
#include "../includes/zs-resource.h"
#endif

#ifndef ZSTEXTURE
#define ZSTEXTURE
#endif


namespace ZSpire {

	struct ZSTextureParams {
		float max_anisotropy = 0;
	};

	struct TextureProperties {
		unsigned int WIDTH;
		unsigned int HEIGHT;
	};

	class Texture {
	protected:
		unsigned int TEXTURE_ID;
		

	public:

		ZSTextureParams params;
		void setTextureParams();

		ZSResourceDesc resource_desc;
		bool loadFromResourceDesk();

		TextureProperties properties;
		void Use(unsigned int slot);
		void InitializeTexture();
		bool LoadDDSFromBuffer(unsigned char* buffer);
		bool LoadDDSFromFile(const char* file_path);
		void Release();
		unsigned int getTextureGL_ID();
	};
}