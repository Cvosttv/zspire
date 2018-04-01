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

//ZSpire::Shader* deffered_object_shader;
ZSpire::Shader* deff_obj_shader;
ZSpire::Shader* light_shader;


unsigned int SCR_WIDTH;
unsigned int SCR_HEIGHT;

unsigned int gBufferFBO;

unsigned int gBufferDiffuseTextureBuffer;
unsigned int gBufferNormalTextureBuffer;
unsigned int gBufferPositionTextureBuffer;

unsigned int gBufferDepthBuffer;

void ZSpire::DefferedRender::setDefferedShaders(Shader* obj_shader, Shader* lighting_shader) {
	deff_obj_shader = obj_shader;
	light_shader = lighting_shader;
}

void ZSpire::DefferedRender::RenderScene(Scene* scene) {

	glBindFramebuffer(GL_FRAMEBUFFER, gBufferFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	deff_obj_shader->Use();

	deff_obj_shader->updateCamera();

	
	for (unsigned int obj = 0; obj < scene->getObjectsCount(); obj++) {
		Transform * tr = scene->getObjectAt(obj)->getTransform();

		deff_obj_shader->setTransform(tr);

		scene->getObjectAt(obj)->Draw();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	light_shader->Use();

	for (unsigned int light = 0; light < scene->getLightsCount(); light++) {
		light_shader->setLight(light, scene->getLightAt(light));
	}

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D ,gBufferDiffuseTextureBuffer);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, gBufferNormalTextureBuffer);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, gBufferPositionTextureBuffer);

	glDisable(GL_DEPTH_TEST);
	getPlaneMesh2D()->Draw();
}

void ZSpire::DefferedRender::set_gBufferSize(unsigned int WIDTH, unsigned int HEIGHT) {
	SCR_WIDTH = WIDTH;
	SCR_HEIGHT = HEIGHT;
}

void ZSpire::DefferedRender::Init_gBuffer() {
	glGenFramebuffers(1, &gBufferFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, gBufferFBO);

	glGenRenderbuffers(1, &gBufferDepthBuffer);

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

	glBindRenderbuffer(GL_RENDERBUFFER, gBufferDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gBufferDepthBuffer);
	


}
