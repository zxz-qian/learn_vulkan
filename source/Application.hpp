#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#include <vector>
#include "optional"

#include "Vertex.hpp"
#include "UniformBufferObject.hpp"

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool IsComplete() const
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Application
{

private:
#pragma region -=VK related=-
    GLFWwindow *window;
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    const std::string MODEL_PATH = "D:\\Projects\\1Cpp\\VulkanTest\\models\\viking_room.obj";
    const std::string TEXTURE_PATH = "D:\\Projects\\1Cpp\\VulkanTest\\models\\viking_room.png";

    const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"};

    const std::vector<const char *> deviceExtensions =
        {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    const int MAX_FRAMES_IN_FLIGHT = 2;
    uint32_t currentFrame = 0;

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    VkInstance Instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    // VkPhysicalDeviceFeatures deviceFeatures{};

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSurfaceKHR surface;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    std::vector<VkImageView> swapchainImageViews;

#pragma region -=pipeline=-
    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
#pragma endregion

#pragma region -=frame buffer=-
    std::vector<VkFramebuffer> swapChainFramebuffers;

    bool framebufferResized = false;
#pragma endregion

#pragma region -=command buffer=-
    VkCommandPool commandPool;
    // VkCommandBuffer commandBuffer;
    std::vector<VkCommandBuffer> commandBuffers;
#pragma endregion

#pragma region -=synchronization=-
    // VkSemaphore imageAvailableSemaphore;
    // VkSemaphore renderFinishedSemaphore;
    // VkFence inFlightFence;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
#pragma endregion

#pragma region -=buffers=-
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;

    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    // we have multi frames to render in flight, thus we must create mulit buffers for uniform buffer.
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void *> uniformBuffersMapped;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
#pragma endregion

#pragma region -=texture image=-
    uint32_t mipLevels;
    VkImage textureImage;

    VkImageView textureImageView;
    VkSampler textureSampler;

    VkDeviceMemory textureImageMemory;
#pragma endregion

#pragma region -=depth image=-
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
#pragma endregion

#pragma region -=msaa=-
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;
#pragma endregion

#pragma endregion

#pragma region -=App data=-
    std::vector<Vertex> vertices;

    std::vector<uint32_t> indices;
#pragma endregion

public:
    Application(/* args */);
    ~Application();
    void Run();

private:
    void InitWindow();
    void InitVulkan();
    void CreateInstance();
    bool CheckGLFWRequired(uint32_t &count, const char **&extensions);
    void MainLoop();
    void CleanUp();

    bool CheckValidationLayerSupport();

    void SetupDebugMessenger();

    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    void PickPhysicalDevice();
    void CreateLogicalDevice();
    void CreateSurface();

    bool IsDevicesSuitable(VkPhysicalDevice devices);

    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

#pragma region -=Swapchain=-
    void CreateSwapChain();

    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    void RecreateSwapChain();

    void CleanSwapChain();

#pragma region -=Image View=-
    void CreateImageViews();
#pragma endregion

#pragma region -=frame buffer=-
    void CreateFramebuffer();
#pragma endregion

    static void OnFramebufferResized(GLFWwindow *window, int width, int height);

#pragma endregion

#pragma region -=Pipeline=-
    void CreateGraphicsPipeline();

    VkShaderModule CreateShaderModule(const std::vector<char> &code);

    void CreateRenderPass();
#pragma endregion

#pragma region -=command buffer=-
    void CreateCommandPool();
    void CreateCommandBuffers();
    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
#pragma endregion

#pragma region -=synchronization=-
    void CreateSyncObject();
#pragma endregion

#pragma region -=Draw frame=-
    void DrawFrame();
#pragma endregion

#pragma region -=create buffer=-
    void CreateVertexBuffer();

    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);

    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void CreateIndexBuffer();

    void CreateUniformBuffers();
#pragma endregion

#pragma region -=uniform buffer=-
    void CreateDescriptorSetLayout();

    void CreateDescriptorPool();
    void CreateDescriptorSets();

    void UpdateUniformBuffer(uint32_t currentImage);
#pragma endregion

#pragma region -=debug messenger=-
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *userData);

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *createInfo, const VkAllocationCallbacks *allocator, VkDebugUtilsMessengerEXT *debugMessenger);

    void DestoryDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *allocator);
#pragma endregion

#pragma region -=texture mapping=-
    void CreateTextureImage();

    void CreateImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

    void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);

    void CreateTextureImageView();

    VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

    void CreateTextureSampler();

    void GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
#pragma endregion

#pragma region -=depth image=-
    void CreateDepthResources();

    VkFormat FindDepthFormat();

    bool HasStencilComponent(VkFormat format);

    VkFormat FindSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
#pragma endregion

#pragma region -=msaa=-
    VkSampleCountFlagBits GetMaxUsableSampleCount();

    void CreateColorResources();
#pragma endregion

    VkCommandBuffer BeginSingleTimeCommands();

    void EndSingleTimeCommands(VkCommandBuffer commandBuffer);

    void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    void LoadModel();
};
