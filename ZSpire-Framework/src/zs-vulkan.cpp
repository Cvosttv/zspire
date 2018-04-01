
#include <vulkan/vulkan.h>

#include <vector>
#include "string.h"
#include "../includes/zs-vulkan.h"


VkInstance instance;

std::vector<VkPhysicalDevice> vk_devices;
std::vector<VkPhysicalDeviceProperties> gpu_properties;
std::vector<VkPhysicalDeviceMemoryProperties> gpu_memory_properties;
std::vector<VkQueueFamilyProperties> gpu_queue_families_prop;
std::vector<uint32_t> gpu_families_count;

bool ZSpire::InitVulkan() {
	VkApplicationInfo app_info = {};
	VkInstanceCreateInfo vk_inst = {};

	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = "test";
	app_info.applicationVersion = 1;
	app_info.apiVersion = VK_MAKE_VERSION(1, 0, 0);

	vk_inst.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	vk_inst.pApplicationInfo = &app_info;
	VkResult result = vkCreateInstance(&vk_inst, nullptr, &instance);

	uint32_t physicalDeviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);

	vk_devices.resize(physicalDeviceCount);
	gpu_properties.resize(physicalDeviceCount);
	gpu_memory_properties.resize(physicalDeviceCount);
	gpu_queue_families_prop.resize(physicalDeviceCount);
	gpu_families_count.resize(physicalDeviceCount);
	
	vkEnumeratePhysicalDevices(instance,&physicalDeviceCount,&vk_devices[0]);

	for (unsigned int device_iterator = 0; device_iterator < physicalDeviceCount; device_iterator++) {
		vkGetPhysicalDeviceProperties(vk_devices[device_iterator], &gpu_properties[device_iterator]);
		vkGetPhysicalDeviceMemoryProperties(vk_devices[device_iterator], &gpu_memory_properties[device_iterator]);
	
		vkGetPhysicalDeviceQueueFamilyProperties(vk_devices[device_iterator], &gpu_families_count[device_iterator], nullptr); //First time
		vkGetPhysicalDeviceQueueFamilyProperties(vk_devices[device_iterator], &gpu_families_count[device_iterator], &gpu_queue_families_prop[device_iterator]); //Do this sh*t again
	}

	return result == VK_SUCCESS;
}