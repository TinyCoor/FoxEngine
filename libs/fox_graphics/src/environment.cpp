#include"fox/environment.hpp"
#include<memory>

VkResult foxCreateEnvironment(foxEnvironment** env)
{
    auto* pEnv = new foxEnvironment;
    *pEnv ={};

      /// Instance 
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "FoxEngineApp";
    appInfo.pNext = nullptr;
    appInfo.pEngineName = "FoxEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.apiVersion= VK_MAKE_VERSION(1,0,0);

    /// GLFW extensions
    // uint32_t extensionsCount = 0;
    // const char** extensionNames = foxWindowGetVulkanExtensions(&extensionsCount);

    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;
    // instanceInfo.ppEnabledExtensionNames = extensionNames;
    // instanceInfo.enabledExtensionCount = extensionsCount;
    instanceInfo.enabledLayerCount = 0;
    instanceInfo.ppEnabledLayerNames = nullptr;

    auto result = vkCreateInstance(&instanceInfo,nullptr,&(pEnv->instance));
    if (result !=VK_SUCCESS)
    {
        // log
        return VK_SUCCESS;
    }

    /// physical device
    uint32_t physicalDeviceCount = 0;
    result= vkEnumeratePhysicalDevices(pEnv->instance,&physicalDeviceCount,nullptr);
    /// todo test it success 
    std::unique_ptr<VkPhysicalDevice[]> physDevices(new VkPhysicalDevice[physicalDeviceCount]);
    result= vkEnumeratePhysicalDevices(pEnv->instance,&physicalDeviceCount,physDevices.get());
    pEnv->physicalDevice= physDevices[0];

    /// logical device


    ///Queues 
    uint32_t queueFamilyCount =0;
    vkGetPhysicalDeviceQueueFamilyProperties(pEnv->physicalDevice,&queueFamilyCount,nullptr);
    std::unique_ptr<VkQueueFamilyProperties[]> queueProperties(new VkQueueFamilyProperties[queueFamilyCount]);
    vkGetPhysicalDeviceQueueFamilyProperties(pEnv->physicalDevice,&queueFamilyCount,queueProperties.get());

    std::unique_ptr<VkDeviceQueueCreateInfo[]> queueInfos(new VkDeviceQueueCreateInfo[queueFamilyCount]);
    uint32_t nextQueueCount = 0;
    for (size_t i = 0; i < queueFamilyCount; i++)
    {
        queueInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfos[i].queueFamilyIndex= i;
        queueInfos[i].queueCount = queueProperties[i].queueCount;
        nextQueueCount = std::max(nextQueueCount,queueProperties[i].queueCount);
    }

    std::unique_ptr<float[]> queuePriorities(new float[nextQueueCount]);
    std::fill_n(queuePriorities.get(),nextQueueCount,0.f);
    for (size_t i = 0; i < queueFamilyCount; i++)
    {
        queueInfos[i].pQueuePriorities= queuePriorities.get();
    }

    VkDeviceCreateInfo deviceInfo{};
    deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.queueCreateInfoCount = queueFamilyCount;
    deviceInfo.pQueueCreateInfos = queueInfos.get();
    
    result = vkCreateDevice(physDevices[0],&deviceInfo,nullptr,&(pEnv->device));
    if (result !=VK_SUCCESS)
    {
        // log
        return VK_SUCCESS;
    }

    uint32_t numQueueFamiles= queueFamilyCount;
    foxQueueFamily queueFamilies[MAX_QUEUE_FAMILES];
    for (size_t i = 0; i < numQueueFamiles; i++)
    {
        queueFamilies[i].createQueueFamily(pEnv->device,queueProperties[i].queueFlags,i,queueProperties[i].queueCount);    
    }

    *env = pEnv;
    return VK_SUCCESS;
    
}


void foxDesroyEnvironment(foxEnvironment* env)
{
    vkDestroyDevice(env->device,nullptr);
    vkDestroyInstance(env->instance,nullptr);

    delete env;
    env =nullptr;
}