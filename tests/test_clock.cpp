/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Clock Component Tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/specialComponents/Clock.hpp"
#include "../include/Factory.hpp"

// Mock component for testing
class MockComponent : public nts::IComponent {
public:
    MockComponent() : state(nts::UNDEFINED) {}
    ~MockComponent() = default;

    nts::Tristate compute(std::size_t tick) override {
        (void)tick;
        return state;
    }

    void setLink(std::size_t pin, std::shared_ptr<nts::IComponent> other, std::size_t otherPin) override {
        (void)pin;
        (void)other;
        (void)otherPin;
    }

    void simulate(std::size_t tick) override {
        (void)tick;
    }

    void setState(nts::Tristate newState) {
        state = newState;
    }

    // Added implementations for abstract functions
    nts::Tristate getState() const override {
        return state;
    }

    const std::string &getName() const override {
        static const std::string name = "MockComponent";
        return name;
    }

private:
    nts::Tristate state;
};

Test(ClockComponent, initialization) {
    nts::ClockComponent clock("clock");
    cr_assert_eq(clock.getState(), nts::UNDEFINED, "Initial clock state should be UNDEFINED");
}

Test(ClockComponent, setLink_valid) {
    nts::ClockComponent clock("clock");
    auto mock = std::make_shared<MockComponent>();

    // Should not throw
    try {
        clock.setLink(1, mock, 1);
        cr_assert(true, "Setting link to pin 1 should not throw");
    } catch (const std::exception &e) {
        cr_assert(false, "Setting link to pin 1 should not throw but threw: %s", e.what());
    }
}

Test(ClockComponent, setLink_invalid) {
    nts::ClockComponent clock("clock");
    auto mock = std::make_shared<MockComponent>();

    // Should throw for invalid pin
    cr_assert_throw(clock.setLink(2, mock, 1), std::invalid_argument, "Setting link to invalid pin should throw");
}

Test(ClockComponent, simulate_toggle) {
    nts::ClockComponent clock("clock");

    // Set initial state
    clock.setState(nts::TRUE);
    cr_assert_eq(clock.getState(), nts::TRUE, "Initial state should be TRUE");

    // First simulate call should toggle state
    clock.simulate(1);
    cr_assert_eq(clock.getState(), nts::FALSE, "State should toggle to FALSE after simulate");

    // Second simulate call should toggle state again
    clock.simulate(2);
    cr_assert_eq(clock.getState(), nts::TRUE, "State should toggle to TRUE after simulate");

    // Simulate with same tick should not change state
    clock.simulate(2);
    cr_assert_eq(clock.getState(), nts::TRUE, "State should not change when tick is the same");
}

Test(ClockComponent, compute) {
    nts::ClockComponent clock("clock");

    // Set initial state
    clock.setState(nts::FALSE);

    // Compute should return the current state after simulation
    nts::Tristate result = clock.compute(1);
    cr_assert_eq(result, nts::TRUE, "Compute should toggle and return TRUE");

    // Next compute should toggle again
    result = clock.compute(2);
    cr_assert_eq(result, nts::FALSE, "Compute should toggle and return FALSE");
}
