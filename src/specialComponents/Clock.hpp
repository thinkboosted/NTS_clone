#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <string>
#include <memory>
#include "../../include/AComponent.hpp"

namespace nts
{
    class ClockComponent : public AComponent
    {
        public:
            ClockComponent(const std::string &name);
            ~ClockComponent() = default;

            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            void simulate() override;
            void compute() override;
    };
}

#endif // CLOCK_HPP
