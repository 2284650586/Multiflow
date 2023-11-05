//
// Created by miku on 11/5/2023.
//

#pragma once

#include <type_traits>
#include <typeinfo>

namespace ml {
    template<class Derived, class Base>
    bool instance_of(const Base& object) {
        return dynamic_cast<const Derived*>(&object) != nullptr;
    }
}
