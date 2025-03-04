#include "AND.hpp"

namespace nts
{
    ANDComponent::ANDComponent(const std::string &name) : AComponent(name)
    {
        this->_pins = new std::unique_ptr<nts::IComponent>[3];
        this->_pins[0] = nullptr;
        this->_pins[1] = nullptr;
        this->_pins[2] = nullptr;
        this->setState(nts::UNDEFINED);
    }

    void ANDComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
    {
        (void)otherPin;
        if (pin == 1 || pin == 2)
            this->_pins[pin - 1].reset(&other);
        else
            throw std::invalid_argument("Pin does not exist");
    }

    void ANDComponent::simulate(std::size_t tick)
    {
        (void)tick;
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