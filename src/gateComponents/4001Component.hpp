#ifndef COMPONENT4001_HPP
#define COMPONENT4001_HPP

#include <string>
#include <memory>
#include "AGate.hpp"

namespace nts
{
    class Component4001 : public AGate
    {
        public:
            Component4001(const std::string &name = "4001");
            ~Component4001();

            void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t tick) override;
    };
}

#endif // COMPONENT4001_HPP
