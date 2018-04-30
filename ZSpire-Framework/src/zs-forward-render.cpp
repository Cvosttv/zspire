#include <vector>

#include "../includes/zs-base-structs.h"

#include "../includes/zs-camera.h"

#include "../includes/zs-light.h"

#include "../includes/zs-shader.h"

#include "../includes/zs-game-object.h"

#include "../includes/zs-scene.h"

#include "../includes/zs-forward-render.h"

#ifdef _WIN32
#include <glew.h>
#endif

#ifdef __linux__
#include <GL/glew.h>
#endif

ZSpire::Shader* object_shader;

ZSpire::ZSRENDERRULE renderRules;
GLbitfield clearMode = GL_COLOR_BUFFER_BIT;

void ZSpire::ForwardRender::setForwardObjectShader(Shader* shader) {
	object_shader = shader;
}

void ZSpire::ForwardRender::RenderScene(Scene* scene) {
	
	glClear(clearMode);
	
	if (renderRules.cullFaces == true) {
		glEnable(GL_CULL_FACE);
	}
	if (renderRules.depthTest == true) {
		glEnable(GL_DEPTH_TEST);
	}
	object_shader->Use();

	object_shader->setUniformInt("lights_amount", scene->getLightsCount());

	Camera::setCameraMode(CAMERA_MODE_SCENE);

	object_shader->updateCamera();

	for (unsigned int light = 0; light < scene->getLightsCount(); light ++) {
		object_shader->setLight(light, scene->getLightAt(light));
	}

	for (unsigned int obj = 0; obj < scene->getObjectsCount(); obj ++) {
		Transform * tr = scene->getObjectAt(obj)->getTransform();
	
		object_shader->setTransform(tr);
		
		scene->getObjectAt(obj)->Draw();
	}

	
}

void ZSpire::ForwardRender::setRenderRule(ZSRENDERRULE rule) {
	renderRules = rule;

	if (rule.depthTest == true) {
		clearMode = clearMode | GL_DEPTH_BUFFER_BIT;
	}
}