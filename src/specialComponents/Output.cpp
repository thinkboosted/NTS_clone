/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Output
*/

#include "Output.hpp"

nts::OutputComponent::OutputComponent(const std::string &name) : AComponent(name)
{
    this->_pins = new std::unique_ptr<nts::IComponent>[1];
    this->_pins[0] = nullptr;
    this->setState(nts::UNDEFINED);
}

void nts::OutputComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin != 1)
        throw std::invalid_argument("Invalid pin for output component");
    _pins[0] = std::unique_ptr<nts::IComponent>(&other);
    (void)otherPin;
}

void nts::OutputComponent::simulate()
{
    if (_pins[0])
        _pins[0]->simulate();
}

void nts::OutputComponent::compute()
{
    if (_pins[0])
        setState(_pins[0]->getState());
    else
        setState(nts::UNDEFINED);

    std::cout << getName() << "=" << (getState() == nts::TRUE ? "1" :
                                    getState() == nts::FALSE ? "0" : "U") << std::endl;
}