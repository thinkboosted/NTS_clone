#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include <string>
#include <memory>

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

            virtual void simulate() = 0;
            virtual void compute() = 0;
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t) = 0;

            virtual nts::Tristate getState() const = 0;
            virtual void setState(nts::Tristate state) = 0;
    };
}

#endif // ICOMPONENT_HPP