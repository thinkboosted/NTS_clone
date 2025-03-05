/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Undefined
*/

#include "../../include/specialComponents/Undefined.hpp"

nts::UndefinedComponent::UndefinedComponent(const std::string &name) : AComponent(name, 0)
{
    this->setState(nts::UNDEFINED);
}

void nts::UndefinedComponent::simulate(std::size_t tick)
{
    (void)tick;
}

nts::Tristate nts::UndefinedComponent::compute(std::size_t tick)
{
    (void)tick;
    return this->getState();
}

void nts::UndefinedComponent::setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin)
{
    (void)otherPin;
    (void)pin;
    (void)other;
}

