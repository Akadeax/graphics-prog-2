#pragma once
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

class GP2Shader
{
public:
	GP2Shader(
		std::string vertexShaderFile,
		std::string fragmentShaderFile
	);

	~GP2Shader() = default;
	GP2Shader(const GP2Shader& rhs) = delete;
	GP2Shader(GP2Shader&& rhs) noexcept = delete;
	GP2Shader& operator=(const GP2Shader& rhs) = delete;
	GP2Shader& operator=(GP2Shader&& rhs) noexcept = delete;

	const std::vector<VkPipelineShaderStageCreateInfo>& GetShaderStages() const { return m_ShaderStages; }

	void Initialize(const VkDevice& vkDevice);
	void DestroyShaderModules(const VkDevice& vkDevice);

	VkPipelineShaderStageCreateInfo CreateFragmentShaderInfo(const VkDevice& vkDevice);
	VkPipelineShaderStageCreateInfo CreateVertexShaderInfo(const VkDevice& vkDevice);
	VkPipelineVertexInputStateCreateInfo CreateVertexInputStateInfo();
	VkPipelineInputAssemblyStateCreateInfo CreateInputAssemblyStateInfo();
	VkShaderModule CreateShaderModule(const VkDevice& vkDevice, const std::vector<char>& code);

private:
	std::string m_VertexShaderFile;
	std::string m_FragmentShaderFile;

	std::vector<VkPipelineShaderStageCreateInfo> m_ShaderStages;
};
