#include "mainwindow.hpp"

#include "third_party/argparse/argparse.hpp"

#include "shared.hpp"
#include "constants.hpp"
#include "qml/main.hpp"

#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>

#include "MultiflowLibrary/core/core.hpp"
#include "MultiflowLibrary/logging/logging.hpp"
#include <MultiflowLibrary/constants.hpp>

#include <MultiflowLibrary/parser/formula_parser.hpp>

argparse::ArgumentParser prepareParser();
void initialize();
void startupUILegacy();
void startupUI();
void printVersions();

static constexpr int ErrorSuccess = 0;
static constexpr int ErrorInvalidArgument = 1;


int main(int argc, char *argv[]) {
    ml::initialize();
    QApplication a(argc, argv);
    gpApplication = &a;

    auto parser = prepareParser();
    try {
        parser.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        return ErrorInvalidArgument;
    }

    if (parser.get<bool>("--version")) {
        printVersions();
        return ErrorSuccess;
    }

    propertyLegacyUI = parser.get<bool>("--legacy");
    propertyEnableVerbose = parser.get<bool>("--verbose");

    initialize();
    if (propertyLegacyUI) {
        startupUILegacy();
    } else {
        startupUI();
    }

    if (propertyEnableVerbose) {
        LOG_INFO << "Verbose ml enabled.\n";
        printVersions();
    }

    LOG_INFO << "Multiflow UI launched and entered event loop.\n";
    int result = a.exec(); // NOLINT(readability-static-accessed-through-instance)

    delete gpQmlApplicationEngine;
    delete gpMainWindow;

    return result;
}

void initialize() {
    ml::FormulaParser parser{};
    auto formulae = parser.parseDistribution("D:\\dist.yaml");
    std::copy(formulae.begin(), formulae.end(), std::back_inserter(gFormulae));
}

void startupUILegacy() {
    gpMainWindow = new MainWindow{};
    gpMainWindow->show();
}

void startupUI() {
    qml::registerQmlComponents();

    // Window shows as the engine create and load.
    gpQmlApplicationEngine = new QQmlApplicationEngine{
        QUrl("qrc:/qml/main.qml"), gpApplication};

    auto* context = gpQmlApplicationEngine->rootContext();
    context->setContextProperty("gFormulae", QVariant::fromValue(gFormulae));
}

void printVersions() {
    std::cout << "MultiflowLibrary version " << ml::Version << std::endl;
    std::cout << "Multiflow UI version " << Version << std::endl;
}

argparse::ArgumentParser prepareParser() {
    auto parser = argparse::ArgumentParser{"Multiflow UI"};
    parser.add_argument("-v", "--version")
        .help("show version and exit")
        .default_value(false)
        .implicit_value(true);

    parser.add_argument("-l", "--legacy")
        .help("start legacy UI")
        .default_value(false)
        .implicit_value(true);

    parser.add_argument("--verbose")
        .help("enable verbose ml")
        .default_value(false)
        .implicit_value(true);
    return parser;
}
