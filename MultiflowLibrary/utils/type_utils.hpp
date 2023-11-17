//
// Created by miku on 11/5/2023.
//

#pragma once

#include <memory>

namespace ml {
    template<class Derived, class Base>
    bool instance_of(const Base& object) {
        return dynamic_cast<const Derived*>(&object) != nullptr;
    }

    template<class Derived, class Base>
    bool instance_of(std::shared_ptr<Base> object) {
        return std::dynamic_pointer_cast<Derived>(object) != nullptr;
    }

    template<class Derived, class Base>
    std::shared_ptr<Derived> as(std::shared_ptr<Base> object) {
        return std::dynamic_pointer_cast<Derived>(object);
    }
}
