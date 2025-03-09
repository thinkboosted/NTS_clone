#include "./4069Component.hpp"
#include "../elementaryComponents/NOTComponent.hpp"
#include <iostream>

namespace nts
{
    Component4069::Component4069(const std::string &name) : AGate(name, 14)
    {
        this->setState(UNDEFINED);
    }

    Component4069::~Component4069()
    {
    }

    void Component4069::setLink(std::size_t pin, std::shared_ptr<IComponent> other, std::size_t otherPin)
    {
        (void)otherPin;
        if (pin < 1 || pin > 13 || pin == 7) {
            return;
        } else {
            this->_pins[pin - 1] = other;
        }
    }

    void Component4069::simulate(std::size_t tick)
    {
        if (tick == this->_lastTick)
            return;
        this->_lastTick = tick;

        for (size_t i = 0; i < 6; i++) {
            size_t inputPin;
            size_t outputPin;
            switch (i) {
                case 0:
                    inputPin = 1;
                    outputPin = 2;
                    break;
                case 1:
                    inputPin = 3;
                    outputPin = 4;
                    break;
                case 2:
                    inputPin = 5;
                    outputPin = 6;
                    break;
                case 3:
                    inputPin = 9;
                    outputPin = 8;
                    break;
                case 4:
                    inputPin = 11;
                    outputPin = 10;
                    break;
                case 5:
                    inputPin = 13;
                    outputPin = 12;
                    break;
            }
            Tristate input = this->_pins[inputPin - 1].lock() ? this->_pins[inputPin - 1].lock()->compute(tick) : UNDEFINED;
            Tristate output = NOTComponent::calculateState(input);
            if (auto outputPinComponent = this->_pins[outputPin - 1].lock()) {
                outputPinComponent->setState(output);
            }
        }
    }

    Tristate Component4069::compute(std::size_t tick)
    {
        this->simulate(tick);
        return UNDEFINED;
    }
}
