#ifndef ZSSHADER
#define ZSSHADER
#endif

#ifndef ZSMATH
#include "../includes/zs-math.h"
#endif

#ifndef ZSLIGHT
#include "../includes/zs-light.h"
#endif

#ifndef ZSTRANSFORM
#include "../includes/zs-transform.h"
#endif // !ZSTRANSFORM


namespace ZSpire {
	class Shader {
	protected:
		unsigned int SHADER_GL_ID;

		unsigned int VS_GL_ID;
		unsigned int FS_GL_ID;
	public:

		void setUniformInt(const char* uniform_string, int value);
		void setUniformVec3(const char* uniform_string, ZSVECTOR3 value);
		void setUniformMat4x4(const char* uniform_string, ZSMATRIX4x4 value);
		void setUniformFloat(const char* uniform_string, float value);
		void setUniformColor3(const char* uniform, ZSRGBCOLOR color);

		
		void InitializeShader();
		bool compileFromFile(const char* VS_SHADER_PATH, const char* FS_SHADER_PATH);
		bool compileFromBuffer(const char* VS_CONTENT, const char* FS_CONTENT);
		void Use();

		void bindUniforms();

		void setTransform(Transform* translation);
		void setLight(unsigned int index, Light* light);
		void updateCamera();
	};
}