#pragma once

#include <QObject>
#include <QSettings>
#include <QScopedPointer>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>

#include "qml/mixin/SingletonMixin.hpp"
#include "qml/interface/IQmlSingleton.hpp"

class SettingsHelper : public QObject, public SingletonMixin<SettingsHelper>, public IQmlSingleton<SettingsHelper> {
Q_OBJECT

explicit SettingsHelper(QObject* parent = nullptr);

friend class SingletonMixin;

public:
    ~SettingsHelper() override;

    void init(const char* argv[]);

    Q_INVOKABLE void setRender(const QVariant& render) { save("render", render); }

    Q_INVOKABLE QVariant getRender() { return get("render"); }

    Q_INVOKABLE void setDarkMode(int darkModel) { save("darkMode", darkModel); }

    Q_INVOKABLE QVariant getDarkMode() { return get("darkMode", QVariant(0)); }

    Q_INVOKABLE void setVsync(bool vsync) { save("vsync", vsync); }

    Q_INVOKABLE QVariant getVsync() { return get("vsync", QVariant(true)); }

private:
    void save(const QString& key, const QVariant& val) const;

    [[nodiscard]] QVariant get(const QString& key, QVariant def = {}) const;

private:
    QScopedPointer<QSettings> m_settings;
};
