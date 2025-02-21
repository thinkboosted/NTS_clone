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
            AComponent(const std::string &name);
            virtual ~AComponent() = default;

            virtual void simulate() {};
            virtual void compute() = 0;
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t) = 0;

            const std::string &getName() const { return _name; }
            nts::Tristate getState() const override { return _state; }
            void setState(nts::Tristate state) override { this->_state = state; }

        protected:
            const std::string _name;
            std::unique_ptr<nts::IComponent> *_pins;

        private:
            nts::Tristate _state = nts::UNDEFINED;
    };
}

#endif // ACOMPONENT_HPP