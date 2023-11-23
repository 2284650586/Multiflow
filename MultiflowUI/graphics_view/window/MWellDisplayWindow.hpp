//
// Created by Hatsune Miku on 2023-11-22.
//

#pragma once

#include "entity/MEntity.hpp"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

namespace Ui {
class MWellDisplayWindow;
}

QT_END_NAMESPACE

class MWellDisplayWindow final : public QWidget {
    Q_OBJECT

public:
    explicit MWellDisplayWindow(MEntity* well, QWidget* parent = nullptr);

    ~MWellDisplayWindow() override;

private:
    void createGraphicsView();

    Ui::MWellDisplayWindow* ui;
    MEntity* _well{};

    QGraphicsScene* _scene{};
    QGraphicsView* _view{};
    QVBoxLayout* _layout{};
};
