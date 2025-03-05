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
    auto pin = this->_pins[0].lock();
    if (!pin)
        throw std::invalid_argument("Pin not linked or component destroyed");
    if (tick == this->_lastTick) {
        std::cerr << "ClockComponent::simulate called twice with the same tick" << std::endl;
        return;
    }
    this->_lastTick = tick;
    if (this->getState() == nts::TRUE)
        this->setState(nts::FALSE);
    else
        this->setState(nts::TRUE);
}

nts::Tristate nts::ClockComponent::compute(std::size_t tick)
{
    this->simulate(tick);
    return this->getState();
}