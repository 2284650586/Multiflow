#include "widget/MainWindow.hpp"

#include "shared.hpp"
#include "constants.hpp"
#include "qml/main.hpp"

#include "third_party/argparse/argparse.hpp"

#include <MultiflowLibrary/core/core.hpp>
#include <MultiflowLibrary/logging/logging.hpp>

#include <QApplication>
#include <memory>

argparse::ArgumentParser prepareParser();
void startupUI(int argc, const char* argv[]);
void printVersions();


static constexpr int ErrorSuccess = 0;
static constexpr int ErrorInvalidArgument = 1;


int main(int argc, char *argv[]) {
    ml::initialize();
    log_init(MultiflowUI, level::debug);

    gpApplication = std::make_unique<QApplication>(argc, argv);

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
    startupUI(argc, const_cast<const char**>(argv));

    if (propertyEnableVerbose) {
        log_init(MultiflowUI, level::trace);
        log_trace("Verbose ml enabled.");
        printVersions();
    }

    log_info("Multiflow UI launched and entered event loop.");
    const int result = gpApplication->exec(); // NOLINT(readability-static-accessed-through-instance);

    return result;
}

void startupUI(const int argc, const char* argv[]) {
    log_info("Creating main window.");
    gpWindowMain = std::make_unique<MainWindow>(nullptr, argc, argv);
    gpWindowMain->show();
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
