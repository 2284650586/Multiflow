//
// Created by Hatsune Miku on 2023-11-22.
//

#pragma once

#include <QWidget>

#include "entity/MEntity.hpp"


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
    Ui::MWellDisplayWindow* ui;
    MEntity* _well{};
};
