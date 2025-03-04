/*
** EPITECH PROJECT, 2025
** NTS_clone
** File description:
** Circuit
*/

#include "../include/Circuit.hpp"

void nts::Circuit::addComponent(const std::string &type, const std::string &name)
{
    _components[name] = _factory.createComponent(type);

    if (type == "output") {
        _outputs.push_back(dynamic_cast<nts::OutputComponent*>(_components[name].get()));
    }
}

void nts::Circuit::linkComponents(const std::string &name1, const std::string &name2, std::size_t pin1, std::size_t pin2) const
{
    auto &component1 = _components.at(name1);
    auto &component2 = _components.at(name2);

    component1->setLink(pin1, *component2, pin2);
    component2->setLink(pin2, *component1, pin1);
}

void nts::Circuit::simulate(size_t tick) const
{
    for (const auto &pair : _components) {
        pair.second->simulate(tick);
    }
}

void nts::Circuit::display() const
{
    std::cout << "Tick: " << "variable à ajouté" << std::endl;
    std::cout << "input(s):" << std::endl;
    std::cout << "output(s):" << std::endl;
    for (const auto &component : _components) {
        std::cout << component.first << ":" << std::endl;
        component.second->compute(_tick);
    }
}


nts::Tristate nts::Circuit::compute(const std::string &name) const
{
    return _components.at(name)->getState();
}

void nts::Circuit::setComponentState(const std::string &name, nts::Tristate state)
{
    _components.at(name)->setState(state);
}