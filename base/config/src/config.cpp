#include "config.h"
#include "utils/file_ex.h"
#include <algorithm>

namespace EL {
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
    if (!LoadBufferFromFile(path.c_str(), content)) {
        return false;
    }
    root = nlohmann::json::parse(content);
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

bool CConfig::WriteFile(const std::string &path, const nlohmann::json &root)
{
    if (path.empty()) {
        return false;
    }

    std::string json = root.dump();
    std::vector<char> content;
    content.assign(json.begin(), json.end());
    if (!SaveBufferToFile(path, content, true)) {
        return false;
    }

    return true;
}

bool CConfig::SaveFile()
{
    std::lock_guard<std::mutex> lock(mutex_);

    // 保存配置文件
    WriteFile(firstPath_, config_);
    WriteFile(secondPath_, config_);
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
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (name == "All") {
            config_ = config;
        } else {
            OnProc(name, config);
            config_[name] = config;
        }
    }

    SaveFile();

    return true;
}

int32_t CConfig::Attach(const std::string &name, Proc proc)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = procs_.find(name);
    if (it == procs_.end()) {
        std::vector<std::pair<int32_t, Proc>> procs;
        procs.push_back(std::make_pair(++count_, proc));
        procs_[name] = procs;
    } else {
        it->second.push_back(std::make_pair(++count_, proc));
    }

    return count_;
}

bool CConfig::Detach(const std::string &name, int32_t handle)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = procs_.find(name);
    if (it == procs_.end()) {
        return false;
    }

    auto &procs = it->second;
    auto itProc = std::find_if(procs.begin(), procs.end(), [handle](const std::pair<int32_t, Proc> &proc) {
        if (proc.first == handle) {
            return true;
        }
        return false;
    });

    if (itProc == procs.end()) {
        return false;
    }
    procs.erase(itProc);
    return true;
}

bool CConfig::OnProc(const std::string &name, const nlohmann::json &config)
{
    auto it = procs_.find(name);
    if (it == procs_.end()) {
        return false;
    }

    auto &procs = it->second;
    for (auto &proc : procs) {
        proc.second(config);
    }

    return true;
}

} // namespace Common
} // namespace EL