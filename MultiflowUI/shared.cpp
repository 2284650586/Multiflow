#include "shared.hpp"

bool propertyEnableVerbose = false;

std::unique_ptr<QApplication> gpApplication = nullptr;
QQmlApplicationEngine* gpQmlApplicationEngine = nullptr;
std::unique_ptr<QMainWindow> gpWindowMain = nullptr;
std::unique_ptr<QObject> gpQmlWindowMain = nullptr;
std::unique_ptr<QObject> gpQmlWindowFormulaViewer = nullptr;
