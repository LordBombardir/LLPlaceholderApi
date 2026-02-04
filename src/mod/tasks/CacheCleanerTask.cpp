#include "CacheCleanerTask.h"
#include "../core/MainManager.h"
#include "../placeholders/PlaceholdersManager.h"

#include <ll/api/coro/CoroTask.h>
#include <ll/api/thread/ServerThreadExecutor.h>

namespace placeholder {

bool CacheCleanerTask::isStarted = false;

std::function<void()> CacheCleanerTask::function = {};

bool CacheCleanerTask::enable() {
    if (isStarted) {
        return false;
    }

    function = []() -> void {
        PlaceholdersManager::cleanPackets();
        MainManager::cleanTemporaryPlaceholders();
    };

    using namespace std::chrono_literals;
    ll::coro::keepThis([function = &function]() -> ll::coro::CoroTask<> {
        while (true) {
            co_await 1s;
            (*function)();
        }
        co_return;
    }).launch(ll::thread::ServerThreadExecutor::getDefault());

    isStarted = true;
    return true;
}

void CacheCleanerTask::disable() {
    isStarted = false;
    function  = {};
}

} // namespace placeholder