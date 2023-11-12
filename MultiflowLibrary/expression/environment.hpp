//
// Created by miku on 11/5/2023.
//

#pragma once

#include <string>
#include <map>
#include <stdexcept>

namespace ml {

using Number = double;

class  __declspec(dllexport) Environment {
private:
    std::map<std::string, ml::Number> env;

public:
    explicit Environment() = default;
    virtual ~Environment() = default;

    void set(const std::string& name, ml::Number value);
    ml::Number get(const std::string& name) const;
    bool present(const std::string& name) const;
};

class KeyNotFoundException : public std::exception {};

}
