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

    void ANDComponent::simulate()
    {
        // Implementation of simulate
    }

    void ANDComponent::compute()
    {
        // Implementation of compute
    }

    void ANDComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
    {
        (void)otherPin;
        (void)pin;
        (void)other;
    }

}