#include "XORComponent.hpp"
#include <iostream>

namespace nts
{
    XORComponent::XORComponent(const std::string &name) : AComponent(name, 3)
    {
        this->setState(nts::UNDEFINED);
    }

    XORComponent::~XORComponent()
    {
    }

    void XORComponent::setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin)
    {
        (void)otherPin;
        if (pin >= 1 && pin <= 3)
            this->_pins[pin - 1] = other;
        else
            throw std::invalid_argument("Pin does not exist");
    }

    nts::Tristate XORComponent::calculateState(nts::Tristate first, nts::Tristate second)
    {
        if (first == nts::UNDEFINED || second == nts::UNDEFINED)
            return nts::UNDEFINED;
        else if (first == second)
            return nts::FALSE;
        else
            return nts::TRUE;
    }

    void XORComponent::simulate(std::size_t tick)
    {
        nts::Tristate first = UNDEFINED;
        nts::Tristate second = UNDEFINED;

        if (tick == this->_lastTick)
            return;
        this->_lastTick = tick;

        if (this->_pins[0].lock() != nullptr)
            first = this->_pins[0].lock()->compute(tick);
        if (this->_pins[1].lock() != nullptr)
            second = this->_pins[1].lock()->compute(tick);
        this->setState(calculateState(first, second));
    }

    nts::Tristate XORComponent::compute(std::size_t tick)
    {
        this->simulate(tick);
        return this->getState();
    }
}