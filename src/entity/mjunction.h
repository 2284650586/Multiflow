#ifndef MJUNCTION_H
#define MJUNCTION_H

#include <QList>


class MSource;
class MSink;
class MWell;

class MJunction
{
public:
    MJunction();

    void addSource(MSource *source);
    void addsink(MSink *sink);
    void addWell(MWell *well);

    QString getId() const;
    QList<MSource *> getSourceList() const;
    QList<MSink *> getSinkList() const;
    QList<MWell *> getWellList() const;

private:
    QString id;
    QList<MSource*> sourceList;
    QList<MSink*> sinkList;
    QList<MWell*> wellList;
};

#endif // MJUNCTION_H
