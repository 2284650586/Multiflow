#pragma once

template<typename T>
class StaticConstructorMixin {
public:
    static T *createInstance() {
        return new T();
    }
};
