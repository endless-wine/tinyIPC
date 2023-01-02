#include "common/config.h"
#include <chrono>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <stdio.h>
#include <thread>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    spdlog::info("application start");

    nlohmann::json param;
    param["FirstPath"] = "firstPath";
    param["SecondPath"] = "secondPath";
    param["DefaultPath"] = "defaultPath";
    Endless::Common::IConfig::GetInstance().LoadConfig(param);

    Endless::Common::IConfig::GetInstance().Attach(
        "record", [](const nlohmann::json &config) { spdlog::info("on config record {}", config.dump().c_str()); });

    nlohmann::json record;
    record["enable"] = true;
    Endless::Common::IConfig::GetInstance().SetConfig("record", record);

    record.clear();
    Endless::Common::IConfig::GetInstance().GetConfig("record", record);
    spdlog::info("config record {}", record.dump().c_str());

    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}