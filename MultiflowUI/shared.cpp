#include "shared.hpp"

bool propertyLegacyUI = false;
bool propertyEnableVerbose = false;

std::unique_ptr<QApplication> gpApplication = nullptr;
std::unique_ptr<QQmlApplicationEngine> gpQmlApplicationEngine = nullptr;
std::unique_ptr<QMainWindow> gpMainWindow = nullptr;
QVector<ml::Formula> gFormulae{};
std::unique_ptr<QObject> gpWindowMain = nullptr;
std::unique_ptr<QObject> gpWindowFormulaViewer = nullptr;
