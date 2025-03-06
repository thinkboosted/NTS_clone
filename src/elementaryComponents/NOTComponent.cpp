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

    void NOTComponent::simulate(std::size_t tick)
    {
        if (tick == this->_lastTick)
            return;
        this->_lastTick = tick;
        if (this->_pins[0].lock() == nullptr || this->_pins[0].lock()->compute(tick) == nts::UNDEFINED)
            return;
        this->setState(this->_pins[0].lock()->compute(tick) == nts::TRUE ? nts::FALSE : nts::TRUE);
    }

    nts::Tristate NOTComponent::compute(std::size_t tick)
    {
        this->simulate(tick);
        return this->getState();
    }
}