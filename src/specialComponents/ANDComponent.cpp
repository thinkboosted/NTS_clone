/*
** EPITECH PROJECT, 2025
** NTS_clone
** File description:
** ANDComponent
*/

#include "AND.hpp"
#include <iostream>

namespace nts
{
    ANDComponent::ANDComponent(const std::string &name) : AComponent(name, 3)
    {
        this->setState(nts::UNDEFINED);
    }

    ANDComponent::~ANDComponent()
    {
    }

    void ANDComponent::setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin)
    {
        (void)otherPin;
        if (pin >= 1 && pin <= 3)
            this->_pins[pin - 1] = other; // This stores a weak_ptr now
        else
            throw std::invalid_argument("Pin does not exist");
    }

    void ANDComponent::simulate(std::size_t tick)
    {
        if (tick == this->_lastTick)
            return;
        this->_lastTick = tick;

        auto pin0 = this->_pins[0].lock();
        auto pin1 = this->_pins[1].lock();

        if (!pin0 || !pin1)
            throw std::invalid_argument("Pin not linked or component destroyed");
        if (pin0->compute(tick) == nts::TRUE && pin1->compute(tick) == nts::TRUE)
            this->setState(nts::TRUE);
        else
            this->setState(nts::FALSE);
    }

    nts::Tristate ANDComponent::compute(std::size_t tick)
    {
        this->simulate(tick);
        return this->getState();
    }
}