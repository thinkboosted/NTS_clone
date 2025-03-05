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
#include "../include/specialComponents/Undefined.hpp"

std::shared_ptr<nts::IComponent> nts::Factory::createComponent(const std::string &type) const
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
    else if (type == "and")
        return createAND();
    else if (type == "undefined")
        return createUndefined();
    else
        return nullptr;
}

std::shared_ptr<nts::IComponent> nts::Factory::createUndefined() const
{
    return std::make_shared<nts::UndefinedComponent>("undefined");
}

std::shared_ptr<nts::IComponent> nts::Factory::createFalse() const
{
    return std::make_shared<nts::FalseComponent>("false");
}

std::shared_ptr<nts::IComponent> nts::Factory::createTrue() const
{
    return std::make_shared<nts::TrueComponent>("true");
}

std::shared_ptr<nts::IComponent> nts::Factory::createInput() const
{
    return std::make_shared<nts::InputComponent>("input");
}

std::shared_ptr<nts::IComponent> nts::Factory::createOutput() const
{
    return std::make_shared<nts::OutputComponent>("output");
}

std::shared_ptr<nts::IComponent> nts::Factory::createClock() const
{
    return std::make_shared<nts::ClockComponent>("clock");
}

std::shared_ptr<nts::IComponent> nts::Factory::createAND() const
{
    return std::make_shared<nts::ANDComponent>("and");
}