/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** True
*/

#include "True.hpp"

nts::TrueComponent::TrueComponent(const std::string &name) : AComponent(name, 0)
{
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

void nts::TrueComponent::setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin)
{
    (void)otherPin;
    (void)pin;
    (void)other;
}

