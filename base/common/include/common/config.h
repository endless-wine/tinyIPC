#pragma once

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <stdio.h>

namespace Endless {
namespace Common {

class IConfig {

public:
    IConfig() = default;
    virtual ~IConfig() = default;

    static IConfig &GetInstance();

    virtual bool LoadConfig(nlohmann::json &param) = 0;

    virtual bool GetConfig(const std::string &name, nlohmann::json &config) = 0;

    virtual bool SetConfig(const std::string &name, const nlohmann::json &config) = 0;

private:
    /* data */
};

} // namespace Common
} // namespace Endless