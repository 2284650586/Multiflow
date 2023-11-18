#pragma once

#include <QWidget>

namespace Ui {
class MWellWidget;
}

class MWellWidget : public QWidget {
    Q_OBJECT

public:
    explicit MWellWidget(QWidget* parent = nullptr);

    ~MWellWidget();

private:
    Ui::MWellWidget* ui;
};
