/*
** EPITECH PROJECT, 2025
** a
** File description:
** a
*/

#include "ShellLoop.hpp"


bool nts::ShellLoop::signalReceived = false;

void nts::ShellLoop::signalHandler(int signal) {
    if (signal == SIGINT) {
        signalReceived = true;
        dup2(0, 0);
    }
}

nts::ShellLoop::ShellLoop(Circuit &circuit) : _circuit(circuit)
{
    struct sigaction sa;

    _commands.emplace("exit", &ShellLoop::exit);
    _commands.emplace("simulate", &ShellLoop::simulate);
    _commands.emplace("display", &ShellLoop::display);
    _commands.emplace("loop", &ShellLoop::loop);
    _running = true;
    sa.sa_handler = signalHandler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);}

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
    while (_running && !signalReceived) {
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

bool nts::ShellLoop::getUserInput(std::string &input)
{
    if (!std::getline(std::cin, input)) {
        if (signalReceived || std::cin.eof()) {
            std::cout << std::endl;
            return false;
        }
        if (std::cin.fail()) {
            std::cin.clear();
            return true;
        }
    }
    return !signalReceived;
}

bool nts::ShellLoop::executeCommand(const std::string &input)
{
    if (input.empty())
        return true;
    if (_commands.find(input) != _commands.end()) {
        (this->*_commands[input])(_circuit);
    } else if (input == "exit") {
        exit(_circuit);
        return false;
    } else if (!setComponentValue(input, _circuit)) {
        std::cerr << "Invalid command: " << input << std::endl;
    }
    return !signalReceived;
}

void nts::ShellLoop::handleException(const std::exception &e)
{
    if (!signalReceived) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void nts::ShellLoop::run()
{
    std::string input;

    _circuit.simulate(0);
    while (_running && !signalReceived) {
        std::cout << "> " << std::flush;
        try {
            if (!getUserInput(input))
                break;
            if (!executeCommand(input))
                break;
        } catch (const std::exception &e) {
            handleException(e);
        }
        if (signalReceived)
            break;
    }
    _running = false;
}