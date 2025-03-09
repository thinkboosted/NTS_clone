#ifndef COMPONENT4069_HPP
#define COMPONENT4069_HPP

#include <string>
#include <memory>
#include "AGate.hpp"

namespace nts
{
    class Component4069 : public AGate
    {
        public:
            Component4069(const std::string &name = "4069");
            ~Component4069();

            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // COMPONENT4069_HPP
