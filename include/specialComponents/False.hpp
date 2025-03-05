#ifndef FALSE_HPP
#define FALSE_HPP

#include <string>
#include <memory>
#include "../AComponent.hpp"
#include <iostream>

namespace nts
{
    class FalseComponent : public AComponent
    {
        public:
            FalseComponent(const std::string &name);
            ~FalseComponent() = default;

            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            void simulate() override;
            void compute() override;
            nts::Tristate getState() const override;
            void setState(nts::Tristate state) override;
    };
}

#endif // FALSE_HPP