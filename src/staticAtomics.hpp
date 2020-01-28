#pragma once

#include <atomic>

namespace StaticAtomics
{
    static std::atomic_bool* const running{new std::atomic_bool(true)};
}
