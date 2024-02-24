#pragma once

#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <string>
#include <vector>

constexpr uint32_t WIDTH{ 800 };
constexpr uint32_t HEIGHT{ 600 };

#ifdef NDEBUG
constexpr bool enableValidationLayers{ false };
#else
constexpr bool enableValidationLayers{ true };
#endif


VkResult CreateDebugUtilsMessengerEXT(
	VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugUtilsMessengerEXT* pDebugMessenger
);

void DestroyDebugUtilsMessengerEXT(
	VkInstance instance,
	VkDebugUtilsMessengerEXT debugMessenger,
	const VkAllocationCallbacks* pAllocator
);

std::vector<char> ReadFile(const std::string& filename);
