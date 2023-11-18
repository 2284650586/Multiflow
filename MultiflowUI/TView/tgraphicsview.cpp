#include "tgraphicsview.h"

#include <QKeyEvent>

TGraphicsView::TGraphicsView(QWidget* parent) : QGraphicsView(parent) {
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setDragMode(RubberBandDrag);
}

QString TGraphicsView::getScale() const {
    return _scale;
}

void TGraphicsView::setScale(const QString& newScale) {
    _scale = newScale;
}

MGraphicsScene* TGraphicsView::scene() const {
    return dynamic_cast<MGraphicsScene*>(
        QGraphicsView::scene());
}

void TGraphicsView::keyPressEvent(QKeyEvent* event) {
    if ((event->modifiers() & Qt::KeyboardModifier::ControlModifier) != 0) {
        setDragMode(ScrollHandDrag);
    }
    QGraphicsView::keyPressEvent(event);
}

void TGraphicsView::keyReleaseEvent(QKeyEvent* event) {
    if ((event->modifiers() & Qt::KeyboardModifier::ControlModifier) == 0) {
        setDragMode(RubberBandDrag);
    }
    QGraphicsView::keyReleaseEvent(event);
}
