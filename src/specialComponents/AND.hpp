#ifndef AND_HPP
#define AND_HPP

#include <string>
#include <memory>
#include "AComponent.hpp"

namespace nts
{
    class ANDComponent : public AComponent
    {
        public:
            ANDComponent(const std::string &name = "AND");
            ~ANDComponent() = default;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            void simulate() override;
            void compute() override;
    };
}

#endif // AND_HPP
