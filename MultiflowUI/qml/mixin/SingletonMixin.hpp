//
// Created by miku on 2023/10/21.
//

#pragma once

template<typename T>
class SingletonMixin {
public:
    static T *getInstance() {
        static T* instance;
        if (instance == nullptr) {
            instance = new T();
        }
        return instance;
    }
};
