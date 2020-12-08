#pragma once

#include "Window.hpp"
#include "Simulation.hpp"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtx/hash.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLFW_INCLUDE_VULKAN
#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL

#define _USE_MATH_DEFINES

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <array>
#include <optional>
#include <set>
#include <math.h>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::string TEXTURE_PATH = "textures/gradiant.png";

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

/// <summary>
/// struct with graphics info
/// </summary>
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

/// <summary>
/// struct with swap chain support details
/// </summary>
struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

/// <summary>
/// strect with the vertex info
/// </summary>
struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, normal);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, color);

        attributeDescriptions[3].binding = 0;
        attributeDescriptions[3].location = 3;
        attributeDescriptions[3].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[3].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }

    bool operator==(const Vertex& other) const {
        return pos == other.pos && normal == other.normal && color == other.color && texCoord == other.texCoord;
    }
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

/// <summary>
/// struct with light info
/// </summary>
struct Light {
    alignas(16) glm::vec3 color;
    alignas(16) glm::vec3 position;
    float intensity;                // NO alignas, causes black screen
};

/// <summary>
/// struct with camera info and map position
/// </summary>
struct UniformBufferObject {        // rename, uboCamera?
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

/// <summary>
/// struct with all light positions
/// </summary>
struct UboLights {
    Light trafficLights[82];
};

/// <summary>
/// struct with pipeline
/// </summary>
struct GraphicsPipeLine {
    VkPipeline pipeline;
    VkPipelineLayout Layout;

    void destroy(VkDevice device) {
        vkDestroyPipeline(device, pipeline, nullptr);
        vkDestroyPipelineLayout(device, Layout, nullptr);
    }
};

/// <summary>
/// struct with model info
/// </summary>
struct ModelBuffers {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    void destroy(VkDevice device) {
        vkDestroyBuffer(device, indexBuffer, nullptr);
        vkFreeMemory(device, indexBufferMemory, nullptr);

        vkDestroyBuffer(device, vertexBuffer, nullptr);
        vkFreeMemory(device, vertexBufferMemory, nullptr);
    };
};

/// <summary>
/// struct with descriptor info
/// </summary>
struct Descriptor {
    VkDescriptorSetLayout layout;
    VkDescriptorPool pool;
    std::vector<VkDescriptorSet> set;

    void destroyPool(VkDevice device) {
        vkDestroyDescriptorPool(device, pool, nullptr);
    }

    void destroyLayout(VkDevice device) {
        vkDestroyDescriptorSetLayout(device, layout, nullptr);
    }
};

class Renderer
{
public:
    /// <summary>
    /// constructor
    /// </summary>
    /// <param name="ptr_w">ptr to window class</param>
    /// <param name="ptr_c">ptr to the camera class</param>
    /// <param name="ptr_s">ptr to the simulation class</param>
    Renderer(std::shared_ptr<Window> ptr_w, std::shared_ptr<Camera> ptr_c, std::shared_ptr<Simulation> ptr_s) : ptr_window(move(ptr_w)), ptr_camera(move(ptr_c)), ptr_simulation(move(ptr_s)) {}

    /// <summary>
    /// call all functions needed to initialize vulkan
    /// </summary>
    void initvulkan();

    /// <summary>
    /// after stopping the vulkan app, the used resources need to cleaned up
    /// </summary>
    void cleanup();

    /// <summary>
    /// everytime this function is called it will draw the next frame
    /// </summary>
    void drawFrame();

    /// <summary>
    /// get the GPU used
    /// </summary>
    /// <returns>GPU</returns>
    VkDevice getDevice();

private:
    int totalModelInstances = 0;

    std::shared_ptr<Window> ptr_window;
    std::shared_ptr<Camera> ptr_camera;
    std::shared_ptr<Simulation> ptr_simulation;
    size_t dynamicAlignment;

    struct DynamicUniformBufferObject {
        alignas(16) glm::mat4* model = nullptr;
    } dubo;

    ModelInfo junctionModelInfo;
    std::vector<ModelInfo> models;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
    VkPhysicalDeviceProperties gpuProperties;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass renderPass;

    GraphicsPipeLine vehiclePipeline;
    GraphicsPipeLine junctionPipeline;

    VkCommandPool commandPool;

    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;

    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    ModelBuffers vehicleBuffers;
    ModelBuffers junctionBuffers;

    Descriptor vehicleDescriptor;
    Descriptor junctionDescriptor;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;

    std::vector<VkBuffer> lightBuffers;
    std::vector<VkDeviceMemory> lightBuffersMemory;

    std::vector<VkBuffer> dynamicUniformBuffers;
    std::vector<VkDeviceMemory> dynamicUniformBuffersMemory;

    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame = 0;

    /// <summary>
    /// create vulkan intance
    /// </summary>
    void createInstance();

    /// <summary>
    /// debug messanger
    /// </summary>
    void setupDebugMessenger();

    /// <summary>
    /// create surface to draw on (black screen inside of the window)
    /// </summary>
    void createSurface();

