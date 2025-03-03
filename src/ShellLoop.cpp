/*
** EPITECH PROJECT, 2025
** a
** File description:
** a
*/

#include "ShellLoop.hpp"

nts::ShellLoop::ShellLoop(Circuit &circuit) : _circuit(circuit)
{
    _commands.emplace("exit", &ShellLoop::exit);
    _commands.emplace("simulate", &ShellLoop::simulate);
    _commands.emplace("dump", &ShellLoop::dump);
    _commands.emplace("display", &ShellLoop::display);
    _commands.emplace("loop", &ShellLoop::loop);
    _running = true;
}

nts::ShellLoop::~ShellLoop()
{
}

void nts::ShellLoop::exit(Circuit &circuit)
{
    (void)circuit;
    _running = false;
}

void nts::ShellLoop::dump(Circuit &circuit)
{
    (void)circuit;
    std::cout << "Dumping circuit" << std::endl;
    // circuit.dump();
}

void nts::ShellLoop::display(Circuit &circuit)
{
    (void)circuit;
    std::cout << "Displaying circuit" << std::endl;
    // circuit.display();
}

void nts::ShellLoop::simulate(Circuit &circuit)
{
    (void)circuit;
    std::cout << "Simulating circuit" << std::endl;
    // circuit.simulate();
}

void nts::ShellLoop::loop(Circuit &circuit)
{
    (void)circuit;
    while (_running) {
        // circuit.simulate();
        // circuit.display();
    }
}

void nts::ShellLoop::run()
{
    std::string input;

    while (_running) {
        std::cout << "> ";
        std::cin >> input;
        if (_commands.find(input) != _commands.end())
            (this->*_commands[input])(_circuit);
        else if (input == "exit")
            exit(_circuit);
        else
            std::cout << "Command not found" << std::endl;
    }
}