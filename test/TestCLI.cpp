#include <cstring>

#include "CLI.hpp"
#include "doctest.h"

TEST_CASE("Test CLI") {
    const char* argv[7];
    for (auto& i : argv) i = new char[10];  // я не смог придумать, как сделать без new

    strcpy((char*)argv[0], "hw03");
    strcpy((char*)argv[1], "-c");
    strcpy((char*)argv[2], "-f");
    strcpy((char*)argv[3], "Input");
    strcpy((char*)argv[4], "-o");
    strcpy((char*)argv[5], "Output");
    WorkMode mode;
    mode = parseArgs(6, argv);
    CHECK(mode.in_name_ == "Input");
    CHECK(mode.out_name_ == "Output");
    CHECK(mode.type_ == ActionType::compress);

    strcpy((char*)argv[1], "--file");
    strcpy((char*)argv[2], "Input");
    strcpy((char*)argv[3], "-u");
    strcpy((char*)argv[4], "--output");
    strcpy((char*)argv[5], "Output");

    //str_c выдает всегда один укзатель
    //argv[1] = std::string("-f").c_str();
    //argv[2] = std::string("InputFile").c_str();
    //argv[3] = std::string("-c").c_str();
    //argv[4] = std::string("-o").c_str();
    //argv[5] = std::string("OutputFile").c_str();

    mode = parseArgs(6, argv);
    CHECK(mode.in_name_ == "Input");
    CHECK(mode.out_name_ == "Output");
    CHECK(mode.type_ == ActionType::extract);

    strcpy((char*)argv[6], "-c");
    try {
        mode = parseArgs(7, argv);
    } catch (const std::invalid_argument& err) {
        CHECK(std::string(err.what()) == "You can't use -u and -c flags together\n");
    }

    strcpy((char*)argv[6], "-u");
    try {
        mode = parseArgs(7, argv);
    } catch (const std::invalid_argument& err) {
        CHECK(std::string(err.what()) == "You can't use this flag twice\n");
    }

    try {
        mode = parseArgs(4, argv);
    } catch (const std::invalid_argument& err) {
        CHECK(std::string(err.what()) == "You should select the output file\n");
    }

    for (auto& i : argv)
        delete [] i;
}