    /// <summary>
    /// query the system for availeble graphics cards and select one
    /// </summary>
    void pickPhysicalDevice();

    /// <summary>
    /// logical device handles communication with the GPU
    /// </summary>
    void createLogicalDevice();

    /// <summary>
    /// queue of images(frames) waiting to be displayed. handels syncing frames with the screen refresch rate.
    /// </summary>
    void createSwapChain();

    /// <summary>
    /// swapchain destructor
    /// </summary>
    void cleanupSwapChain();

    /// <summary>
    /// rebuild swapchain, is used for resizing the window
    /// </summary>
    void recreateSwapChain();

    /// <summary>
    /// image views are used to acces the images in the swapchain. these discribe how to acces them
    /// </summary>
    void createImageViews();

    /// <summary>
    /// specify the framebuffer attachments that are going to be used
    /// </summary>
    void createRenderPass();

    /// <summary>
    /// define layout of the descriptors
    /// </summary>
    void createDescriptorSetLayout();

    /// <summary>
    /// takes all the vertex and texture data and aplies the shader calculations to create the pixeldata needed for rendering
    /// </summary>
    void createGraphicsPipeline();

    /// <summary>
    /// the commandpool holds all drawing commands
    /// </summary>
    void createCommandPool();

    /// <summary>
    /// 
    /// </summary>
    void createColorResources();

    /// <summary>
    /// create depth information for the images in the swap chain
    /// </summary>
    void createDepthResources();

    /// <summary>
    /// create the buffers for images in the swapchain
    /// </summary>
    void createFramebuffers();

    /// <summary>
    /// load the texture into a buffer
    /// </summary>
    void createTextureImage();

    /// <summary>
    /// 
    /// </summary>
    void createTextureImageView();

    /// <summary>
    /// 
    /// </summary>
    void createTextureSampler();

    /// <summary>
    /// declair all model information and load them in the specefied buffers
    /// </summary>
    void loadModels();

    /// <summary>
    /// create vertex buffers
    /// </summary>
    void createVertexBuffers();

    /// <summary>
    /// create index buffers
    /// </summary>
    void createIndexBuffers();

    /// <summary>
    /// create the uniform buffers, these contain date the shaders can use
    /// </summary>
    void createUniformBuffers();

    /// <summary>
    /// descriptorpool contain per image in de swapchain the discriptors sets
    /// </summary>
    void createDescriptorPool();

    /// <summary>
    /// descriptor sets tell the shader how to acces the data in the uniform buffers
    /// </summary>
    void createDescriptorSets();

    /// <summary>
    /// command buffer contain the instruction for how to draw the frame.
    /// </summary>
    void createCommandBuffers();

    /// <summary>
    /// creates fences and semaphores.
    /// fences: can be accessed from your program using calls, fences are mainly designed to synchronize your application itself with rendering operations
    /// semaphores: are used to synchronize operations within or across command queues
    /// </summary>
    void createSyncObjects();
    

    /// <summary>
    /// setup the debug messanger
    /// </summary>
    /// <param name="createInfo">info of the created vulkan instance</param>
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    /// <summary>
    /// get the list of required extentions of glwf, so these can be used for error checking
    /// </summary>
    /// <returns>list of glfw extensions</returns>
    std::vector<const char*> getRequiredExtensions();

    /// <summary>
    /// check if there are any layers that support validation
    /// </summary>
    /// <returns>tue or false</returns>
    bool checkValidationLayerSupport();

    /// <summary>
    /// prints the error thrown to the console
    /// </summary>
    /// <param name="messageSeverity">flags</param>
    /// <param name="messageType"></param>
    /// <param name="pCallbackData"></param>
    /// <param name="pUserData">used varibeles</param>
    /// <returns></returns>
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    
    /// <summary>
    /// create debug messanger
    /// </summary>
    /// <param name="instance"></param>
    /// <param name="pCreateInfo"></param>
    /// <param name="pAllocator"></param>
    /// <param name="pDebugMessenger"></param>
    /// <returns></returns>
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    
    /// <summary>
    /// destroy debug messanger
    /// </summary>
    /// <param name="instance"></param>
    /// <param name="debugMessenger"></param>
    /// <param name="pAllocator"></param>
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

    /// <summary>
    /// check if the selected GPU is supports vulkan
    /// </summary>
    /// <param name="device">selected GPU</param>
    /// <returns></returns>
    bool isDeviceSuitable(VkPhysicalDevice device);

    /// <summary>
    /// ckeck if the selected gpu supports all used extensions
    /// </summary>
    /// <param name="device">selected GPU</param>
    /// <returns></returns>
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    /// <summary>
    /// query the selected GPU to see which queue types it supports
    /// </summary>
    /// <param name="device">selected GPU</param>
    /// <returns>supported queue families</returns>
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    /// <summary>
    /// check if the GPU supports swapchain
    /// </summary>
    /// <param name="device">selected GPU</param>
    /// <returns></returns>
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="availableFormats"></param>
    /// <returns></returns>
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

