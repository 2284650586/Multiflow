#include "MGraphicsView.h"

#include <QKeyEvent>

MGraphicsView::MGraphicsView(QWidget* parent) : QGraphicsView(parent) {
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setDragMode(RubberBandDrag);
}

QString MGraphicsView::getScale() const {
    return _scale;
}

void MGraphicsView::setScale(const QString& newScale) {
    _scale = newScale;
}

MGraphicsScene* MGraphicsView::scene() const {
    return dynamic_cast<MGraphicsScene*>(
        QGraphicsView::scene());
}

void MGraphicsView::keyPressEvent(QKeyEvent* event) {
    if ((event->modifiers() & Qt::KeyboardModifier::ControlModifier) != 0) {
        setDragMode(ScrollHandDrag);
    }
    QGraphicsView::keyPressEvent(event);
}

void MGraphicsView::keyReleaseEvent(QKeyEvent* event) {
    if ((event->modifiers() & Qt::KeyboardModifier::ControlModifier) == 0) {
        setDragMode(RubberBandDrag);
    }
    QGraphicsView::keyReleaseEvent(event);
}
