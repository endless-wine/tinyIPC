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
    CConfig();
    ~CConfig() override = default;

    static CConfig &GetInstance();

    /**
     * @brief Load config from file
     * "FirstPath" : "/mnt/config/config1", //第一个配置文件路径
     * "SecondPath" : "/mnt/config/config2", //第二个配置文件路径
     * "DefaultPath": "/mnt/config/defaultConfig", //默认配置文件路径
     */
    bool LoadConfig(nlohmann::json &param) override;

    bool GetConfig(const std::string &name, nlohmann::json &config) override;
    
    bool SetConfig(const std::string &name, const nlohmann::json &config) override;

private:
    bool ReadFile(const std::string &path, nlohmann::json &root);
    bool ReadConfigFromFile(const std::string &firstFilePath,
                            const std::string &secondFilePath,
                            nlohmann::json &config);
    bool CopyFile(const std::string &from, const std::string &to);

private:
    std::string firstPath_;
    std::string secondPath_;
    std::string defaultPath_;

    nlohmann::json config_;
    std::mutex mutex_;
};

} // namespace Common
} // namespace Endless