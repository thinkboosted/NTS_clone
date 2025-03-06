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
    : _factory(nts::Factory()), _tick(0)
{
    _components["false"] = _factory.createComponent("false", "false");
    _components["true"] = _factory.createComponent("true", "true");
    _components["undefined"] = _factory.createComponent("undefined", "undefined");
}

nts::Circuit::~Circuit()
{
    _components.clear();
    _outputs.clear();
}

void nts::Circuit::addComponent(const std::string &type, const std::string &name)
{
    _components[name] = _factory.createComponent(type, name);

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

void nts::Circuit::displayComponentState(const std::string& name, nts::Tristate state) const
{
    char stateChar = 'U';
    if (state == nts::TRUE)
        stateChar = '1';
    else if (state == nts::FALSE)
        stateChar = '0';

    std::cout << "  " << name << ": " << stateChar << std::endl;
}

void nts::Circuit::displayInputs() const
{
    for (const auto &component : _components)
    {
        if (component.first == "true" || component.first == "false" || component.first == "undefined")
            continue;
        auto clock = dynamic_cast<nts::ClockComponent *>(component.second.get());
        if (clock != nullptr)
        {
            displayComponentState(clock->getName(), clock->getState());
            continue;
        }
        auto input = dynamic_cast<nts::InputComponent *>(component.second.get());
        if (input != nullptr)
        {
            displayComponentState(input->getName(), input->getState());
        }
        auto trueComponent = dynamic_cast<nts::TrueComponent *>(component.second.get());
        if (trueComponent != nullptr)
        {
            displayComponentState(trueComponent->getName(), trueComponent->getState());
        }
        auto falseComponent = dynamic_cast<nts::FalseComponent *>(component.second.get());
        if (falseComponent != nullptr)
        {
            displayComponentState(falseComponent->getName(), falseComponent->getState());
        }
    }
}

void nts::Circuit::display() const
{
    std::cout << "tick: " << _tick << std::endl;
    std::cout << "input(s):" << std::endl;
    displayInputs();
    std::cout << "output(s):" << std::endl;
    for (const auto &output : _outputs) {
        displayComponentState(output->getName(), output->getState());
    }
}

nts::Tristate nts::Circuit::compute(const std::string &name) const
{
    return _components.at(name)->compute(_tick);
}

void nts::Circuit::linkComponents(const std::string &name1, const std::string &name2, std::size_t pin1, std::size_t pin2) const
{
    auto comp1 = _components.at(name1);
    auto comp2 = _components.at(name2);

    if (!comp1 || !comp2)
        throw std::runtime_error("Cannot link with null component: " + name1 + " or " + name2);

    comp1->setLink(pin1, comp2, pin2);
    comp2->setLink(pin2, comp1, pin1);
}

void nts::Circuit::setInputState(nts::InputComponent &input, nts::Tristate state) const
{
    if (state == input.getState())
        return;

    std::shared_ptr<nts::IComponent> tempComponent;
    if (state == nts::UNDEFINED)
        input.setLink(1, _components.at("undefined"), 1);
    else if (state == nts::TRUE)
        input.setLink(1, _components.at("true"), 1);
    else
        input.setLink(1, _components.at("false"), 1);
}

std::shared_ptr<nts::IComponent> &nts::Circuit::getComponent(const std::string &name)
{
    return _components.at(name);
}
