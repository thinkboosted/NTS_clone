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

            std::shared_ptr<nts::IComponent> createComponent(const std::string &type, const std::string &name) const;

        private:
            std::shared_ptr<nts::IComponent> createUndefined(const std::string &name) const;
            std::shared_ptr<nts::IComponent> createFalse(const std::string &name) const;
            std::shared_ptr<nts::IComponent> createTrue(const std::string &name) const;
            std::shared_ptr<nts::IComponent> createInput(const std::string &name) const;
            std::shared_ptr<nts::IComponent> createOutput(const std::string &name) const;
            std::shared_ptr<nts::IComponent> createClock(const std::string &name) const;

            std::shared_ptr<nts::IComponent> createAND(const std::string &name) const;
            std::shared_ptr<nts::IComponent> createOR(const std::string &name) const;
            std::shared_ptr<nts::IComponent> createNOT(const std::string &name) const;
            std::shared_ptr<nts::IComponent> createXOR(const std::string &name) const;
            std::shared_ptr<nts::IComponent> createNOR(const std::string &name) const;
            std::shared_ptr<nts::IComponent> createNAND(const std::string &name) const;

            std::shared_ptr<nts::IComponent> create4001(const std::string &name) const;
            std::shared_ptr<nts::IComponent> create4011() const;
            std::shared_ptr<nts::IComponent> create4030() const;
            std::shared_ptr<nts::IComponent> create4069() const;
            std::shared_ptr<nts::IComponent> create4071() const;
            std::shared_ptr<nts::IComponent> create4081() const;

            std::shared_ptr<nts::IComponent> create4008() const;
            std::shared_ptr<nts::IComponent> create4013() const;
            std::shared_ptr<nts::IComponent> create4017() const;
            std::shared_ptr<nts::IComponent> create4040() const;
            std::shared_ptr<nts::IComponent> create4094() const;
            std::shared_ptr<nts::IComponent> create4512() const;
            std::shared_ptr<nts::IComponent> create4514() const;
            std::shared_ptr<nts::IComponent> create4801() const;
            std::shared_ptr<nts::IComponent> create2716() const;
    };
}

#endif // FACTORY_HPP