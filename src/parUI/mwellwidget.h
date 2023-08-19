#ifndef MWELLWIDGET_H
#define MWELLWIDGET_H

#include <QWidget>

namespace Ui {
class MWellWidget;
}

class MWellWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MWellWidget(QWidget *parent = nullptr);
    ~MWellWidget();

private:
    Ui::MWellWidget *ui;
};

#endif // MWELLWIDGET_H
