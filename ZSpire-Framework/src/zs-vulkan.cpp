#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include "string.h"
#include "../includes/zs-vulkan.h"

VkInstance instance;
std::vector<VkPhysicalDevice> vk_devices;


bool ZSpire::InitVulkan(const char* app_name, int app_version) {
	VkApplicationInfo app_info = {};
	VkInstanceCreateInfo vk_inst = {};

	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = "test";
	app_info.applicationVersion = app_version;
	app_info.apiVersion = VK_MAKE_VERSION(1, 0, 0);

	vk_inst.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	vk_inst.pApplicationInfo = &app_info;
	VkResult result = vkCreateInstance(&vk_inst, nullptr, &instance);

	uint32_t physicalDeviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
	vk_devices.resize(physicalDeviceCount);
	vkEnumeratePhysicalDevices(instance,&physicalDeviceCount,&vk_devices[0]);

	return result == VK_SUCCESS;
}