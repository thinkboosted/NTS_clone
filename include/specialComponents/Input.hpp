#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>
#include <memory>
#include "../AComponent.hpp"

namespace nts
{
    class InputComponent : public AComponent
    {
        public:
            InputComponent(const std::string &name);
            ~InputComponent() = default;

            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // INPUT_HPP
