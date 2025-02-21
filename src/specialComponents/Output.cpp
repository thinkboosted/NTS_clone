/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Output
*/

#include "../../include/specialComponents/Output.hpp"

nts::OutputComponent::OutputComponent(const std::string &name) : AComponent(name)
{
    this->_pins = new std::unique_ptr<nts::IComponent>[1];
    this->_pins[0] = nullptr;
    this->setState(nts::UNDEFINED);
}

void nts::OutputComponent::simulate()
{
}

void nts::OutputComponent::compute()
{
}
