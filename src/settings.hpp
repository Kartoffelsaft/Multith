#pragma once

#include "../tomlplusplus/toml.hpp"

struct Settings
{
    Settings(toml::parse_result config)
    {
        filmgrainEnabled = config
            ["Graphics"]
            ["PostProcesing"]
            ["filmgrainEnabled"]
            .value_or(false);
        filmgrainIntensity = config
            ["Graphics"]
            ["PostProcesing"]
            ["filmgrainEnabled"]
            .value_or(0.0);
    }

    bool filmgrainEnabled;
    float filmgrainIntensity;
};
