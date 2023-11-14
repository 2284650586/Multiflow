#include "tgraphicsview.h"
#include <QKeyEvent>
#include <QDebug>

TGraphicsView::TGraphicsView(QWidget* parent) : QGraphicsView(parent) {
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
}

QString TGraphicsView::getScale() const {
    return m_scale;
}

void TGraphicsView::setScale(QString newScale) {
    m_scale = newScale;
}

TGraphicsScene* TGraphicsView::scene() const {
    return dynamic_cast<TGraphicsScene*>(
        QGraphicsView::scene());
}

void TGraphicsView::keyPressEvent(QKeyEvent* event) {
    if ((event->modifiers() & Qt::KeyboardModifier::ControlModifier) != 0) {
        setDragMode(DragMode::ScrollHandDrag);
    }
    QGraphicsView::keyPressEvent(event);
}

void TGraphicsView::keyReleaseEvent(QKeyEvent* event) {
    if ((event->modifiers() & Qt::KeyboardModifier::ControlModifier) == 0) {
        setDragMode(DragMode::RubberBandDrag);
    }
    QGraphicsView::keyReleaseEvent(event);
}
