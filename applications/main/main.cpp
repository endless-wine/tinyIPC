#include <stdio.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <thread>
#include <chrono>
#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    nlohmann::json json;
    json["hello"] = "world";
    spdlog::info("sky start {}", json.dump().c_str());

    // 启动测试框架
    ::testing::InitGoogleTest();
    RUN_ALL_TESTS();

    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}