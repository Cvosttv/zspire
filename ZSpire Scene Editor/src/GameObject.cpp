typedef unsigned int uint;
#include <vector>

#include "string.h"

#include "../includes/zs-math.h"
#include "../includes/zs-transform.h"
#include "../includes/Camera.hpp"
#include "../includes/Light.h"
#include "../includes/GameObject.h"

void GameObject::setLabel(const char* label){
	strcpy_s(this->label, label);
}

std::vector<GameObject> objs;

void addObject(GameObject object){
	bool hasFreePlace = false;
	uint placeFree = 0;

	for (uint i = 0; i < objs.size(); i ++) {
		if (objs[i].exist = false)
		{
			hasFreePlace = true; placeFree = i;
		}
	}

	if (hasFreePlace == true) 
	{
		objs[placeFree] = object;
	}
	else 
	{
		objs.push_back(object);
	}

}

void createNewObject() {
	GameObject obj;
	obj.setLabel("gameobject");
	addObject(obj);
}

GameObject getObject(uint pos)
{
	return objs[pos];
}

GameObject* getObjectPtr(uint pos)
{
	return &objs[pos];
}

uint getObjectsAmount(){
	return (unsigned int)objs.size();
}