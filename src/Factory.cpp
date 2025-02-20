/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Factory
*/

#include "../include/Factory.hpp"
#include "../include/specialComponents/AND.hpp"
#include "../include/specialComponents/Clock.hpp"
#include "../include/specialComponents/Input.hpp"
#include "../include/specialComponents/Output.hpp"
#include "../include/specialComponents/True.hpp"
#include "../include/specialComponents/False.hpp"

std::unique_ptr<nts::IComponent> nts::Factory::createComponent(const std::string &type) const
{
    if (type == "false")
        return createFalse();
    else if (type == "true")
        return createTrue();
    else if (type == "input")
        return createInput();
    else if (type == "output")
        return createOutput();
    else if (type == "clock")
        return createClock();
    else if (type == "AND")
        return createAND();
    else
        return nullptr;
}

std::unique_ptr<nts::IComponent> nts::Factory::createFalse() const
{
    return std::make_unique<nts::FalseComponent>("false");
}

std::unique_ptr<nts::IComponent> nts::Factory::createTrue() const
{
    return std::make_unique<nts::TrueComponent>("true");
}

std::unique_ptr<nts::IComponent> nts::Factory::createInput() const
{
    return std::make_unique<nts::InputComponent>("input");
}

std::unique_ptr<nts::IComponent> nts::Factory::createOutput() const
{
    return std::make_unique<nts::OutputComponent>("output");
}

std::unique_ptr<nts::IComponent> nts::Factory::createClock() const
{
    return std::make_unique<nts::ClockComponent>("clock");
}

std::unique_ptr<nts::IComponent> nts::Factory::createAND() const
{
    return std::make_unique<nts::ANDComponent>("AND");
}