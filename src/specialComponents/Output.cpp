/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Output
*/

#include "../../include/specialComponents/Output.hpp"

nts::OutputComponent::OutputComponent(const std::string &name) : AComponent(name)
{
    this->_pins = new std::unique_ptr<nts::IComponent>[1];
    this->_pins[0] = nullptr;
    this->setState(nts::UNDEFINED);
}

void nts::OutputComponent::simulate(std::size_t tick)
{
    (void)tick;
    if (this->_pins[0] == nullptr)
        throw std::invalid_argument("Pin not linked");
    this->setState(this->_pins[0]->compute(tick));
}

nts::Tristate nts::OutputComponent::compute(std::size_t tick)
{
    this->simulate(tick);
    return this->getState();
}

void nts::OutputComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    (void)otherPin;
    if (pin != 1)
        throw std::out_of_range("Error: Pin index out of range");
    this->_pins[pin - 1].reset(&other);
}
