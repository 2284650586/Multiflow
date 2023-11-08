//
// Created by miku on 11/7/2023.
//

#include "settings_helper.hpp"

#include "MultiflowLibrary/logging/logging.hpp"

#include <QDataStream>
#include <QStandardPaths>

SettingsHelper::SettingsHelper(QObject* parent)
    : QObject(parent),
      IQmlSingleton<SettingsHelper>("Multiflow.UI", 1, 0, "SettingsHelper") {

}

SettingsHelper::~SettingsHelper() = default;

void SettingsHelper::save(const QString& key, const QVariant& val) {
    QByteArray data = {};
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_5);
    stream << val;
    m_settings->setValue(key, data);
}

QVariant SettingsHelper::get(const QString& key, QVariant def) {
    const QByteArray data = m_settings->value(key).toByteArray();
    if (data.isEmpty()) {
        return def;
    }
    QDataStream stream(data);
    stream.setVersion(QDataStream::Qt_6_5);
    QVariant val;
    stream >> val;
    return val;
}

void SettingsHelper::init(char* argv[]) {
    auto applicationPath = QString::fromStdString(argv[0]);
    const QFileInfo fileInfo(applicationPath);
    const QString iniFileName = fileInfo.completeBaseName() + ".ini";
    const QString iniFilePath =
        QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/" + iniFileName;
    info("Application configuration file path {}", iniFilePath.toStdString());
    m_settings.reset(new QSettings(iniFilePath, QSettings::IniFormat));
}
