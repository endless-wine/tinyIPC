#ifndef UTILS_NOCOPYABLE_H
#define UTILS_NOCOPYABLE_H

namespace EL {

#define DISALLOW_COPY_AND_MOVE(className) \
    DISALLOW_COPY(className);             \
    DISALLOW_MOVE(className)

#define DISALLOW_COPY(className)           \
    className(const className &) = delete; \
    className &operator=(const className &) = delete

#define DISALLOW_MOVE(className)      \
    className(className &&) = delete; \
    className &operator=(className &&) = delete

class NoCopyable {
protected:
    NoCopyable() {}
    virtual ~NoCopyable() {}

private:
    DISALLOW_COPY_AND_MOVE(NoCopyable);
};

} // namespace EL

#endif // UTILS_NOCOPYABLE_H
