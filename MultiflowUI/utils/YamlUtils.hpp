//
// Created by miku on 11/20/2023.
//

#pragma once

#ifndef OUT
#define OUT
#endif

#include <yaml-cpp/yaml.h>

#include <QString>

class YamlUtils {
public:
    static bool loadFromQResourcePath(const QString& path, YAML::Node& outNode);
};
