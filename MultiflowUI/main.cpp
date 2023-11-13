#include "mainwindow.hpp"

#include "shared.hpp"
#include "constants.hpp"
#include "qml/main.hpp"

#include "third_party/argparse/argparse.hpp"

#include <MultiflowLibrary/core/core.hpp>
#include <MultiflowLibrary/logging/logging.hpp>
#include <MultiflowLibrary/parser/formula_parser.hpp>

#include <QApplication>
#include <memory>

argparse::ArgumentParser prepareParser();
void parserAndLoadFormulae();
void startupUI(int argc, char* argv[]);
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

    propertyEnableVerbose = parser.get<bool>("--verbose");

    parserAndLoadFormulae();
    startupUI(argc, argv);

    if (propertyEnableVerbose) {
        trace("Verbose ml enabled.");
        printVersions();
    }

    info("Multiflow UI launched and entered event loop.");
    return a.exec(); // NOLINT(readability-static-accessed-through-instance);
}

void parserAndLoadFormulae() {
    ml::FormulaParser parser{};
    auto formulae = parser.loadDistribution("D:\\dist.yaml");
    info("Loaded {} formula(e).", formulae.size());
    std::ranges::copy(formulae, std::back_inserter(gFormulae));
}

void startupUI(int argc, char* argv[]) {
    qml::start(argc, argv);
}

void printVersions() {
    std::cout << "Multiflow version " << Version << std::endl;
}

argparse::ArgumentParser prepareParser() {
    auto parser = argparse::ArgumentParser{"Multiflow UI"};
    parser.add_argument("-v", "--version")
        .help("show version and exit")
        .default_value(false)
        .implicit_value(true);

    parser.add_argument("--verbose")
        .help("enable verbose ml")
        .default_value(false)
        .implicit_value(true);
    return parser;
}
