#pragma once

#define Q_MEMBER_INIT(type, name, init) Q_PROPERTY(type name MEMBER name CONSTANT)\
    type name{init};

#define Q_MEMBER(type, name)\
    private:\
    Q_PROPERTY(type name MEMBER name CONSTANT)\
    public:\
    type name{};
