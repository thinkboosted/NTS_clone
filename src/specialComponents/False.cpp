/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** False
*/

#include "False.hpp"

nts::FalseComponent::FalseComponent(const std::string &name) : AComponent(name, 0)
{
    this->setState(nts::FALSE);
}

void nts::FalseComponent::simulate(std::size_t tick)
{
    (void)tick;
}

nts::Tristate nts::FalseComponent::compute(std::size_t tick)
{
    (void)tick;
    return this->getState();
}

void nts::FalseComponent::setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin)
{
    (void)otherPin;
    (void)pin;
    (void)other;
}
