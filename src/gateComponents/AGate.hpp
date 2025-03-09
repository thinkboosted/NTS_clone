#ifndef AGATE_HPP
#define AGATE_HPP

#include "../include/AComponent.hpp"

namespace nts
{
class AGate : public AComponent {
    public:
        AGate(const std::string &name, size_t nbPins) : AComponent(name, nbPins) {}
        virtual ~AGate() = default;
};
}

#endif // AGATE_HPP