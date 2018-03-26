#ifdef _WIN32
#include <glew.h>
#endif

#ifdef __linux__
#include <GL/glew.h>
#endif

#include <vector>



#include "../includes/zs-camera.h"

#include "../includes/zs-light.h"

#include "../includes/zs-shader.h"

#include "../includes/zs-mesh.h"

#include "../includes/zs-texture.h"

#include "../includes/zs-game-object.h"

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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gBufferDiffuseTextureBuffer, 0);

	//Generate Normal texture
	glGenTextures(1, &gBufferNormalTextureBuffer);
	glBindTexture(GL_TEXTURE_2D, gBufferNormalTextureBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gBufferNormalTextureBuffer, 0);

	glGenTextures(1, &gBufferPositionTextureBuffer);
	glBindTexture(GL_TEXTURE_2D, gBufferPositionTextureBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gBufferPositionTextureBuffer, 0);

	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

}