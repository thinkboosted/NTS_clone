#include "ORComponent.hpp"
#include <iostream>

namespace nts
{
    ORComponent::ORComponent(const std::string &name) : AComponent(name, 3)
    {
        this->setState(nts::UNDEFINED);
    }

    ORComponent::~ORComponent()
    {
    }

    void ORComponent::setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin)
    {
        (void)otherPin;
        if (pin >= 1 && pin <= 3)
            this->_pins[pin - 1] = other;
        else
            throw std::invalid_argument("Pin does not exist");
    }

    void ORComponent::simulate(std::size_t tick)
    {
        nts::Tristate first;
        nts::Tristate second;

        if (tick == this->_lastTick)
            return;
        this->_lastTick = tick;
        if (this->_pins[0].lock() == nullptr)
            first = nts::UNDEFINED;
        else
            first = this->_pins[0].lock()->compute(tick);
        if (this->_pins[1].lock() == nullptr)
            second = nts::UNDEFINED;
        else
            second = this->_pins[1].lock()->compute(tick);
        if (first == nts::TRUE || second == nts::TRUE)
            this->setState(nts::TRUE);
        else if (first == nts::UNDEFINED || second == nts::UNDEFINED)
            this->setState(nts::UNDEFINED);
        else
            this->setState(nts::FALSE);
    }

    nts::Tristate ORComponent::compute(std::size_t tick)
    {
        this->simulate(tick);
        return this->getState();
    }
}