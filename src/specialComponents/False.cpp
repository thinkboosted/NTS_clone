/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** False
*/

#include "False.hpp"

nts::FalseComponent::FalseComponent(const std::string &name) : AComponent(name)
{
    this->_pins = new std::unique_ptr<nts::IComponent>[1];
    this->_pins[0] = nullptr;
    this->setState(nts::FALSE);
}

void nts::FalseComponent::simulate()
{
}

void nts::FalseComponent::compute()
{
}

void nts::FalseComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    (void)otherPin;
    (void)pin;
    (void)other;
}

nts::Tristate nts::FalseComponent::getState() const
{
    return nts::FALSE;
}

void nts::FalseComponent::setState(nts::Tristate state)
{
    (void)state;
}
