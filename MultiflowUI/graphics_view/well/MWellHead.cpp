//
// Created by Hatsune Miku on 2023-11-23.
//

#include "MWellHead.hpp"
#include "graphics_view/widget/MTabWidget.hpp"

#include <MultiflowLibrary/logging/logging.hpp>

MWellHead::MWellHead(MEntity* well, MIndependentVariables* iv, QGraphicsPixmapItem* parent)
    : QGraphicsPolygonItem(parent), MWellGeneric(well, iv) {
}

void MWellHead::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option)

    _coordinateHelper->updateBoundaries(widget->width(), widget->height());

    // 顶端长管
    const QPolygonF topRectangle{
        {hc(-.050), vc(.010)},
        {hc(+.050), vc(.010)},
        {hc(+.050), vc(.080)},
        {hc(-.050), vc(.080)}
    };

    // 中间圆盘，长度也就是顶端的1/4，而宽度则是3倍
    // 紧贴顶端长管
    const QPolygonF middleRectangle{
        {hc(-.150), vc(.080)},
        {hc(+.150), vc(.080)},
        {hc(+.150), vc(.105)},
        {hc(-.150), vc(.105)}
    };

    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawPolygon(topRectangle);
    painter->drawPolygon(middleRectangle);

    // 底端长管则要看是否含有Packer和Choke而定
    const bool packer = _containsPacker();
    const bool choke = _containsChoke();

    if (packer && choke) {
        _drawBottomRectangleChokePackered(painter);
    }
    else if (packer) {
        _drawBottomRectanglePackered(painter);
    }
    else if (choke) {
        _drawBottomRectangleChoked(painter);
    }
    else {
        _drawBottomRectanglePlain(painter);
    }
}

void MWellHead::_drawBottomRectanglePlain(QPainter* painter) const {
    // 比中间圆盘还要粗一圈儿，但是一样高
    painter->drawPolygon(QPolygonF{
        {hc(-.175), vc(.105)},
        {hc(+.175), vc(.105)},
        {hc(+.175), vc(.130)},
        {hc(-.175), vc(.130)}
    });
}

void MWellHead::_drawBottomRectangleChoked(QPainter* painter) const {
    // 正常按照plain画的同时，左右各有额外一个小长方形
    painter->drawPolygon(QPolygonF{
        {hc(-.175), vc(.100)},
        {hc(+.175), vc(.100)},
        {hc(+.175), vc(.115)},
        {hc(-.175), vc(.115)}
    });
    painter->drawPolygon(QPolygonF{
        {hc(-.150), vc(.120)},
        {hc(-.120), vc(.120)},
        {hc(-.120), vc(.124)},
        {hc(-.150), vc(.124)}
    });
    painter->drawPolygon(QPolygonF{
        {hc(+.150), vc(.120)},
        {hc(+.120), vc(.120)},
        {hc(+.120), vc(.124)},
        {hc(+.150), vc(.124)}
    });
}

void MWellHead::_drawBottomRectanglePackered(QPainter* painter) const {
    // 好麻烦啊我说不清楚了
    painter->drawPolygon(QPolygonF{
        {hc(-.175), vc(.100)},
        {hc(-.150), vc(.100)},
        {hc(-.150), vc(.120)},
        {hc(-.175), vc(.120)}
    });
    painter->drawPolygon(QPolygonF{
        {hc(+.175), vc(.100)},
        {hc(+.150), vc(.100)},
        {hc(+.150), vc(.120)},
        {hc(+.175), vc(.120)}
    });

    painter->drawLines({
        // 两个叉叉
        QLineF{
            {hc(-.150), vc(.100)},
            {hc(), vc(.120)}
        },
        QLineF{
            {hc(-.150), vc(.120)},
            {hc(), vc(.100)},
        },
        QLineF{
            {hc(), vc(.100)},
            {hc(.150), vc(.120)}
        },
        QLineF{
            {hc(), vc(.120)},
            {hc(.150), vc(.100)},
        },

        // 两个分割线
        QLineF{
            {hc(-.150), vc(.120)},
            {hc(.150), vc(.120)}
        },
        QLineF{
            {hc(0), vc(.100)},
            {hc(0), vc(.120)}
        },
    });
}

void MWellHead::_drawBottomRectangleChokePackered(QPainter* painter) const {
    _drawBottomRectangleChoked(painter);
    _clearArea(painter, {
                   {hc(-.150), vc(.100)},
                   {hc(+.150), vc(.100)},
                   {hc(+.150), vc(.120)},
                   {hc(-.150), vc(.120)},
               });
    _drawBottomRectanglePackered(painter);
}

void MWellHead::_clearArea(QPainter* painter, const QPolygonF& area) {
    const auto brushBackup = painter->brush();
    const auto penBackup = painter->pen();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::lightGray);
    painter->drawPolygon(area);
    painter->setPen(penBackup);
    painter->setBrush(brushBackup);
}

QRectF MWellHead::boundingRect() const {
    return {hc(-.175), vc(.010), hc(+.175), vc(.165)};
}

QPainterPath MWellHead::shape() const {
    QPainterPath path{};
    path.addRect(boundingRect());
    return path;
}

bool MWellHead::_containsPacker() const {
    const auto& items = _iv->get("downhole-equipment");
    return std::ranges::any_of(items, [](const QMap<QString, QVariant>& item) {
        return item["equipment"].toString() == "Packer";
    });
}

bool MWellHead::_containsChoke() const {
    const auto& items = _iv->get("downhole-equipment");
    return std::ranges::any_of(items, [](const QMap<QString, QVariant>& item) {
        return item["equipment"].toString() == "Choke";
    });
}
