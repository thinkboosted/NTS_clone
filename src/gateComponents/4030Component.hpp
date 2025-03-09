#ifndef COMPONENT4030_HPP
#define COMPONENT4030_HPP

#include <string>
#include <memory>
#include "AGate.hpp"

namespace nts
{
    class Component4030 : public AGate
    {
        public:
            Component4030(const std::string &name = "4030");
            ~Component4030();

            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // COMPONENT4030_HPP
