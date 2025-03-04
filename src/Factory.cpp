/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Factory
*/

#include "../include/Factory.hpp"
#include "./specialComponents/AND.hpp"
#include "../include/specialComponents/Clock.hpp"
#include "../include/specialComponents/Input.hpp"
#include "../include/specialComponents/Output.hpp"
#include "../include/specialComponents/True.hpp"
#include "../include/specialComponents/False.hpp"

std::unique_ptr<nts::IComponent> nts::Factory::createComponent(const std::string &type, const std::string &name) const
{
    if (type == "false")
        return createFalse(name);
    else if (type == "true")
        return createTrue(name);
    else if (type == "input")
        return createInput(name);
    else if (type == "output")
        return createOutput(name);
    else if (type == "clock")
        return createClock(name);
    else if (type == "and")
        return createAND(name);
    else
        return nullptr;
}

std::unique_ptr<nts::IComponent> nts::Factory::createFalse(const std::string &name) const
{
    return std::make_unique<nts::FalseComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::Factory::createTrue(const std::string &name) const
{
    return std::make_unique<nts::TrueComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::Factory::createInput(const std::string &name) const
{
    return std::make_unique<nts::InputComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::Factory::createOutput(const std::string &name) const
{
    return std::make_unique<nts::OutputComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::Factory::createClock(const std::string &name) const
{
    return std::make_unique<nts::ClockComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::Factory::createAND(const std::string &name) const
{
    return std::make_unique<nts::ANDComponent>(name);
}