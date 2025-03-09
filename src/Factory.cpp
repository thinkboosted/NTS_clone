/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Factory
*/

#include "../include/Factory.hpp"
#include "./elementaryComponents/ANDComponent.hpp"
#include "./elementaryComponents/NOTComponent.hpp"
#include "./elementaryComponents/ORComponent.hpp"
#include "./elementaryComponents/XORComponent.hpp"
#include "./elementaryComponents/NANDComponent.hpp"
#include "./elementaryComponents/NORComponent.hpp"
#include "./gateComponents/4001Component.hpp"
#include "./gateComponents/4011Component.hpp"
#include "./gateComponents/4030Component.hpp"
#include "./gateComponents/4069Component.hpp"
#include "../include/specialComponents/Clock.hpp"
#include "../include/specialComponents/Input.hpp"
#include "../include/specialComponents/Output.hpp"
#include "../include/specialComponents/True.hpp"
#include "../include/specialComponents/False.hpp"
#include "../include/specialComponents/Undefined.hpp"

std::shared_ptr<nts::IComponent> nts::Factory::createComponent(const std::string &type, const std::string &name) const
{
    if (type == "false")
        return createFalse(name);
    else if (type == "true")
        return createTrue(name);
    else if (type == "undefined")
        return createUndefined(name);
    else if (type == "input")
        return createInput(name);
    else if (type == "output")
        return createOutput(name);
    else if (type == "clock")
        return createClock(name);
    else if (type == "and")
        return createAND(name);
    else if (type == "or")
        return createOR(name);
    else if (type == "xor")
        return createXOR(name);
    else if (type == "not")
        return createNOT(name);
    else if (type == "nand")
        return createNAND(name);
    else if (type == "nor")
        return createNOR(name);
    else if (type == "4001")
        return create4001(name);
    else if (type == "4011")
        return create4011(name);
    else if (type == "4030")
        return create4030(name);
    else if (type == "4069")
        return create4069(name);
    else
        return nullptr;
}

std::shared_ptr<nts::IComponent> nts::Factory::create4069(const std::string &name) const
{
    return std::make_shared<nts::Component4069>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::create4011(const std::string &name) const
{
    return std::make_shared<nts::Component4011>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::create4001(const std::string &name) const
{
    return std::make_shared<nts::Component4001>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createNAND(const std::string &name) const
{
    return std::make_shared<nts::NANDComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createNOR(const std::string &name) const
{
    return std::make_shared<nts::NORComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createUndefined(const std::string &name) const
{
    return std::make_shared<nts::UndefinedComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createFalse(const std::string &name) const
{
    return std::make_shared<nts::FalseComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createTrue(const std::string &name) const
{
    return std::make_shared<nts::TrueComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createInput(const std::string &name) const
{
    return std::make_shared<nts::InputComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createOutput(const std::string &name) const
{
    return std::make_shared<nts::OutputComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createClock(const std::string &name) const
{
    return std::make_shared<nts::ClockComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createAND(const std::string &name) const
{
    return std::make_shared<nts::ANDComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createOR(const std::string &name) const
{
    return std::make_shared<nts::ORComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createXOR(const std::string &name) const
{
    return std::make_shared<nts::XORComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::createNOT(const std::string &name) const
{
    return std::make_shared<nts::NOTComponent>(name);
}

std::shared_ptr<nts::IComponent> nts::Factory::create4030(const std::string &name) const
{
    return std::make_shared<nts::Component4030>(name);
}