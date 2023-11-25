//
// Created by Hatsune Miku on 2023-11-22.
//

#include "MWellDisplayWindow.hpp"
#include "ui_MWellDisplayWindow.h"

MWellDisplayWindow::MWellDisplayWindow(MEntity* well, MIndependentVariables* iv, QWidget* parent)
    : _well(well), _iv(iv), ui(new Ui::MWellDisplayWindow{}) {
    ui->setupUi(this);
    _wellHead = new MWellHead{_well, _iv, nullptr};
}

MWellDisplayWindow::~MWellDisplayWindow() {
    delete ui;
}

void MWellDisplayWindow::showAndClipTo(const QQuickWindow* qmlWindow) {
    show();
    resize(300, 600);
    createGraphicsView();

    const auto clip = [this, qmlWindow] {
        if (!isVisible()) {
            return;
        }
        // Clip this to the left of the main window
        move(qmlWindow->x() - width(), qmlWindow->y());
    };
    connect(qmlWindow, &QQuickWindow::xChanged, clip);
    connect(qmlWindow, &QQuickWindow::yChanged, clip);
    connect(qmlWindow, &QQuickWindow::destroyed, this, &MWellDisplayWindow::close);
}

void MWellDisplayWindow::resizeEvent(QResizeEvent* event) {
    if (_scene && _view) {
        _scene->setSceneRect(rect());
        _view->setGeometry(0, 0, width(), height());
    }
}

void MWellDisplayWindow::createGraphicsView() {
    _scene = new QGraphicsScene{};
    _view = new QGraphicsView{this};
    _layout = new QVBoxLayout{this};

    _scene->setSceneRect(rect());
    _scene->addItem(_wellHead);
    _scene->setBackgroundBrush(QBrush{Qt::lightGray}); // TODO: 暗黑模式，暗黑模式啊

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

void MWellDisplayWindow::notifyDataChanged() const {
    _scene->update();
}
