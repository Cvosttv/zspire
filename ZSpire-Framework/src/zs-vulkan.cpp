#define ZS_Framework
#include "../includes/zspire.h"

#ifdef USE_VULKAN
#include <vulkan/vulkan.h>
#endif

#include <vector>
#include "string.h"
#include "../includes/zs-vulkan.h"

#ifdef USE_VULKAN
VkInstance instance;

std::vector<VkPhysicalDevice> vk_phys_devices;
std::vector<VkDevice> vk_devices;
std::vector<VkPhysicalDeviceFeatures> gpu_features;
std::vector<VkPhysicalDeviceProperties> gpu_properties;
std::vector<VkPhysicalDeviceMemoryProperties> gpu_memory_properties;
std::vector<VkQueueFamilyProperties> gpu_queue_families_prop;
std::vector<uint32_t> gpu_families_count;

bool ZSpire::Vulkan::InitVulkan() {
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

	vk_phys_devices.resize(physicalDeviceCount);
	gpu_features.resize(physicalDeviceCount);
	gpu_properties.resize(physicalDeviceCount);
	gpu_memory_properties.resize(physicalDeviceCount);
	gpu_queue_families_prop.resize(physicalDeviceCount);
	gpu_families_count.resize(physicalDeviceCount);
	
	vkEnumeratePhysicalDevices(instance,&physicalDeviceCount,&vk_phys_devices[0]);

	for (unsigned int device_iterator = 0; device_iterator < physicalDeviceCount; device_iterator++) {
		vkGetPhysicalDeviceProperties(vk_phys_devices[device_iterator], &gpu_properties[device_iterator]);
		vkGetPhysicalDeviceFeatures(vk_phys_devices[device_iterator], &gpu_features[device_iterator]);
		vkGetPhysicalDeviceMemoryProperties(vk_phys_devices[device_iterator], &gpu_memory_properties[device_iterator]);
	
		vkGetPhysicalDeviceQueueFamilyProperties(vk_phys_devices[device_iterator], &gpu_families_count[device_iterator], nullptr); //First time
		vkGetPhysicalDeviceQueueFamilyProperties(vk_phys_devices[device_iterator], &gpu_families_count[device_iterator], &gpu_queue_families_prop[device_iterator]); //Do this sh*t again
	}

	return result == VK_SUCCESS;
}

bool ZSpire::Vulkan::InitDevice(int device){
	VkResult result;

	VkDevice dev;

	VkDeviceQueueCreateInfo dqcinfo;
	dqcinfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	dqcinfo.flags = 0;
	dqcinfo.queueFamilyIndex = device;
	dqcinfo.queueCount = 4;
	dqcinfo.pQueuePriorities = nullptr;

	//Set up device creation info
	VkDeviceCreateInfo dcinfo;
	dcinfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	dcinfo.pNext = nullptr;
	dcinfo.flags = 0;
	dcinfo.pQueueCreateInfos = &dqcinfo;
	dcinfo.enabledLayerCount = 0;
	dcinfo.enabledExtensionCount = 0;
	dcinfo.ppEnabledLayerNames = nullptr;
	dcinfo.ppEnabledExtensionNames = nullptr;
	dcinfo.pEnabledFeatures = &gpu_features[device];

	result = vkCreateDevice(vk_phys_devices[device], &dcinfo, NULL, &dev);

	return result == VK_SUCCESS;
}
#endif