#ifndef NORCOMPONENT_HPP
#define NORCOMPONENT_HPP

#include <string>
#include <memory>
#include "../include/AComponent.hpp"

namespace nts
{
    class NORComponent : public AComponent
    {
        public:
            NORComponent(const std::string &name = "nor");
            ~NORComponent();
            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin);
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
            static nts::Tristate calculateState(nts::Tristate first, nts::Tristate second);
    };
}

#endif // NORCOMPONENT_HPP
