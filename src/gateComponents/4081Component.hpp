#ifndef COMPONENT4081_HPP
#define COMPONENT4081_HPP

#include <string>
#include <memory>
#include "AGate.hpp"

namespace nts
{
    class Component4081 : public AGate
    {
        public:
            Component4081(const std::string &name = "4081");
            ~Component4081();

            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // COMPONENT4081_HPP
