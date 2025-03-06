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

void nts::ShellLoop::display(Circuit &circuit)
{
    circuit.display();
}

void nts::ShellLoop::simulate(Circuit &circuit)
{
    circuit.simulate(circuit.getTick() + 1);
}

void nts::ShellLoop::loop(Circuit &circuit)
{
    while (_running) {
        circuit.simulate(circuit.getTick() + 1);
        circuit.display();
    }
}

bool nts::ShellLoop::setComponentValue(const std::string &input, Circuit &circuit)
{
    std::regex valuePattern("([a-zA-Z0-9_]+)=([01U])");
    std::smatch matches;

    if (std::regex_match(input, matches, valuePattern)) {
        std::string componentName = matches[1];
        std::string valueStr = matches[2];

        try {
            auto &component = circuit.getComponent(componentName);
            auto inputComp = dynamic_cast<nts::InputComponent*>(component.get());
            if (!inputComp) {
                std::cerr << "Error: " << componentName << " is not an input component" << std::endl;
                return false;
            }
            nts::Tristate state;
            if (valueStr == "1")
                state = nts::TRUE;
            else if (valueStr == "0")
                state = nts::FALSE;
            else
                state = nts::UNDEFINED;
            circuit.setInputState(*inputComp, state);
            return true;
        } catch (const std::out_of_range &e) {
            std::cerr << "Error: component " << componentName << " not found" << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return false;
}

void nts::ShellLoop::run()
{
    std::string input;

    while (_running) {
        std::cout << "> ";
        if (!std::getline(std::cin, input)) {
            std::cout << std::endl;
            break;
        }
        if (input.empty())
            continue;
        if (_commands.find(input) != _commands.end())
            (this->*_commands[input])(_circuit);
        else if (input == "exit")
            exit(_circuit);
        else if (!setComponentValue(input, _circuit)) {
            std::cerr << "Invalid command: " << input << std::endl;
        }
    }
}