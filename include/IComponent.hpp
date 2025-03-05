#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include <string>
#include <memory>
#include <stdexcept>

namespace nts
{
    enum Tristate
    {
        UNDEFINED = (-true),
        TRUE = true,
        FALSE = false
    };

    class IComponent
    {
        public:
            virtual ~IComponent() = default;

            virtual void simulate(std::size_t tick) = 0;
            virtual nts::Tristate compute(std::size_t tick) = 0;
            virtual void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin) = 0;
            virtual nts::Tristate getState() const = 0;
            virtual void setState(nts::Tristate state) = 0;
            virtual const std::string &getName() const = 0;
    };
}

#endif // ICOMPONENT_HPP