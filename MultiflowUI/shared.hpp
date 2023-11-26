#pragma once

#include "entity/MIndependentVariables.hpp"

#include <QApplication>
#include <QMainWindow>
#include <QQmlApplicationEngine>

#include <memory>

enum MItemKind {
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


#define MAKE_EXCEPTION(name) \
  class name final : public std::exception {\
   std::string _what; \
  public: \
   explicit name(std::string what) : _what{std::move(what)} {} \
   const char* what() const noexcept override { return _what.c_str(); } \
  }
