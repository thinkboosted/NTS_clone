/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** False
*/

#include "../../include/specialComponents/False.hpp"

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