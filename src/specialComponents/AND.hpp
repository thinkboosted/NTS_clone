#ifndef AND_HPP
#define AND_HPP

#include <string>
#include <memory>
#include "../include/AComponent.hpp"

namespace nts
{
    class ANDComponent : public AComponent
    {
        public:
            ANDComponent(const std::string &name = "and");
            ~ANDComponent();
            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin);
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // AND_HPP
