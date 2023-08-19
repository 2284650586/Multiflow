#ifndef TMULTIFLOWITEM_H
#define TMULTIFLOWITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>

class TMultiflowItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    TMultiflowItem(QString name = "MultflowItem", QGraphicsItem *parent = nullptr);

    void setType(int type);

private:
    int m_type;
    QString name;
};

#endif // TMULTIFLOWITEM_H
