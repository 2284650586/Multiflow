//
// Created by miku on 11/7/2023.
//

#include "SettingsHelper.hpp"

#include "MultiflowLibrary/logging/logging.hpp"

#include <QDataStream>
#include <QStandardPaths>
#include <QString>
#include <QByteArray>
#include <QIODevice>

SettingsHelper::SettingsHelper(QObject* parent)
    : QObject(parent),
      IQmlSingleton("Multiflow.UI", 1, 0, "SettingsHelper") {

}

QVariant SettingsHelper::getRender() const {
    return _get("render");
}

void SettingsHelper::setDarkMode(const int darkModel) const {
    _set("darkMode", darkModel);
}

QVariant SettingsHelper::getDarkMode() const {
    return _get("darkMode", QVariant(0));
}

void SettingsHelper::setVsync(const bool vsync) const {
    _set("vsync", vsync);
}

QVariant SettingsHelper::getVsync() const {
    return _get("vsync", QVariant(true));
}

void SettingsHelper::setRender(const QVariant& render) const {
    _set("render", render);
}

void SettingsHelper::_set(const QString& key, const QVariant& val) const {
    QByteArray data = {};
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_5);
    stream << val;
    _settings->setValue(key, data);
}

QVariant SettingsHelper::_get(const QString& key, QVariant def) const {
    const QByteArray data = _settings->value(key).toByteArray();
    if (data.isEmpty()) {
        return def;
    }
    QDataStream stream(data);
    stream.setVersion(QDataStream::Qt_6_5);
    QVariant val;
    stream >> val;
    return val;
}

void SettingsHelper::init(const char* argv[]) {
    const auto applicationPath = QString::fromStdString(argv[0]);
    const QFileInfo fileInfo(applicationPath);
    const QString iniFileName = fileInfo.completeBaseName() + ".ini";
    const QString iniFilePath =
        QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/" + iniFileName;
    log_info("Application configuration file path {}", iniFilePath.toStdString());
    _settings.reset(new QSettings(iniFilePath, QSettings::IniFormat));
}
