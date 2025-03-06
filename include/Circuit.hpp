#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include "IComponent.hpp"
#include "Factory.hpp"
#include "./specialComponents/Output.hpp"
#include "specialComponents/Input.hpp"
#include "specialComponents/Clock.hpp"
#include "specialComponents/True.hpp"
#include "specialComponents/False.hpp"
#include <vector>

#include <iostream>
#include "./specialComponents/Input.hpp"

namespace nts
{
    class Circuit {
        public:
            Circuit();
            ~Circuit();

            void addComponent(const std::string &type, const std::string &name);
            void linkComponents(const std::string &name1, const std::string &name2, std::size_t pin1, std::size_t pin2) const;
            void simulate(size_t tick);
            void display() const;
            void displayInputs() const;
            nts::Tristate compute(const std::string &name) const;
            size_t getTick() const { return _tick; }
            void setInputState(nts::InputComponent &input, nts::Tristate state) const;
            std::shared_ptr<nts::IComponent> &getComponent(const std::string &name);

        private:
            mutable size_t _tick;
		    std::vector<nts::OutputComponent*> _outputs;
            mutable std::vector<std::shared_ptr<nts::IComponent>> _tempComponents;
            std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> _components;
            Factory _factory;
            void displayComponentState(const std::string& name, nts::Tristate state) const;
    };
}
#endif // CIRCUIT_HPP