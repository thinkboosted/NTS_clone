#include "NOTComponent.hpp"
#include <iostream>

namespace nts
{
    NOTComponent::NOTComponent(const std::string &name) : AComponent(name, 2)
    {
        this->setState(nts::UNDEFINED);
    }

    NOTComponent::~NOTComponent()
    {
    }

    void NOTComponent::setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin)
    {
        (void)otherPin;
        if (pin >= 1 && pin <= 2)
            this->_pins[pin - 1] = other;
        else
            throw std::invalid_argument("Pin does not exist");
    }

    nts::Tristate NOTComponent::calculateState(nts::Tristate state)
    {
        if (state == nts::TRUE)
            return nts::FALSE;
        else if (state == nts::FALSE)
            return nts::TRUE;
        else
            return nts::UNDEFINED;
    }

    void NOTComponent::simulate(std::size_t tick)
    {
        Tristate state = UNDEFINED;

        if (tick == this->_lastTick)
            return;
        this->_lastTick = tick;
        if (this->_pins[0].lock() != nullptr)
            state = this->_pins[0].lock()->compute(tick);
        this->setState(calculateState(state));
    }

    nts::Tristate NOTComponent::compute(std::size_t tick)
    {
        this->simulate(tick);
        return this->getState();
    }
}