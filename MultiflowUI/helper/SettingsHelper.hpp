#pragma once

#include <QObject>
#include <QSettings>
#include <QScopedPointer>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>

#include "qml/mixin/SingletonMixin.hpp"
#include "qml/interface/IQmlSingleton.hpp"

#include <QVariant>
#include <QObject>

class SettingsHelper final : public QObject, public SingletonMixin<SettingsHelper>,
                             public IQmlSingleton<SettingsHelper> {
    Q_OBJECT

    explicit SettingsHelper(QObject* parent = nullptr);

    friend class SingletonMixin;

public:
    ~SettingsHelper() override = default;

    void init(const char* argv[]);

    Q_INVOKABLE void setRender(const QVariant& render) const;

    Q_INVOKABLE [[nodiscard]] QVariant getRender() const;

    Q_INVOKABLE void setDarkMode(int darkModel) const;

    Q_INVOKABLE [[nodiscard]] QVariant getDarkMode() const;

    Q_INVOKABLE void setVsync(bool vsync) const;

    Q_INVOKABLE [[nodiscard]] QVariant getVsync() const;

private:
    void _set(const QString& key, const QVariant& val) const;

    [[nodiscard]] QVariant _get(const QString& key, QVariant def = {}) const;

    QScopedPointer<QSettings> _settings;
};
