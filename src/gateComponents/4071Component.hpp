#ifndef COMPONENT4071_HPP
#define COMPONENT4071_HPP

#include <string>
#include <memory>
#include "AGate.hpp"

namespace nts
{
    class Component4071 : public AGate
    {
        public:
            Component4071(const std::string &name = "4071");
            ~Component4071();

            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // COMPONENT4071_HPP
