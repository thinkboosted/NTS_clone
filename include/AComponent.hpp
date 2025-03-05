#ifndef ACOMPONENT_HPP
#define ACOMPONENT_HPP

#include <string>
#include <memory>
#include "IComponent.hpp"

namespace nts
{
    class AComponent : public IComponent
    {
        public:
            AComponent(const std::string &name, std::size_t nbPins);
            virtual ~AComponent();

            virtual void simulate(std::size_t tick);
            virtual nts::Tristate compute(std::size_t tick);
            virtual void setState(nts::Tristate state) override;
            virtual void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin) = 0;
            virtual nts::Tristate getState() const override { return _state; }
            const std::string &getName() const { return _name; }

        protected:
            const std::string _name;
            std::shared_ptr<nts::IComponent> *_pins;
            std::size_t _lastTick;

        private:
            nts::Tristate _state;
    };
}

#endif // ACOMPONENT_HPP