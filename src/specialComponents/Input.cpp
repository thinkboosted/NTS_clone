/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Input
*/

#include "../../include/specialComponents/Input.hpp"

nts::InputComponent::InputComponent(const std::string &name) : AComponent(name)
{
    this->_pins = new std::unique_ptr<nts::IComponent>[1];
    this->_pins[0] = nullptr;
    this->setState(nts::UNDEFINED);
}

void nts::InputComponent::simulate(std::size_t tick)
{
    (void)tick;
    if (this->_pins[0] == nullptr)
        throw std::invalid_argument("Pin not linked");
    this->setState(this->_pins[0]->compute(tick));
}

nts::Tristate nts::InputComponent::compute(std::size_t tick)
{
    this->simulate(tick);
    return this->getState();
}

void nts::InputComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    (void)otherPin;
    if (pin != 1)
        throw std::out_of_range("Error: Pin index out of range");
    this->_pins[pin - 1].reset(&other);
}
