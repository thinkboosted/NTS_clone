#ifndef SHELL_LOOP_HPP
#define SHELL_LOOP_HPP

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <regex>
#include "Circuit.hpp"

namespace nts {

class ShellLoop {
    public:
        ShellLoop(Circuit &circuit);
        ~ShellLoop();
        void run();

    private:
        Circuit &_circuit;
        std::map<std::string, void (ShellLoop::*)(Circuit &)> _commands;
        bool setComponentValue(const std::string &input, Circuit &circuit);
        void exit(Circuit &circuit);
        void display(Circuit &circuit);
        void simulate(Circuit &circuit);
        void loop(Circuit &circuit);
        bool _running;
};
}

#endif // SHELL_LOOP_HPP
