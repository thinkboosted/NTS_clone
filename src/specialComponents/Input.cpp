/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Input
*/

#include "../../include/specialComponents/Input.hpp"

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
