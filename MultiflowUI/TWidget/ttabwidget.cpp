#include "ttabwidget.h"

TTabWidget::TTabWidget(QWidget* parent) : QTabWidget(parent) {
}

TGraphicsView* TTabWidget::widgetAt(const int index) const {
    return dynamic_cast<TGraphicsView*>(widget(index));
}

TGraphicsView* TTabWidget::currentTGraphicsView() const {
    return widgetAt(currentIndex());
}
