#pragma once

#include "TView/tgraphicsview.h"

#include <QTabWidget>

class TTabWidget final : public QTabWidget {
    Q_OBJECT

public:
    explicit TTabWidget(QWidget* parent = nullptr);

    [[nodiscard]] TGraphicsView* widgetAt(int index) const;

    [[nodiscard]] TGraphicsView* currentTGraphicsView() const;
};
