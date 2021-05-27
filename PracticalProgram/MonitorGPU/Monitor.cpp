
#include <iostream>
#include<string>
#include<windows.h>
#include "nvml.h"
using namespace std;
int main()
{
    nvmlReturn_t result;
    unsigned int device_count, i;
    // First initialize NVML library
    result = nvmlInit();
 
    result = nvmlDeviceGetCount(&device_count);
    if (NVML_SUCCESS != result)
    {
        std::cout << "Failed to query device count: " << nvmlErrorString(result);
    }
    std::cout << "Found" << device_count <<" device" << endl;
 
    std::cout << "Listing devices:";
    while (true)
    {
        for (i = 0; i < device_count; i++)
        {
            nvmlDevice_t device;
            char name[NVML_DEVICE_NAME_BUFFER_SIZE];
            nvmlPciInfo_t pci;
            result = nvmlDeviceGetHandleByIndex(i, &device);
            if (NVML_SUCCESS != result) {
                std::cout << "get device failed " << endl;
            }
            result = nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_BUFFER_SIZE);
            if (NVML_SUCCESS != result) {
                std::cout << "GPU name： " << name << endl;
            }
            //使用率
            nvmlUtilization_t utilization;
            result = nvmlDeviceGetUtilizationRates(device, &utilization);
            if (NVML_SUCCESS == result)
            {
                std::cout << "----- 使用率 ----- " << endl;
                std::cout << "GPU 使用率： " << utilization.gpu << endl;
                std::cout << "显存使用率 " << utilization.memory << endl;
            }
        }
        Sleep(1000);
    }
    return 0;
