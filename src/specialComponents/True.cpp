/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** True
*/

#include "../../include/specialComponents/True.hpp"

nts::TrueComponent::TrueComponent(const std::string &name) : AComponent(name)
{
    this->_pins = new std::unique_ptr<nts::IComponent>[1];
    this->_pins[0] = nullptr;
    this->setState(nts::TRUE);
}

void nts::TrueComponent::simulate(std::size_t tick)
{
    (void)tick;
}

nts::Tristate nts::TrueComponent::compute(std::size_t tick)
{
    (void)tick;
    return this->getState();
}

void nts::TrueComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    (void)otherPin;
    (void)pin;
    (void)other;
}

void nts::TrueComponent::setState(nts::Tristate state)
{
    (void)state;
}
