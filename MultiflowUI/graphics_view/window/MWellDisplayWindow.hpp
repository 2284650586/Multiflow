//
// Created by Hatsune Miku on 2023-11-22.
//

#pragma once

#include "entity/MEntity.hpp"
#include "graphics_view/well/MWellHead.hpp"

#include <QWidget>
#include <QGraphicsView>
#include <QQuickWindow>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

namespace Ui {
class MWellDisplayWindow;
}

QT_END_NAMESPACE

class MWellDisplayWindow final : public QWidget {
    Q_OBJECT

public:
    explicit MWellDisplayWindow(MEntity* well, MIndependentVariables* iv, QWidget* parent = nullptr);

    ~MWellDisplayWindow() override;

    void showAndClipTo(const QQuickWindow* qmlWindow);

    void notifyDataChanged() const;

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void createGraphicsView();

    Ui::MWellDisplayWindow* ui;
    MEntity* _well{};
    MIndependentVariables* _iv{};

    QGraphicsScene* _scene{};
    QGraphicsView* _view{};
    QVBoxLayout* _layout{};
    MWellHead* _wellHead;
};
