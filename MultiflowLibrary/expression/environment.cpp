//
// Created by miku on 11/5/2023.
//

#include "environment.hpp"

#include <logging/logging.hpp>

ml::Environment::Environment(std::initializer_list<std::pair<std::string, Number>> init) {
    for (const auto& [k, v]: init) {
        log_debug("Environment: set {} = {}", k, v);
        _env[k] = v;
    }
}

ml::Environment::Environment(const Environment& env) {
    this->_env = env._env;
}

void ml::Environment::set(const std::string& name, const Number value) {
    log_debug("Environment: set {} = {}", name, value);
    _env[name] = value;
}

ml::Number ml::Environment::get(const std::string& name) const {
    if (!present(name)) {
        log_error("Environment: key not found: {}", name);
        throw KeyNotFoundException();
    }
    return _env.at(name);
}

bool ml::Environment::present(const std::string& name) const {
    return _env.contains(name);
}
