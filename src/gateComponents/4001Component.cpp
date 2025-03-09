#include "./4001Component.hpp"
#include "../elementaryComponents/NORComponent.hpp"
#include <iostream>

namespace nts
{
    Component4001::Component4001(const std::string &name) : AGate(name, 14)
    {
        this->setState(UNDEFINED);
    }

    Component4001::~Component4001()
    {
    }

    void Component4001::setLink(std::size_t pin, std::shared_ptr<IComponent> other, std::size_t otherPin)
    {
        (void)otherPin;
        if (pin < 1 || pin > 13 || pin == 7) {
            return;
        } else {
            this->_pins[pin - 1] = other;
        }
    }

    void Component4001::simulate(std::size_t tick)
    {
        if (tick == this->_lastTick)
            return;
        this->_lastTick = tick;

        for (size_t i = 0; i < 4; i++) {
            size_t input1Pin;
            size_t input2Pin;
            size_t outputPin;
            switch (i) {
                case 0:
                    input1Pin = 1;
                    input2Pin = 2;
                    outputPin = 3;
                    break;
                case 1:
                    input1Pin = 5;
                    input2Pin = 6;
                    outputPin = 4;
                    break;
                case 2:
                    input1Pin = 8;
                    input2Pin = 9;
                    outputPin = 10;
                    break;
                case 3:
                    input1Pin = 12;
                    input2Pin = 13;
                    outputPin = 11;
                    break;
            }
            Tristate input1 = this->_pins[input1Pin - 1].lock() ? this->_pins[input1Pin - 1].lock()->compute(tick) : UNDEFINED;
            Tristate input2 = this->_pins[input2Pin - 1].lock() ? this->_pins[input2Pin - 1].lock()->compute(tick) : UNDEFINED;
            Tristate output = NORComponent::calculateState(input1, input2);
            if (auto outputPinComponent = this->_pins[outputPin - 1].lock()) {
                outputPinComponent->setState(output);
            }
        }
    }

    Tristate Component4001::compute(std::size_t tick)
    {
        this->simulate(tick);
        return UNDEFINED;
    }
}
