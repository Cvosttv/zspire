#include <glew.h>

#include "../includes/GameObject.h"

#include "../includes/Renderer.h"


ZSpire::Shader* object_shader;

void ZSpire::Renderer::RenderScene() {
	unsigned int objectsCount = getObjectsAmount();
	unsigned int lightsCount = getLightsAmount();

	object_shader->Use();
	object_shader->updateCamera();

	object_shader->setUniformInt("lights_amount", lightsCount);
	for (unsigned int lig = 0; lig < lightsCount; lig ++) {
		object_shader->setLight(lig, getLightPtr(lig));
	}

	for (unsigned int obj = 0; obj < objectsCount; obj ++) {
		getObjectPtr(obj)->Draw(object_shader);
	}

}

void ZSpire::Renderer::setObjectShaderPtr(Shader* obj_shader) {
	object_shader = obj_shader;
}