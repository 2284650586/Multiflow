#include "mwellwidget.h"
#include "ui_mwellwidget.h"

MWellWidget::MWellWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MWellWidget)
{
    ui->setupUi(this);
}

MWellWidget::~MWellWidget()
{
    delete ui;
}
