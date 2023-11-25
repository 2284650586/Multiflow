//
// Created by miku on 11/5/2023.
//

#include "environment.hpp"

ml::Environment::Environment(std::initializer_list<std::pair<std::string, Number>> init) {
    for (const auto& [k, v]: init) {
        _env[k] = v;
    }
}

ml::Environment::Environment(const Environment& env) {
    this->_env = env._env;
}

void ml::Environment::set(const std::string& name, const Number value) {
    _env[name] = value;
}

ml::Number ml::Environment::get(const std::string& name) const {
    if (!present(name)) {
        throw KeyNotFoundException();
    }
    return _env.at(name);
}

bool ml::Environment::present(const std::string& name) const {
    return _env.contains(name);
}
