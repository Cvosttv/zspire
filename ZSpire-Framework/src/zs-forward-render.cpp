#include <vector>


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

void ZSpire::ForwardRender::setForwardObjectShader(Shader* shader) {
	object_shader = shader;
}

void ZSpire::ForwardRender::RenderScene(Scene* scene) {
	glEnable(GL_CULL_FACE);
	object_shader->Use();

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

