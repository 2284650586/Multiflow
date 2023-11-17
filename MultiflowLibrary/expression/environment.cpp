//
// Created by miku on 11/5/2023.
//

#include "environment.hpp"

ml::Environment::Environment(const Environment& env) {
    this->env = env.env;
}

void ml::Environment::set(const std::string &name, const Number value) {
    env[name] = value;
}

ml::Number ml::Environment::get(const std::string &name) const {
    if (!present(name)) {
        throw KeyNotFoundException();
    }
    return env.at(name);
}

bool ml::Environment::present(const std::string &name) const {
    return env.contains(name);
}
