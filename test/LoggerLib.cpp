#include "LoggerLib.h"
#include <chrono>
#include <thread>

int main()
{
    DEBUG("Debug here!");
    LOG("Log here!");
    WARN("Warning here!");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    ERROR("Error here!");
    return 0;
}