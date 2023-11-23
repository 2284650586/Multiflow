#pragma once

#include "shared.hpp"
#include "MArrow.hpp"
#include "MAbstractItem.hpp"

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

    void setItemType(MItemKind kind);

signals:
    // Smart pointers have to downgrade to fit the signal.
    void mulItemInserted(MAbstractItem*);

    void linePointerInserted();

    void setPointerCursor();

private:
    [[nodiscard]] bool isItemChange(int type) const;

    static bool canInterConnect(const MAbstractItem* startItem, const MAbstractItem* endItem);

    void _handleInsertItem(const QGraphicsSceneMouseEvent* event);

    void _handleInsertLine(const QGraphicsSceneMouseEvent* event);

    void _handleSetPointer(const QGraphicsSceneMouseEvent* event);

    [[nodiscard]] static MAbstractItem* _createItem(MItemKind kind);

    MItemKind _itemKind{};
    Mode _sceneMode{};
    QGraphicsLineItem* _line{};
    MAbstractItem* _startItem{};
    QColor lineColor{Qt::black};
};

MAKE_EXCEPTION(ItemNotFoundException);
