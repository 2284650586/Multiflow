#pragma once

#include "shared.hpp"
#include "MArrow.hpp"
#include "MAbstractItem.hpp"

#include <QGraphicsScene>
#include <QObject>
#include <QColor>
#include <QGraphicsLineItem>

#include <memory>

class MGraphicsScene final : public QGraphicsScene {
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, MoveItem, setPointer };

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

    static bool judgeConnect(
        const std::shared_ptr<MAbstractItem>& startItem,
        const std::shared_ptr<MAbstractItem>& endItem
    );

    void _handleInsertItem(const QGraphicsSceneMouseEvent* event);

    void _handleInsertLine(const QGraphicsSceneMouseEvent* event);

    void _handleSetPointer(const QGraphicsSceneMouseEvent* event);

    [[nodiscard]]QString name() const;

    MultiflowKind _itemKind{};
    Mode _sceneMode{};
    std::shared_ptr<QGraphicsLineItem> _line{};
    QColor lineColor{Qt::black};
};
