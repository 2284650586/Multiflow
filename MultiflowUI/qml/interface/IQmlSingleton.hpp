#pragma once

#include <QString>
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qml/interface/IQmlObject.hpp"
#include "qml/mixin/SingletonMixin.hpp"

template<typename Derived>
class IQmlSingleton: public IQmlObject<Derived> {
protected:
    IQmlSingleton(const char* uri, int majorVersion, int minorVersion, const char* name)
    : IQmlObject<Derived>(uri, majorVersion, minorVersion, name) {
    }

public:
    virtual void registerSingleton(const QQmlApplicationEngine& engine) {
        qmlRegisterSingletonType<Derived>(
            this->uri,
            this->majorVersion,
            this->minorVersion,
            this->name, [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject* {
            Q_UNUSED(engine)
            Q_UNUSED(scriptEngine)
            return Derived::getInstance();
        });
        engine.rootContext()->setContextProperty(this->name, Derived::getInstance());
    }
};
