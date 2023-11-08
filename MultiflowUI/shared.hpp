#pragma once

#include "MultiflowLibrary/formula/formula.hpp"

#include <QObject>
#include <QMainWindow>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QVector>

#include <memory>

enum MultiflowKind {
    Well,
    Source,
    Sink,
    Junction,
    Flowline,
    LinePointer,
    Pointer,
    NONETYPE
};

extern bool propertyLegacyUI;
extern bool propertyEnableVerbose;

// Memory managed by Qt.
extern QApplication* gpApplication;

// Memory managed by Qt.
extern QQmlApplicationEngine* gpQmlApplicationEngine;

extern QVector<ml::Formula> gFormulae;

extern std::unique_ptr<QMainWindow> gpMainWindow;

extern std::unique_ptr<QObject> gpWindowMain;
extern std::unique_ptr<QObject> gpWindowFormulaViewer;
