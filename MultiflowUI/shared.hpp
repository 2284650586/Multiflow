#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QQmlApplicationEngine>

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

extern bool propertyEnableVerbose;

/**
 * @brief The global QML application engine.
 */
extern QQmlApplicationEngine* gpQmlApplicationEngine;

/**
 * @brief The global QML application object.
 */
extern QApplication* gpApplication;

/**
 * @brief The global Widget-based main window.
 */
extern QMainWindow* gpWindowMain;

/**
 * @brief The global QML-based formula viewer window.
 */
extern QObject* gpQmlVMFormulaViewer;
