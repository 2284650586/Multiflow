#include "MTabWidget.h"

MTabWidget::MTabWidget(QWidget* parent) : QTabWidget(parent) {
}

MGraphicsView* MTabWidget::widgetAt(const int index) const {
    return dynamic_cast<MGraphicsView*>(widget(index));
}

MGraphicsView* MTabWidget::currentTGraphicsView() const {
    return widgetAt(currentIndex());
}
