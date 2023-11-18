//
// Created by miku on 11/5/2023.
//

#pragma once

#include "MultiflowLibrary_global.hpp"

#include <string>
#include <map>
#include <stdexcept>

namespace ml {
using Number = double;

class ML_PUBLIC Environment final {
    std::map<std::string, Number> env{};

public:
    explicit Environment() = default;

    Environment(const Environment& env);

    ~Environment() = default;

    void set(const std::string& name, Number value);

    [[nodiscard]] Number get(const std::string& name) const;

    [[nodiscard]] bool present(const std::string& name) const;
};

class KeyNotFoundException final : public std::exception {
};
}
