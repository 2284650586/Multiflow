#include "mainwindow.hpp"
#include "shared.hpp"
#include "constants.hpp"
#include "qml/main.hpp"

#include "third_party/argparse/argparse.hpp"
#include <spdlog/spdlog.h>

#include <memory>
#include <utility>
#include <functional>
#include <algorithm>
#include <ranges>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

import core;
import formula;
import formula_parser;

argparse::ArgumentParser prepareParser();
void initialize();
void startupUILegacy(int argc, char* argv[]);
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

    propertyLegacyUI = parser.get<bool>("--legacy");
    propertyEnableVerbose = parser.get<bool>("--verbose");

    initialize();
    if (propertyLegacyUI) {
        startupUILegacy(argc, argv);
    } else {
        startupUI(argc, argv);
    }

    if (propertyEnableVerbose) {
        spdlog::trace("Verbose ml enabled.");
        printVersions();
    }

    spdlog::info("Multiflow UI launched and entered event loop.");

    int result = a.exec(); // NOLINT(readability-static-accessed-through-instance)

    return result;
}

void initialize() {
    ml::FormulaParser parser{};
    auto formulae = parser.loadDistribution("D:\\dist.yaml");
    spdlog::info("Loaded {} formula(e).", formulae.size());
    std::copy(formulae.begin(), formulae.end(), std::back_inserter(gFormulae));
}

void startupUILegacy(int argc, char* argv[]) {
    gpMainWindow = std::make_unique<MainWindow>();
    gpMainWindow->show();
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
