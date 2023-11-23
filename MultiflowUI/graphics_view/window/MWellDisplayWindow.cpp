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

void MWellDisplayWindow::createGraphicsView() {
    _scene = new QGraphicsScene{this};
    _view = new QGraphicsView{this};
    _layout = new QVBoxLayout{this};

    _scene->setSceneRect(rect());
    _scene->setBackgroundBrush(QPixmap{":/resources/image/background3.png"});

    _view->setGeometry(0, 0, width(), height());
    _view->setScene(_scene);
    _view->setRenderHint(QPainter::Antialiasing);
    _view->setDragMode(QGraphicsView::NoDrag);
    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Display the view
    _layout->addWidget(_view);
    _layout->setContentsMargins(0, 0, 0, 0);

    setLayout(_layout);
}
