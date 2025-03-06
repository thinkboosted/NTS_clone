/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Clock
*/

#include "../../include/specialComponents/Clock.hpp"
#include <iostream>

nts::ClockComponent::ClockComponent(const std::string &name) : InputComponent(name)
{
    this->_lastTick = 0;
}

void nts::ClockComponent::setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin)
{
    (void)otherPin;
    if (pin == 1)
        this->_pins[pin - 1] = other; // This stores a weak_ptr now
    else
        throw std::invalid_argument("Pin does not exist");
}

void nts::ClockComponent::simulate(std::size_t tick)
{
    if (tick == this->_lastTick)
        return;
    this->_lastTick = tick;
    if (_pins[0].lock() == nullptr)
        return;
    this->setState(this->_pins[0].lock()->compute(tick));
}

nts::Tristate nts::ClockComponent::compute(std::size_t tick)
{
    this->simulate(tick);
    return this->getState();
}