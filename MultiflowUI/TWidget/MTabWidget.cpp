#include "MTabWidget.h"

MTabWidget::MTabWidget(QWidget* parent) : QTabWidget(parent) {
}

TGraphicsView* MTabWidget::widgetAt(const int index) const {
    return dynamic_cast<TGraphicsView*>(widget(index));
}

TGraphicsView* MTabWidget::currentTGraphicsView() const {
    return widgetAt(currentIndex());
}
