#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include "IComponent.hpp"
#include "Factory.hpp"

namespace nts
{
    class Circuit {
        public:
            ~Circuit() = default;

            void addComponent(const std::string &type, const std::string &name) const;
            void linkComponents(const std::string &name1, const std::string &name2, std::size_t pin1, std::size_t pin2) const;
            void simulate() const;
            void display() const;
            nts::Tristate compute(const std::string &name) const;
            // void dump() const;

        private:
            std::unordered_map<std::string, std::unique_ptr<nts::IComponent>> _components;
            Factory _factory;
    };
}

#endif // CIRCUIT_HPP