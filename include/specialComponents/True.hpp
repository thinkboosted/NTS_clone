#ifndef TRUE_HPP
#define TRUE_HPP

#include <string>
#include <memory>
#include "../AComponent.hpp"

namespace nts
{
    class TrueComponent : public AComponent
    {
        public:
            TrueComponent(const std::string &name);
            ~TrueComponent() = default;

            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // TRUE_HPP
