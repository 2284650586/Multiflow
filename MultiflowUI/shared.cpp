#include "shared.hpp"

bool propertyEnableVerbose = false;

std::unique_ptr<QApplication> gpApplication{};
QQmlApplicationEngine* gpQmlApplicationEngine{};
std::unique_ptr<QMainWindow> gpWindowMain{};
std::unique_ptr<QObject> gpQmlVMFormulaViewer{};
