#pragma once

#include <QList>

#include "MSource.hpp"
#include "MSink.hpp"
#include "MWell.hpp"

class MJunction {
    QString id;
    QList<MSource> sources;
    QList<MSink> sinks;
    QList<MWell> wells;
};
