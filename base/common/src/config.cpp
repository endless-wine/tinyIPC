#include "config.h"
#include "utils/file_ex.h"

namespace Endless {
namespace Common {

CConfig &CConfig::GetInstance()
{
    static CConfig sConfig;
    return sConfig;
}

IConfig &IConfig::GetInstance()
{
    return CConfig::GetInstance();
}

bool CConfig::LoadConfig(nlohmann::json &param)
{
    firstPath_ = param["FirstPath"].get<std::string>();
    secondPath_ = param["SecondPath"].get<std::string>();
    defaultPath_ = param["DefaultPath"].get<std::string>();

    if (!ReadConfigFromFile(firstPath_, secondPath_, config_)) {
        return false;
    }

    return true;
}

bool CConfig::ReadFile(const std::string &path, nlohmann::json &root)
{
    if (path.empty()) {
        return false;
    }

    std::vector<char> content;
    if (LoadBufferFromFile(path.c_str(), content)) {
        root = nlohmann::json::parse(content);
        return false;
    }
    return true;
}

bool CConfig::CopyFile(const std::string &from, const std::string &to)
{
    std::vector<char> content;
    if (!LoadBufferFromFile(from, content)) {
        spdlog::error("CopyFile LoadBufferFromFile failed. from:{}, to:{} ", from, to);
        return false;
    }

    if (!SaveBufferToFile(to, content, true)) {
        spdlog::error("CopyFile SaveBufferToFile failed. from:{}, to:{} ", from, to);
        return false;
    }

    return true;
}

bool CConfig::ReadConfigFromFile(const std::string &firstFilePath,
                                 const std::string &secondFilePath,
                                 nlohmann::json &config)
{
    if (!ReadFile(firstFilePath, config)) {
        if (!ReadFile(secondFilePath, config)) {
            spdlog::warn("read config files failed. firstFilePath:{}, secondFilePath:{} ", firstFilePath.c_str(),
                         secondFilePath.c_str());
            return false;
        } else {
            if (!CopyFile(secondFilePath.c_str(), firstFilePath.c_str())) {
                spdlog::warn("copy config files failed. from {}, to {} ", secondFilePath.c_str(),
                             firstFilePath.c_str());
            }
        }
    } else {
        if (!CopyFile(firstFilePath.c_str(), secondFilePath.c_str())) {
            spdlog::warn("copy config files failed. from {}, to {} ", firstFilePath.c_str(), secondFilePath.c_str());
        }
    }
    return true;
}

bool CConfig::GetConfig(const std::string &name, nlohmann::json &config)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (name == "All") {
        config = config_;
        return true;
    }

    config_.at(name).get_to(config);
    if (config.empty()) {
        spdlog::warn("GetConfig failed. name:{}", name);
        return false;
    }
    return true;
}

bool CConfig::SetConfig(const std::string &name, const nlohmann::json &config)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (name == "All") {
        config_ = config;
        return true;
    }
    config_[name] = config;

    return true;
}

} // namespace Common
} // namespace Endless