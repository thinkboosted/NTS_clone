#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include "IComponent.hpp"
#include "Factory.hpp"
#include "./specialComponents/Output.hpp"
#include <vector>

namespace nts
{
    class Circuit {
        public:
            ~Circuit() = default;

            void addComponent(const std::string &type, const std::string &name) const;
            void linkComponents(const std::string &name1, const std::string &name2, std::size_t pin1, std::size_t pin2) const;
            void simulate() const;
            void display() const;
            void dump() const;
            nts::Tristate compute(const std::string &name) const;

        private:
		    std::vector<nts::OutputComponent*> _outputs;
            std::unordered_map<std::string, std::unique_ptr<nts::IComponent>> _components;
            Factory _factory;
    };
}

#endif // CIRCUIT_HPP