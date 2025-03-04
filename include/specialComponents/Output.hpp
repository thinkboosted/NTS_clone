#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <string>
#include <memory>
#include "../AComponent.hpp"

namespace nts
{
    class OutputComponent : public AComponent
    {
        public:
            OutputComponent(const std::string &name);
            ~OutputComponent() = default;

            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // OUTPUT_HPP
