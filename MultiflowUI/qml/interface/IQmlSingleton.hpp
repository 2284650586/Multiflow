#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qml/interface/IQmlObject.hpp"

template<typename Derived>
class IQmlSingleton : public IQmlObject<Derived> {
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
            this->name, [](const QQmlEngine*, const QJSEngine*) -> QObject* {
                return Derived::getInstance();
            });
        engine.rootContext()->setContextProperty(this->name, Derived::getInstance());
    }

    virtual ~IQmlSingleton() = default;
};
