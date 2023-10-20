#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QQmlApplicationEngine>

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

extern bool                     propertyLegacyUI;
extern bool                     propertyEnableVerbose;

extern QApplication*            gpApplication;
extern QQmlApplicationEngine*   gpQmlApplicationEngine;
extern QMainWindow*             gpMainWindow;
