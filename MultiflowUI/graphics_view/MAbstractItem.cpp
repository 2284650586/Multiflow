//
// Created by miku on 11/17/2023.
//

#include "MAbstractItem.hpp"
#include "qml/main.hpp"

#include <logging/logging.hpp>

#include <QQmlContext>

#include <utility>

MAbstractItem::MAbstractItem(
    const MItemKind kind,
    QString itemName,
    const QString& resourceFileName,
    QString route,
    MEntity* entity,
    CalculationUnit* calculationUnit,
    QGraphicsPixmapItem* parent)
    : QGraphicsPixmapItem(parent),
      _kind(kind),
      _itemName(std::move(itemName)),
      _qmlRoute(std::move(route)),
      _entity(entity),
      _independentVariables(new MIndependentVariables{}),
      _calculationUnit(calculationUnit),
      _bridge(new MSignalBridge{}) {
    setPixmap(QPixmap{resourceFileName}
        .scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setFlags(
        ItemIsMovable
        | ItemIsSelectable
        | ItemSendsGeometryChanges
        | ItemIsFocusable
    );

    QObject::connect(_bridge, &MSignalBridge::onDataChanged, [this](const QVariant& data) {
        /// Casting directly to MEntity* will produce nullptr,
        /// however, a middle step (QQmlPropertyMap*, aka MEntity's superclass)
        /// can get the valid pointer. 好奇怪啊
        const auto* entityStep1 = data.value<QQmlPropertyMap*>();
        const auto* entityStep2 = dynamic_cast<const MEntity*>(entityStep1);
        // const auto* entity = data.value<MEntity*>(); // nullptr

        if (!entityStep2) {
            log_critical("Failed to cast QVariant to MEntity*");
            return;
        }
        // 其实是同一份啦
        assert(_entity == entityStep2);
        onUserDataSaved();
    });
}

void MAbstractItem::openEditorDialog(const QString& route) const {
    // TODO: Don't use global context
    auto* context = gpQmlApplicationEngine->rootContext();
    context->setContextProperty("bridge", _bridge);
    context->setContextProperty("entity", QVariant::fromValue(_entity));
    context->setContextProperty("independentVariables", QVariant::fromValue(_independentVariables));
    context->setContextProperty("calculationUnit", QVariant::fromValue(_calculationUnit));
    qml::navigate(route);
}


void MAbstractItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    event->accept();
    if (event->button() != Qt::LeftButton) {
        return;
    }
    openEditorDialog(_qmlRoute);
}

void MAbstractItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);

    const auto& pixmap = this->pixmap();
    painter->drawPixmap(pixmap.rect(), pixmap);

    painter->setPen(QPen{Qt::black});
    painter->setFont(QFont{"Verdana", 8, QFont::Normal});
    painter->drawText(0, 0, _itemName);

    if (isSelected()) {
        QPen pen(Qt::red);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}

QRectF MAbstractItem::boundingRect() const {
    const QRect& rect = pixmap().rect();
    return {0, 0, static_cast<qreal>(rect.width()), static_cast<qreal>(rect.height())};
}

QPainterPath MAbstractItem::shape() const {
    const QRectF& rect = boundingRect();

    QPainterPath path{};
    path.addRoundedRect(rect, 5, 5);
    return path;
}

const QString& MAbstractItem::itemName() const {
    return _itemName;
}

const QList<MAbstractItem::ArrowType*>& MAbstractItem::arrows() const {
    return _arrows;
}

MItemKind MAbstractItem::itemKind() const {
    return _kind;
}

int MAbstractItem::type() const {
    return Type;
}

void MAbstractItem::addArrow(ArrowType* arrow) {
    _arrows.append(arrow);
}

void MAbstractItem::removeArrow(const ArrowType* arrow) {
    _arrows.removeAll(arrow);
}

void MAbstractItem::removeAllArrows() {
    _arrows.clear();
}

void MAbstractItem::setItemName(const QString& name) {
    _itemName = name;
}

size_t MAbstractItem::countStartArrows() const {
    return std::ranges::count_if(_arrows, [this](const ArrowType* arrow) {
        return arrow->getStartItem() == this;
    });
}

size_t MAbstractItem::countEndArrows() const {
    return std::ranges::count_if(_arrows, [this](const ArrowType* arrow) {
        return arrow->getEndItem() == this;
    });
}

QVariant MAbstractItem::itemChange(const GraphicsItemChange change, const QVariant& value) {
    if (change == ItemPositionChange) {
        std::ranges::for_each(_arrows, [](const auto& arrow) {
            arrow->updatePosition();
        });
    }
    return QGraphicsPixmapItem::itemChange(change, value);
}
