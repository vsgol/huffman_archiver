#include "CLI.hpp"

//-------------------------------------------------------------------------Help
void typeHelp() {
    std::cout << "Huffman code-based archiver \n";
    std::cout << "DESCRIPTION\n";
    std::cout << "    -c     archiving\n";
    std::cout << '\n';
    std::cout << "    -u     unpack archive\n";
    std::cout << '\n';
    std::cout << "    -f, --file <path>\n";
    std::cout << "           input file name\n";
    std::cout << '\n';
    std::cout << "    -o, --output <path>\n";
    std::cout << "           output file name\n";
    std::cout << '\n';
    std::cout << "    -h, --help\n";
    std::cout << "           help\n";
    std::cout.flush();
    exit(0);
}
//-----------------------------------------------------------------------------

void WorkMode::check() {
    if (type_ == ActionType::none)
        throw std::invalid_argument("You should choose one of the types of work\n");
    if (in_name_.empty())
        throw std::invalid_argument("You should select the input file\n");
    if (out_name_.empty())
        throw std::invalid_argument("You should select the output file\n");
}

void WorkMode::setAction(ActionType action) {
    if (type_ == ActionType::none) {
        type_ = action;
        return;
    }
    if (type_ == action)
        throw std::invalid_argument("You can't use this flag twice\n");
    throw std::invalid_argument("You can't use -u and -c flags together\n");
}

WorkMode parseArgs(int argc, const char** argv) {
    WorkMode args;
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);

        if (arg == "-h" || arg == "--help") {
            typeHelp();
        }
        if (arg == "-c") {
            args.setAction(ActionType::compress);
            continue;
        }
        if (arg == "-u") {
            args.setAction(ActionType::extract);
            continue;
        }
        if (arg == "-f" || arg == "--file") {
            if (i == argc - 1)
                throw std::invalid_argument("Input file name was expected\n");
            args.in_name_ = std::string(argv[++i]);
            if (args.out_name_ == args.in_name_)
                throw std::invalid_argument("Input and output filenames should be different\n");
            continue;
        }
        if (arg == "-o" || arg == "--output") {
            if (i == argc - 1)
                throw std::invalid_argument("Output file name was expected\n");
            args.out_name_ = std::string(argv[++i]);
            if (args.out_name_ == args.in_name_)
                throw std::invalid_argument("Input and output filenames should be different\n");
            continue;
        }
        throw std::invalid_argument("Unknown argument, type '-h' or '--help' for information\n");
    }
    args.check();
    return args;
}