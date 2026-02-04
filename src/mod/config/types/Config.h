#pragma once

#include <string>

namespace placeholder::config {

struct Config {
    int         version                            = 1;
    std::string defaultLocaleCode                  = "en_US";
    bool        replaceLeviLaminaDefaultLocaleCode = true;
};

} // namespace placeholder::config