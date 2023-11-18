#pragma once

#include "shared.hpp"
#include "MArrow.hpp"
#include "MAbstractItem.hpp"

#include <QGraphicsScene>
#include <QObject>
#include <QColor>
#include <QGraphicsLineItem>
#include <QSharedPointer>

#include <memory>

class MGraphicsScene final : public QGraphicsScene {
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, MoveItem, SetPointer };

    explicit MGraphicsScene(QObject* parent = nullptr);

    ~MGraphicsScene() override = default;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

public slots:
    void setMode(Mode mode);

    void setItemType(MultiflowKind kind);

signals:
    // Smart pointers have to downgrade to fit the signal.
    void mulItemInserted(MAbstractItem*);

    void linePointerInserted();

    void setPointerCursor();

private:
    [[nodiscard]] bool isItemChange(int type) const;

    static bool judgeConnect(const MAbstractItem* startItem, const MAbstractItem* endItem);

    void _handleInsertItem(const QGraphicsSceneMouseEvent* event);

    void _handleInsertLine(const QGraphicsSceneMouseEvent* event);

    void _handleSetPointer(const QGraphicsSceneMouseEvent* event);

    MultiflowKind _itemKind{};
    Mode _sceneMode{};
    QGraphicsLineItem* _line{};
    MAbstractItem* _startItem{};
    QColor lineColor{Qt::black};
};
