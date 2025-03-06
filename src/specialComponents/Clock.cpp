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

void nts::ClockComponent::setLink(std::size_t pin, ComponentPtr other, std::size_t otherPin)
{
    (void)otherPin;
    if (pin == 1)
        this->_pins[pin - 1] = other;
    else
        throw std::invalid_argument("Pin does not exist");
    _manuallySet = true;
}

void nts::ClockComponent::simulate(std::size_t tick)
{
    if (tick == this->_lastTick)
        return;
    this->_lastTick = tick;
    if (this->_pins[0].lock()) {
        nts::Tristate newState = this->_pins[0].lock()->compute(tick);
        if (this->getState() == nts::UNDEFINED || this->_manuallySet) {
            this->setState(newState);
            this->_manuallySet = false;
        } else {
            if (this->getState() == nts::TRUE)
                this->setState(nts::FALSE);
            else
                this->setState(nts::TRUE);
        }
    } else {
        if (this->getState() == nts::TRUE)
            this->setState(nts::FALSE);
        else if (this->getState() == nts::FALSE)
            this->setState(nts::TRUE);
    }
}

nts::Tristate nts::ClockComponent::compute(std::size_t tick)
{
    this->simulate(tick);
    return this->getState();
}