//
// Created by vsg on 16.04.2020.
//

#ifndef HW_03_CLI_HPP
#define HW_03_CLI_HPP

#include <iostream>

void typeHelp();
enum class ActionType { none, compress, extract };
struct WorkMode {
    void check();
    void setAction(ActionType action);

    ActionType type_ = ActionType::none;
    std::string in_name_, out_name_;
};

WorkMode parseArgs(int argc, const char** argv);

#endif  //HW_03_CLI_HPP