    /// <summary>
    /// check if VK_PRESENT_MODE_MAILBOX_KHR is supoorted
    /// </summary>
    /// <param name="availablePresentModes">list to check</param>
    /// <returns></returns>
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="capabilities"></param>
    /// <returns></returns>
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    /// <summary>
    /// read the .spv files (shaders)
    /// </summary>
    /// <param name="filename">.spv file path</param>
    /// <returns>buffer with the spv data</returns>
    static std::vector<char> readFile(const std::string& filename);

    /// <summary>
    /// create shade module
    /// </summary>
    /// <param name="code">buffer with the .spv data</param>
    /// <returns></returns>
    VkShaderModule createShaderModule(const std::vector<char>& code);

    /// <summary>
    /// check the memmory type on the GPU
    /// </summary>
    /// <param name="typeFilter"></param>
    /// <param name="properties"></param>
    /// <returns>index of the choosen memmory type</returns>
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    
    /// <summary>
    /// load the vertex data(verticies, indecies, normals, texture coords) from de models into the specified buffers
    /// </summary>
    /// <param name="model">model info</param>
    /// <param name="modelBuffer">buffers to push the loaded data into</param>
    void loadModel(ModelInfo* model, ModelBuffers& modelBuffer);

    /// <summary>
    /// take the modeldata en copy the verticies to the GPU
    /// </summary>
    /// <param name="modelBuffer">data struct containing model data</param>
    void createVertexBuffer(ModelBuffers& modelBuffer);

    /// <summary>
    /// take the modeldata en copy the indicies to the GPU
    /// </summary>
    /// <param name="modelBuffer">data struct containing model data</param>
    void createIndexBuffer(ModelBuffers& modelBuffer);

    /// <summary>
    /// create the buffer
    /// </summary>
    /// <param name="size"></param>
    /// <param name="usage"></param>
    /// <param name="properties"></param>
    /// <param name="buffer">buffer variable for access</param>
    /// <param name="bufferMemory">buffermemmory variable for access</param>
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    
    /// <summary>
    /// copy one buffer to another
    /// </summary>
    /// <param name="srcBuffer"></param>
    /// <param name="dstBuffer"></param>
    /// <param name="size"></param>
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    /// <summary>
    /// check the min alignment size and reserve memmory for the dynamic uniform buffer
    /// </summary>
    void prepareDanymicUniformBuffer();
    
    /// <summary>
    /// update the camera position
    /// </summary>
    /// <param name="currentImage">swapchain image(current frame)</param>
    void updateUniformBuffer(uint32_t currentImage);

    /// <summary>
    /// update all vehicle positions
    /// </summary>
    /// <param name="currentImage">swapchain image(current frame)</param>
    void updateDynamicUniformBuffer(uint32_t currentImage);

    /// <summary>
    /// update all lights
    /// </summary>
    /// <param name="currentImage">swapchain image(current frame)</param>
    void updateUboLights(uint32_t currentImage);

    /// <summary>
    /// create swapchain image
    /// </summary>
    /// <param name="width">window width</param>
    /// <param name="height">window heigth</param>
    /// <param name="numSamples"></param>
    /// <param name="format"></param>
    /// <param name="tiling"></param>
    /// <param name="usage"></param>
    /// <param name="properties"></param>
    /// <param name="image"></param>
    /// <param name="imageMemory"></param>
    void createImage(uint32_t width, uint32_t height, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
   
    /// <summary>
    /// start recording the command buffer
    /// </summary>
    /// <returns>command buffer thats being recorded</returns>
    VkCommandBuffer beginSingleTimeCommands();
    
    /// <summary>
    /// end the recording of the command buffer
    /// </summary>
    /// <param name="commandBuffer">commandbuffer to stop recording of</param>
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    
    /// <summary>
    /// make sure that the image has the correct layout
    /// </summary>
    /// <param name="image"></param>
    /// <param name="format">can be used for depth, but is not used here</param>
    /// <param name="oldLayout"></param>
    /// <param name="newLayout"></param>
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    
    /// <summary>
    /// record the coppy buffer to image command
    /// </summary>
    /// <param name="buffer"></param>
    /// <param name="image"></param>
    /// <param name="width"></param>
    /// <param name="height"></param>
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="image"></param>
    /// <param name="format"></param>
    /// <param name="aspectFlags"></param>
    /// <returns></returns>
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

    /// <summary>
    /// return supported depth format
    /// </summary>
    /// <returns>supported format</returns>
    VkFormat findDepthFormat();
    
    /// <summary>
    /// find supported format
    /// </summary>
    /// <param name="candidates">list of formats</param>
    /// <param name="tiling"></param>
    /// <param name="features"></param>
    /// <returns>supported format</returns>
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    
    /// <summary>
    /// check the stecil format
    /// </summary>
    /// <param name="format"></param>
    /// <returns>true or false</returns>
    bool hasStencilComponent(VkFormat format);

    /// <summary>
    /// check the highest supported msaa count by the GPU
    /// </summary>
    /// <returns>highest supported msaa</returns>
    VkSampleCountFlagBits getMaxUsableSampleCount();
};