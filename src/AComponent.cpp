/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** AComponent
*/

#include "../include/AComponent.hpp"

namespace nts
{
    AComponent::AComponent(const std::string &name, std::size_t nbPins) : _name(name), _lastTick(0), _state(nts::UNDEFINED)
    {
        _pins = new std::shared_ptr<nts::IComponent>[nbPins];
        for (std::size_t i = 0; i < nbPins; i++) {
            _pins[i] = nullptr;
        }
    }

    AComponent::~AComponent()
    {
        delete[] _pins;
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