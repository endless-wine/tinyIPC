#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <stdio.h>

namespace endless {
namespace base {

class CConfig : public IConfig {

public:
    IConfig();
    ~IConfig();

private:
    /* data */
};

} // namespace base
} // namespace endless