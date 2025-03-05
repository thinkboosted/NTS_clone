/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Input
*/

#include "Input.hpp"

nts::InputComponent::InputComponent(const std::string &name) : AComponent(name)
{
    this->_pins = new std::unique_ptr<nts::IComponent>[1];
    this->_pins[0] = nullptr;
    this->setState(nts::UNDEFINED);
}

void nts::InputComponent::simulate()
{
}

void nts::InputComponent::compute()
{
}

void nts::InputComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin != 1)
        throw std::invalid_argument("Invalid pin for input component");
    _pins[0] = std::unique_ptr<nts::IComponent>(&other);
    (void)otherPin;
}