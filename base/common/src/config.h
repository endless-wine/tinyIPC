#include "common/config.h"
#include <mutex>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <stdio.h>
#include <string>

namespace Endless {
namespace Common {

class CConfig : public IConfig {

public:
    CConfig() = default;
    ~CConfig() override = default;

    static CConfig &GetInstance();

    /**
     * @brief Load config from file
     * "FirstPath" : "/config/config1", //第一个配置文件路径
     * "SecondPath" : "/config/config2", //第二个配置文件路径
     * "DefaultPath": "/config/defaultConfig", //默认配置文件路径
     */
    bool LoadConfig(nlohmann::json &param) override;

    bool GetConfig(const std::string &name, nlohmann::json &config) override;

    bool SetConfig(const std::string &name, const nlohmann::json &config) override;

    int32_t Attach(const std::string &name, Proc proc) override;

    bool Detach(const std::string &name, int32_t handle) override;

private:
    bool ReadFile(const std::string &path, nlohmann::json &root);
    bool ReadConfigFromFile(const std::string &firstFilePath,
                            const std::string &secondFilePath,
                            nlohmann::json &config);
    bool CopyFile(const std::string &from, const std::string &to);
    bool WriteFile(const std::string &path, const nlohmann::json &root);
    bool SaveFile();
    bool OnProc(const std::string &name, const nlohmann::json &config);

private:
    std::string firstPath_;
    std::string secondPath_;
    std::string defaultPath_;
    nlohmann::json config_;
    std::mutex mutex_;
    std::map<std::string, std::vector<std::pair<int32_t, Proc>>> procs_;
    int32_t count_{0};
};

} // namespace Common
} // namespace Endless