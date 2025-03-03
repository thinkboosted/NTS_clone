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

            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            void simulate() override;
            void compute() override;
            nts::Tristate getState() const override;
            void setState(nts::Tristate state) override;
    };
}

#endif // TRUE_HPP
