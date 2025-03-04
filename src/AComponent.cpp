/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** AComponent
*/

#include "../include/AComponent.hpp"

nts::AComponent::AComponent(const std::string &name) : _name(name)
{
}

void nts::AComponent::simulate(std::size_t tick)
{
    (void)tick;
}

nts::Tristate nts::AComponent::compute(std::size_t tick)
{
    (void)tick;
    return _state;
}

void nts::AComponent::setState(nts::Tristate state)
{
    _state = state;
}