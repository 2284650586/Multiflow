#pragma once

#include <QObject>
#include <QQmlEngine>

template<typename T>
class IQmlObject {
protected:
    const char* uri;
    int majorVersion;
    int minorVersion;
    const char* name;

    IQmlObject(const char* uri, const int majorVersion, const int minorVersion, const char* name)
    : uri(uri), majorVersion(majorVersion), minorVersion(minorVersion), name(name) {
    }
public:
    virtual void registerObjectType() {
        qmlRegisterType<T>(uri, majorVersion, minorVersion, name);
    }

    virtual ~IQmlObject() = default;
};
