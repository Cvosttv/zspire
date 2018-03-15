

#include <vector>

#include "../includes/zs-math.h"

#include "../includes/zs-mesh.h"

#include "../includes/zs-texture.h"

#include "../includes/zs-transform.h"

#include "../includes/zs-game-object.h"

#include "../includes/zs-scene.h"

ZSpire::GameObject* ZSpire::Scene::getObjectAt(unsigned int index){
	return &this->game_objects[index];
}

unsigned int ZSpire::Scene::getObjectsCount() {
	return (unsigned int)game_objects.size();
}