#include <glew.h>

#include "../includes/GameObject.h"

#include "../includes/Renderer.h"

#include "../includes/Light.h"

ZSpire::Shader* object_shader;

void ZSpire::Renderer::RenderScene() {
	unsigned int objectsCount = getObjectsAmount();

	object_shader->Use();
	object_shader->updateCamera();

	for (unsigned int obj = 0; obj < objectsCount; obj ++) {
		getObjectPtr(obj)->Draw(object_shader);
	}

}

void ZSpire::Renderer::setObjectShaderPtr(Shader* obj_shader) {
	object_shader = obj_shader;
}