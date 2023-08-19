#include "mjunction.h"
#include <QUuid>

MJunction::MJunction()
{
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

void MJunction::addSource(MSource *source)
{
    sourceList.append(source);
}

void MJunction::addsink(MSink *sink)
{
    sinkList.append(sink);
}

void MJunction::addWell(MWell *well)
{
    wellList.append(well);
}

QString MJunction::getId() const
{
    return id;
}

QList<MSource *> MJunction::getSourceList() const
{
    return sourceList;
}

QList<MSink *> MJunction::getSinkList() const
{
    return sinkList;
}

QList<MWell *> MJunction::getWellList() const
{
    return wellList;
}
