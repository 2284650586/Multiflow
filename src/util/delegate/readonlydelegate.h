#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H

#include <QItemDelegate>
#include <QPainter>

class ReadOnlyDelegate : public QItemDelegate
{
public:
    explicit ReadOnlyDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override //final
    {
        Q_UNUSED(parent)
        Q_UNUSED(option)
        Q_UNUSED(index)
        return NULL;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {

        QColor bgColor = Qt::lightGray;
        painter->fillRect(option.rect, bgColor); // 设置特殊单元格的背景色为灰色

        QItemDelegate::paint(painter, option, index);
    }

};

#endif // READONLYDELEGATE_H
