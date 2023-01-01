#pragma once

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <stdio.h>

namespace Endless {
namespace Common {

class IConfig {

public:
    using Proc = std::function<void(const nlohmann::json &config)>;

    IConfig() = default;
    virtual ~IConfig() = default;

    static IConfig &GetInstance();

    virtual bool LoadConfig(nlohmann::json &param) = 0;

    virtual bool GetConfig(const std::string &name, nlohmann::json &config) = 0;

    virtual bool SetConfig(const std::string &name, const nlohmann::json &config) = 0;

    virtual int32_t Attach(const std::string &name, Proc proc) = 0;

    virtual bool Detach(const std::string &name, int32_t handle) = 0;

};

} // namespace Common
} // namespace Endless