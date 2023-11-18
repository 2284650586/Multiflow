#pragma once

#include "TView/tgraphicsview.h"

#include <QTabWidget>

class MTabWidget final : public QTabWidget {
    Q_OBJECT

public:
    explicit MTabWidget(QWidget* parent = nullptr);

    [[nodiscard]] TGraphicsView* widgetAt(int index) const;

    [[nodiscard]] TGraphicsView* currentTGraphicsView() const;
};
