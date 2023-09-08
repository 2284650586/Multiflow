#include "tmultiflowitem.h"

TMultiflowItem::TMultiflowItem(QString name, QGraphicsItem *parent)
    : QObject(nullptr)
    , QGraphicsPixmapItem(parent)
{

}

void TMultiflowItem::setType(int type)
{
    m_type = type;
}
