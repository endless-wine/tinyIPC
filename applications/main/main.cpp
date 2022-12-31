#include <stdio.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <thread>
#include <chrono>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    nlohmann::json json;
    json["hello"] = "world";
    spdlog::info("sky start {}", json.dump().c_str());

    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}