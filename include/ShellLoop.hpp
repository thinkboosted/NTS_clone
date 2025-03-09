#ifndef SHELL_LOOP_HPP
#define SHELL_LOOP_HPP

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <regex>
#include "Circuit.hpp"
#include <csignal>

namespace nts {

class ShellLoop {
    public:
        ShellLoop(Circuit &circuit);
        ~ShellLoop();
        void run();

        static bool signalReceived;
        static void signalHandler(int signal);
    private:
    protected:
        Circuit &_circuit;
        std::map<std::string, void (ShellLoop::*)(Circuit &)> _commands;
        bool setComponentValue(const std::string &input, Circuit &circuit);
        void exit(Circuit &circuit);
        void display(Circuit &circuit);
        void simulate(Circuit &circuit);
        void loop(Circuit &circuit);
        bool getUserInput(std::string &input);
        bool executeCommand(const std::string &input);
        void handleException(const std::exception &e);
        bool _running;

};
}

#endif // SHELL_LOOP_HPP
