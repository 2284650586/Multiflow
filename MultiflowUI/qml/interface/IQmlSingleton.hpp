#pragma once

#include <QString>
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

#include "qml/interface/IQmlObject.hpp"
#include "qml/mixin/SingletonMixin.hpp"

template<typename Derived>
class IQmlSingleton: public IQmlObject<Derived> {
protected:
    IQmlSingleton(const char* uri, int majorVersion, int minorVersion, const char* name)
    : IQmlObject<Derived>(uri, majorVersion, minorVersion, name) {
    }

public:
    virtual void registerSingleton() {
        qmlRegisterSingletonType<Derived>(
            this->uri,
            this->majorVersion,
            this->minorVersion,
            this->name, [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject* {
            Q_UNUSED(engine)
            Q_UNUSED(scriptEngine)
            return Derived::getInstance();
        });
    }
};
