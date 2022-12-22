#pragma once

#define ACE_DISALLOW_COPY_AND_MOVE(className) \
    ACE_DISALLOW_COPY(className);             \
    ACE_DISALLOW_MOVE(className)

#define ACE_DISALLOW_COPY(className)      \
    className(const className&) = delete; \
    className& operator=(const className&) = delete

#define ACE_DISALLOW_MOVE(className) \
    className(className&&) = delete; \
    className& operator=(className&&) = delete

namespace ti {

class NonCopyable {
protected:
    NonCopyable() = default;
    virtual ~NonCopyable() = default;

private:
    ACE_DISALLOW_COPY_AND_MOVE(NonCopyable);
};

}
