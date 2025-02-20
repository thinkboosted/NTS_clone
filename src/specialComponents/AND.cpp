/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** AND
*/

#include "../../include/specialComponents/AND.hpp"
#include <stdexcept>

nts::ANDComponent::ANDComponent(const std::string &name) : AComponent(name)
{
    this->_pins = new std::unique_ptr<nts::IComponent>[3];
    for (int i = 0; i < 3; ++i)
        this->_pins[i] = nullptr;
    this->setState(nts::UNDEFINED);
}

void nts::ANDComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin == 0 || pin > 2)
        throw std::out_of_range("Pin number out of range");
    this->_pins[pin] = std::make_unique<nts::IComponent>(other);
}

void nts::ANDComponent::simulate()
{
    // Simulation logic for AND gate
}

void nts::ANDComponent::compute()
{
    if (this->_pins[0] && this->_pins[1])
    {
        nts::Tristate state1 = this->_pins[0]->getState();
        nts::Tristate state2 = this->_pins[1]->getState();
        if (state1 == nts::TRUE && state2 == nts::TRUE)
            this->setState(nts::TRUE);
        else
            this->setState(nts::FALSE);
    }
    else
    {
        this->setState(nts::UNDEFINED);
    }
}
