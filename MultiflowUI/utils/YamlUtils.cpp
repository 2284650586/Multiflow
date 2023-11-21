//
// Created by miku on 11/20/2023.
//

#include "YamlUtils.hpp"

#include <QFile>

#include <string>

bool YamlUtils::loadFromQResourcePath(const QString& path, YAML::Node& outNode) {
    QFile file{path};
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    const std::string content = file.readAll().toStdString();
    outNode = YAML::Load(content);
    file.close();
    return true;
}
