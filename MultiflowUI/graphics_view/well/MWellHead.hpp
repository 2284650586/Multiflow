//
// Created by Hatsune Miku on 2023-11-23.
//

#pragma once

#include "graphics_view/well/MWellGeneric.hpp"

#include <QGraphicsPolygonItem>

class MWellHead final : public MWellGeneric, public QGraphicsPolygonItem {
    [[nodiscard]] bool _containsPacker() const;

    [[nodiscard]] bool _containsChoke() const;

    void _drawBottomRectanglePlain(QPainter* painter) const;

    void _drawBottomRectangleChoked(QPainter* painter) const;

    void _drawBottomRectanglePackered(QPainter* painter) const;

    void _drawBottomRectangleChokePackered(QPainter* painter) const;

    static void _clearArea(QPainter* painter, const QPolygonF& area) ;

public:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    [[nodiscard]] QRectF boundingRect() const override;

    [[nodiscard]] QPainterPath shape() const override;

    explicit MWellHead(MEntity* well, MIndependentVariables* iv, QGraphicsPixmapItem* parent);
};
