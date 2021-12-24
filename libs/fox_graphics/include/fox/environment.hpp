#pragma once
#include<vulkan/vulkan.h>
#include<mutex>
#include<cstdint>
#include <cassert>
enum {
    MAX_QUEUE_FAMILES = 8,
    MAX_QUEUE_PER_FAMILY =8,
};

struct foxQueueFamily {

    VkQueueFlags flags;

    uint32_t family;  /// 
    uint32_t numQueues;
    
    std::mutex sync[MAX_QUEUE_PER_FAMILY];
    VkQueue queue[MAX_QUEUE_PER_FAMILY];

    void createQueueFamily(VkDevice device,VkQueueFlags flags, uint32_t family, uint32_t numQueues)
    {
        assert(numQueues < MAX_QUEUE_PER_FAMILY);
        std::fill_n(queue,numQueues,VK_NULL_HANDLE);
        this->family = family;
        this->flags = flags;
        this->numQueues = numQueues;

        for (size_t i = 0; i < numQueues; i++)
        {
            this->sync[i].unlock();
            vkGetDeviceQueue(device,family,i,&queue[i]);
        }    
    }
};



struct foxEnvironment {
    VkInstance instance{VK_NULL_HANDLE};
    VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};
    VkDevice device{VK_NULL_HANDLE};
    uint32_t numQueueFamilies;
    foxQueueFamily* queueFamiles;
};

VkResult foxCreateEnvironment(foxEnvironment** env);

void foxDesroyEnvironment(foxEnvironment* env);

