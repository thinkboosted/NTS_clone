/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Output
*/

#include "../../include/specialComponents/Output.hpp"
#include "../gateComponents/4001Component.hpp"

nts::OutputComponent::OutputComponent(const std::string &name) : AComponent(name, 1)
{
    this->setState(nts::UNDEFINED);
}

void nts::OutputComponent::simulate(std::size_t tick)
{
    (void)tick;
    auto pin = this->_pins[0].lock();
    if (!pin)
        this->setState(nts::UNDEFINED);
    else if (auto component4001 = std::dynamic_pointer_cast<nts::AGate>(pin))
        pin->compute(tick);
    else
        this->setState(pin->compute(tick));
}

nts::Tristate nts::OutputComponent::compute(std::size_t tick)
{
    this->simulate(tick);
    return this->getState();
}

void nts::OutputComponent::setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin)
{
    (void)otherPin;
    if (pin != 1)
        throw std::out_of_range("Error: Pin index out of range");
    this->_pins[pin - 1] = other;
}