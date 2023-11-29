//
// Created by miku on 11/21/2023.
//

#include "MIndependentVariables.hpp"

#include <logging/logging.hpp>

MIndependentVariables::MIndependentVariables(QObject* parent): QObject(parent) {
}

size_t MIndependentVariables::size(const QString& category) const {
    return _variables[category].size();
}

void MIndependentVariables::createEmpty(const QString& category) {
    _variables[category].push_back(QMap<QString, QVariant>{});
    emit sizeChanged(category);
}

void MIndependentVariables::remove(const QString& category, const int index) {
    log_debug("Removing IV (size={}) at index {}", _variables[category].size(), index);
    auto& m = _variables[category];
    if (index >= m.size()) {
        return;
    }
    m.remove(index);
    emit sizeChanged(category);
}

void MIndependentVariables::set(const QString& category, const int index, const QString& key, const QVariant& value) {
    auto& m = _variables[category];
    if (index >= m.size()) {
        return;
    }
    m[index][key] = value;
    emit propertyChanged(category);
}

QVariant MIndependentVariables::get(const QString& category, const int index, const QString& key) const {
    const QVector<QMap<QString, QVariant>>& v = _variables[category];
    if (index >= v.size()) {
        log_critical("IV at index {} does not exist", index);
        return QVariant::fromValue(QString{});
    }

    const QMap<QString, QVariant>& m = v[index];
    if (!m.contains(key)) {
        return QVariant::fromValue(QString{});
    }
    return m[key];
}

QVariant MIndependentVariables::getMaps(const QString& category) const {
    return QVariant::fromValue(get(category));
}

const QVector<QMap<QString, QVariant>>& MIndependentVariables::get(const QString& category) const {
    static const QVector<QMap<QString, QVariant>> empty{};
    if (const auto it = _variables.find(category); it != _variables.end()) {
        return it.value();
    }
    return empty;
}
