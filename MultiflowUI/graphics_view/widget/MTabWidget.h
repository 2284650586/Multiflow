#pragma once

#include "graphics_view/MGraphicsView.h"

#include <QTabWidget>

class MTabWidget final : public QTabWidget {
    Q_OBJECT

public:
    explicit MTabWidget(QWidget* parent = nullptr);

    [[nodiscard]] MGraphicsView* widgetAt(int index) const;

    [[nodiscard]] MGraphicsView* currentTGraphicsView() const;
};
