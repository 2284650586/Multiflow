#ifndef TGRAPHICSSCENE_H
#define TGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include "common.h"

class MulItem;
class TArrow;

class QGraphicsLineItem;
class QColor;

class TGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode { InsertItem, InsertLine, MoveItem, setPointer };

    TGraphicsScene(QObject *parent = nullptr);
    ~TGraphicsScene();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
    void setMode(Mode type);
    void setItemType(Multiflow_TYPE type);


signals:
    void mulItemInserted(MulItem*);

    void linePointerInserted();
    void setPointerCursor();

private:
    bool isItemChange(int type) const;
    static bool judgeConnect(MulItem *startItem, MulItem *endItem);

    QString getName();
    Multiflow_TYPE m_itemType;
    Mode m_mode;
    QGraphicsLineItem *line;
    QColor myLineColor = Qt::black;
};

#endif // TGRAPHICSSCENE_H
