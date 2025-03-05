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
            this->_pins[pin - 1] = other;
        else
            throw std::invalid_argument("Pin does not exist");
    }

    void ANDComponent::simulate(std::size_t tick)
    {
        if (tick == this->_lastTick)
            return;
        this->_lastTick = tick;
        if (this->_pins[0] == nullptr || this->_pins[1] == nullptr)
            throw std::invalid_argument("Pin not linked");
        if (this->_pins[0]->compute(tick) == nts::TRUE && this->_pins[1]->compute(tick) == nts::TRUE)
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