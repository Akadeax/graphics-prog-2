#include "GP2Shader.h"

#include <stdexcept>
#include "vulkanbase/VulkanUtil.h"

GP2Shader::GP2Shader(std::string vertexShaderFile, std::string fragmentShaderFile)
	: m_VertexShaderFile{ std::move(vertexShaderFile) }
	, m_FragmentShaderFile{ std::move(fragmentShaderFile) }
{
}

void GP2Shader::Initialize(const VkDevice& vkDevice)
{
	m_ShaderStages.push_back(CreateVertexShaderInfo(vkDevice));
	m_ShaderStages.push_back(CreateFragmentShaderInfo(vkDevice));
}

void GP2Shader::DestroyShaderModules(const VkDevice& vkDevice)
{
	for (const auto& stageInfo : m_ShaderStages)
	{
		vkDestroyShaderModule(vkDevice, stageInfo.module, nullptr);
	}
}

VkPipelineShaderStageCreateInfo GP2Shader::CreateFragmentShaderInfo(const VkDevice& vkDevice)
{
	const std::vector fragShaderCode{ ReadFile(m_FragmentShaderFile) };
	const VkShaderModule fragShaderModule{ CreateShaderModule(vkDevice, fragShaderCode) };

	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";

	return fragShaderStageInfo;
}

VkPipelineShaderStageCreateInfo GP2Shader::CreateVertexShaderInfo(const VkDevice& vkDevice)
{
	const std::vector vertShaderCode{ ReadFile(m_VertexShaderFile) };
	const VkShaderModule vertShaderModule{ CreateShaderModule(vkDevice, vertShaderCode) };

	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";
	return vertShaderStageInfo;
}

VkPipelineVertexInputStateCreateInfo GP2Shader::CreateVertexInputStateInfo()
{
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 0;
	vertexInputInfo.vertexAttributeDescriptionCount = 0;
	return vertexInputInfo;
}

VkPipelineInputAssemblyStateCreateInfo GP2Shader::CreateInputAssemblyStateInfo()
{
	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;
	return inputAssembly;
}

VkShaderModule GP2Shader::CreateShaderModule(const VkDevice& vkDevice, const std::vector<char>& code)
{
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(vkDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}

	return shaderModule;
}
