/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Clock
*/

#include "../../include/specialComponents/Clock.hpp"

nts::ClockComponent::ClockComponent(const std::string &name) : AComponent(name)
{
    this->_pins = new std::unique_ptr<nts::IComponent>[1];
    this->_pins[0] = nullptr;
    this->setState(nts::UNDEFINED);
}

void nts::ClockComponent::simulate()
{
}

void nts::ClockComponent::compute()
{
}

void nts::ClockComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin != 1)
        throw std::invalid_argument("Error: invalid pin");
    this->_pins[pin - 1] = std::make_unique<nts::IComponent>(other);
}
