#include "config/config.h"
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <stdio.h>

namespace Endless {
namespace Common {

class CConfig : public IConfig {

public:
    CConfig();
    ~CConfig();

private:
    /* data */
};

} // namespace base
} // namespace endless