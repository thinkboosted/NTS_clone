#ifndef COMPONENT4011_HPP
#define COMPONENT4011_HPP

#include <string>
#include <memory>
#include "AGate.hpp"

namespace nts
{
    class Component4011 : public AGate
    {
        public:
            Component4011(const std::string &name = "4011");
            ~Component4011();

            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // COMPONENT4011_HPP
