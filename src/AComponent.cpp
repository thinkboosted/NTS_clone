/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** AComponent
*/

#include "../include/AComponent.hpp"
#include "../include/specialComponents/True.hpp"
#include "../include/specialComponents/False.hpp"

namespace nts
{
    AComponent::AComponent(const std::string &name, std::size_t nbPins) : _name(name), _lastTick(1), _nbPins(nbPins), _state(nts::UNDEFINED)
    {
        _pins = std::vector<std::weak_ptr<nts::IComponent>>(nbPins);
    }

    AComponent::~AComponent()
    {
    }

    void AComponent::simulate(std::size_t tick)
    {
        (void)tick;
    }

    nts::Tristate AComponent::compute(std::size_t tick)
    {
        (void)tick;
        return _state;
    }

    void AComponent::setState(nts::Tristate state)
    {
        _state = state;
    }
}

bool isTrueFalseComponent(const nts::IComponent& component)
{
    return dynamic_cast<const nts::TrueComponent*>(&component) != nullptr
        || dynamic_cast<const nts::FalseComponent*>(&component) != nullptr;
}
