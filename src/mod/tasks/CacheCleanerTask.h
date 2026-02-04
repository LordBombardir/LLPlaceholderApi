#pragma once

#include <functional>

namespace placeholder {

class CacheCleanerTask final {
public:
    static bool enable();
    static void disable();

private:
    static bool isStarted;

    static std::function<void()> function;
};

} // namespace placeholder