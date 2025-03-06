#ifndef ORCOMPONENT_HPP
#define ORCOMPONENT_HPP

#include <string>
#include <memory>
#include "../include/AComponent.hpp"

namespace nts
{
    class ORComponent : public AComponent
    {
        public:
            ORComponent(const std::string &name = "or");
            ~ORComponent();
            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin);
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // ORCOMPONENT_HPP
