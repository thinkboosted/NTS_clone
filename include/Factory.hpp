#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include "IComponent.hpp"

namespace nts
{
    class Factory {
        public:
            ~Factory() = default;

            std::unique_ptr<nts::IComponent> createComponent(const std::string &type) const;

        private:
            std::unique_ptr<nts::IComponent> createFalse() const;
            std::unique_ptr<nts::IComponent> createTrue() const;
            std::unique_ptr<nts::IComponent> createInput() const;
            std::unique_ptr<nts::IComponent> createOutput() const;
            std::unique_ptr<nts::IComponent> createClock() const;

            std::unique_ptr<nts::IComponent> createAND() const;
            std::unique_ptr<nts::IComponent> createOR() const;
            std::unique_ptr<nts::IComponent> createNOR() const;
            std::unique_ptr<nts::IComponent> createXOR() const;

            std::unique_ptr<nts::IComponent> create4001() const;
            std::unique_ptr<nts::IComponent> create4011() const;
            std::unique_ptr<nts::IComponent> create4030() const;
            std::unique_ptr<nts::IComponent> create4069() const;
            std::unique_ptr<nts::IComponent> create4071() const;
            std::unique_ptr<nts::IComponent> create4081() const;

            std::unique_ptr<nts::IComponent> create4008() const;
            std::unique_ptr<nts::IComponent> create4013() const;
            std::unique_ptr<nts::IComponent> create4017() const;
            std::unique_ptr<nts::IComponent> create4040() const;
            std::unique_ptr<nts::IComponent> create4094() const;
            std::unique_ptr<nts::IComponent> create4512() const;
            std::unique_ptr<nts::IComponent> create4514() const;
            std::unique_ptr<nts::IComponent> create4801() const;
            std::unique_ptr<nts::IComponent> create2716() const;
    };
}

#endif // FACTORY_HPP