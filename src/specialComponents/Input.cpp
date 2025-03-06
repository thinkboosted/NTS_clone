/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Input
*/

#include "../../include/specialComponents/Input.hpp"
#include "../../include/specialComponents/True.hpp"
#include "../../include/specialComponents/False.hpp"
#include "../../include/specialComponents/Undefined.hpp"

nts::InputComponent::InputComponent(const std::string &name) : AComponent(name, 1)
{
    this->setState(nts::UNDEFINED);
}

void nts::InputComponent::simulate(std::size_t tick)
{
    (void)tick;
    auto pin = this->_pins[0].lock();
    if (!pin)
        this->setState(nts::UNDEFINED);
    else
        this->setState(pin->compute(tick));
    this->setState(pin->compute(tick));
}

nts::Tristate nts::InputComponent::compute(std::size_t tick)
{
    this->simulate(tick);
    return this->getState();
}

void nts::InputComponent::setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin)
{
    (void)otherPin;
    if (pin == 1)
        this->_pins[pin - 1] = other;
    else
        throw std::invalid_argument("Pin does not exist");
}