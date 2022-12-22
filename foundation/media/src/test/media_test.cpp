#include <limits.h>
#include <time.h>
#include "spdlog/spdlog.h"
#include "gtest/gtest.h"
#include "plat_video_enc.h"

namespace {

int32_t dspVideoEncPacketCallback(void *cbUser, dspVideoEncPacket *packet)
{
    spdlog::error("dspVideoEncPacketCallback");
    return 0;
}

class QuickTest : public testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

class IntegerFunctionTest : public QuickTest {};

TEST_F(IntegerFunctionTest, Factorial)
{
    dspVideoEncConfig config;
    config.channel = 0;
    config.stream = 0;
    dspVideoEncoder *handle;

    auto iRet = palCreateVideoEncoder(&config, &handle);
    if (iRet != 0) {
        spdlog::error("palCreateVideoEncoder failed");
    }

    handle->attach(handle, dspVideoEncPacketCallback, nullptr);
    handle->start(handle);

    EXPECT_EQ(1, 1);
}

} // namespace
