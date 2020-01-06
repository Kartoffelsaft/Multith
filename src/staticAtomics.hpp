#pragma once

#include <atomic>

namespace StaticAtomics
{
    static std::atomic_bool running{true};
}
