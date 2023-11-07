//
// Created by miku on 11/6/2023.
//

#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>

namespace qml {

class WindowMain: public QObject {
Q_OBJECT

public:
    explicit WindowMain(QObject *parent = nullptr);
    ~WindowMain() override = default;

public slots:
    void onFormulaViewerButtonClicked();
};

}
