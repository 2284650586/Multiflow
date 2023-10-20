#include "mainwindow.h"

#include "third_party/argparse/argparse.hpp"

#include "shared.hpp"
#include "constants.hpp"

#include <QQuickView>
#include <QApplication>
#include <MultiflowLibrary/core/core.h>
#include <MultiflowLibrary/logging/logging.h>
#include <MultiflowLibrary/constants.hpp>


argparse::ArgumentParser    prepareParser();
void                        startupUILegacy();
void                        startupUI();

static constexpr int        ErrorSuccess = 0;
static constexpr int        ErrorInvalidArgument = 1;


int main(int argc, char *argv[])
{
    ml::initialize();
    QApplication a(argc, argv);

    auto parser = prepareParser();
    try {
        parser.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        return ErrorInvalidArgument;
    }

    if (parser.get<bool>("--version")) {
        std::cout << "Multiflow version " << ml::Version << std::endl;
        std::cout << "Multiflow UI version " << Version << std::endl;
        return ErrorSuccess;
    }

    propertyLegacyUI = parser.get<bool>("--legacy");
    propertyEnableVerbose = parser.get<bool>("--verbose");

    if (propertyLegacyUI) {
        startupUILegacy();
    }
    else {
        startupUI();
    }

    LOG_INFO << "Multiflow UI launched and entered event loop.";
    return a.exec(); // NOLINT(readability-static-accessed-through-instance)
}

void startupUILegacy()
{
    MainWindow w;
    w.show();
}
void startupUI()
{
    QQuickView view;
    view.setSource(QUrl{"qrc:/qml/main.qml"});
    view.show();
}

argparse::ArgumentParser prepareParser()
{
    auto parser = argparse::ArgumentParser{"Multiflow UI"};
    parser.add_argument("-v", "--version")
            .help("show version and exit")
            .default_value(false)
            .implicit_value(true);

    parser.add_argument("--legacy")
            .help("start legacy UI")
            .default_value(false)
            .implicit_value(true);

    parser.add_argument("--verbose")
            .help("enable verbose logging")
            .default_value(false)
            .implicit_value(true);
    return parser;
}
