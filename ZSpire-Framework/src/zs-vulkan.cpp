#define _CRT_SECURE_NO_WARNINGS

#include "string.h"
#include "../includes/zs-vulkan.h"

VkInstance instance;

bool ZSpire::InitVulkan(const char* app_name, int app_version) {
	VkApplicationInfo app_info = {};
	VkInstanceCreateInfo vk_inst = {};

	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	strcpy((char*)app_info.pApplicationName, app_name);
	app_info.applicationVersion = app_version;
	app_info.apiVersion = VK_MAKE_VERSION(1, 0, 0);	vk_inst.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	vk_inst.pApplicationInfo = &app_info;
	VkResult result = vkCreateInstance(&vk_inst, nullptr, &instance);

	return result == VK_SUCCESS;
}