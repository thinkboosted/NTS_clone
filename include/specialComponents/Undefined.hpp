#ifndef UNDEFINED_HPP
#define UNDEFINED_HPP

#include <string>
#include <memory>
#include "../AComponent.hpp"

namespace nts
{
    class UndefinedComponent : public AComponent
    {
        public:
            UndefinedComponent(const std::string &name);
            ~UndefinedComponent() = default;

            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // UNDEFINED_HPP
