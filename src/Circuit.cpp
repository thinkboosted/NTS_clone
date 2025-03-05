/*
** EPITECH PROJECT, 2025
** NTS_clone
** File description:
** Circuit
*/

#include "../include/Circuit.hpp"
#include "../include/specialComponents/Input.hpp"
#include "../include/IComponent.hpp"

nts::Circuit::Circuit()
{
    _factory = nts::Factory();
    _tick = 0;
    _factory.createComponent("true");
    _factory.createComponent("false");
    _factory.createComponent("undefined");
}

nts::Circuit::~Circuit()
{
    _components.clear();
    _outputs.clear();
}

void nts::Circuit::addComponent(const std::string &type, const std::string &name)
{
    _components[name] = _factory.createComponent(type);

    if (type == "output") {
        _outputs.push_back(dynamic_cast<nts::OutputComponent*>(_components[name].get()));
    }
}

void nts::Circuit::simulate(size_t tick)
{
    for (const auto &pair : _outputs) {
        pair->compute(tick);
    }
    this->_tick = tick;
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
    return _components.at(name)->compute(_tick);
}

void nts::Circuit::linkComponents(const std::string &name1, const std::string &name2, std::size_t pin1, std::size_t pin2) const
{
    _components.at(name1)->setLink(pin1, _components.at(name2), pin2);
    _components.at(name2)->setLink(pin2, _components.at(name1), pin1);
}

void nts::Circuit::setInputState(nts::InputComponent &input, nts::Tristate state) const
{
    if (state == input.getState())
        return;
    if (state == nts::UNDEFINED)
        input.setLink(1, _factory.createComponent("undefined"), 1);
    else if (state == nts::TRUE)
        input.setLink(1, _factory.createComponent("true"), 1);
    else
        input.setLink(1, _factory.createComponent("false"), 1);

    input.simulate(_tick);
}

std::shared_ptr<nts::IComponent> &nts::Circuit::getComponent(const std::string &name)
{
    return _components.at(name);
}
