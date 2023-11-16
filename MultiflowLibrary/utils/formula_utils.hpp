//
// Created by miku on 11/15/2023.
//

#pragma once

#include "expression/expression.hpp"

#include <memory>
#include <vector>

namespace ml {
void _internalExtractVariablesAndConstants(
    const std::shared_ptr<Expression>& expression,
    std::vector<std::shared_ptr<Expression>>& ret
);
}
