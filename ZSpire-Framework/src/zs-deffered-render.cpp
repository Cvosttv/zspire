
#include <glew.h>
#include <vector>

#include "../includes/zs-math.h"

#include "../includes/zs-transform.h"

#include "../includes/zs-camera.h"

#include "../includes/zs-shader.h"

#include "../includes/zs-mesh.h"

#include "../includes/zs-texture.h"

#include "../includes/zs-game-object.h"

#include "../includes/zs-light.h"

#include "../includes/zs-scene.h"

#include "../includes/zs-deffered-render.h"

unsigned int SCR_WIDTH;
unsigned int SCR_HEIGHT;

unsigned int gBufferFBO;

unsigned int gBufferDiffuseTextureBuffer;
unsigned int gBufferNormalTextureBuffer;
unsigned int gBufferPositionTextureBuffer;

void ZSpire::RenderSceneDeffered(Scene* scene) {}

void ZSpire::set_gBufferSize(unsigned int WIDTH, unsigned int HEIGHT) {

}

void ZSpire::Init_gBuffer() {
	glGenFramebuffers(1, &gBufferFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, gBufferFBO);
	//Generate Diffuse Albedo texture
	glGenTextures(1, &gBufferDiffuseTextureBuffer);
	glBindTexture(GL_TEXTURE_2D, gBufferDiffuseTextureBuffer);

	//Generate Normal texture
	glGenTextures(1, &gBufferNormalTextureBuffer);
	glBindTexture(GL_TEXTURE_2D, gBufferNormalTextureBuffer);

	glGenTextures(1, &gBufferPositionTextureBuffer);
	glBindTexture(GL_TEXTURE_2D, gBufferPositionTextureBuffer);

}