#ifndef NOTCOMPONENT_HPP
#define NOTCOMPONENT_HPP

#include <string>
#include <memory>
#include "../include/AComponent.hpp"

namespace nts
{
    class NOTComponent : public AComponent
    {
        public:
            NOTComponent(const std::string &name = "not");
            ~NOTComponent();
            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin);
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // NOTCOMPONENT_HPP
