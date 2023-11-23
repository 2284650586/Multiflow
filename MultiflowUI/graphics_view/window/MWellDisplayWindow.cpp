//
// Created by Hatsune Miku on 2023-11-22.
//

#include "MWellDisplayWindow.hpp"
#include "ui_MWellDisplayWindow.h"


MWellDisplayWindow::MWellDisplayWindow(MEntity* well, QWidget* parent)
    : _well(well), QWidget(parent), ui(new Ui::MWellDisplayWindow{}) {
    ui->setupUi(this);
}

MWellDisplayWindow::~MWellDisplayWindow() {
    delete ui;
}
