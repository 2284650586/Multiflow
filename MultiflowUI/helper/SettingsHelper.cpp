//
// Created by miku on 11/7/2023.
//

#include "SettingsHelper.hpp"

#include "MultiflowLibrary/logging/logging.hpp"

#include <QDataStream>
#include <QStandardPaths>
#include <QString>

SettingsHelper::SettingsHelper(QObject* parent)
    : QObject(parent),
      IQmlSingleton("Multiflow.UI", 1, 0, "SettingsHelper") {

}

SettingsHelper::~SettingsHelper() = default;

void SettingsHelper::save(const QString& key, const QVariant& val) const {
    QByteArray data = {};
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_5);
    stream << val;
    m_settings->setValue(key, data);
}

QVariant SettingsHelper::get(const QString& key, QVariant def) const {
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

void SettingsHelper::init(const char* argv[]) {
    const auto applicationPath = QString::fromStdString(argv[0]);
    const QFileInfo fileInfo(applicationPath);
    const QString iniFileName = fileInfo.completeBaseName() + ".ini";
    const QString iniFilePath =
        QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/" + iniFileName;
    log_info("Application configuration file path {}", iniFilePath.toStdString());
    m_settings.reset(new QSettings(iniFilePath, QSettings::IniFormat));
}
