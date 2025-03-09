#ifndef NANDCOMPONENT_HPP
#define NANDCOMPONENT_HPP

#include <string>
#include <memory>
#include "../include/AComponent.hpp"

namespace nts
{
    class NANDComponent : public AComponent
    {
        public:
            NANDComponent(const std::string &name = "nand");
            ~NANDComponent();
            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin);
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
            static nts::Tristate calculateState(nts::Tristate first, nts::Tristate second);
    };
}

#endif // NANDCOMPONENT_HPP
