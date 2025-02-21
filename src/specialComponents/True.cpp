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

void nts::TrueComponent::simulate()
{
}

void nts::TrueComponent::compute()
{
}
