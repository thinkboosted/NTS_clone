/*
** EPITECH PROJECT, 2025
** NTS_clone
** File description:
** testCircuit
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/Circuit.hpp"



Test(circuit, add_output_component) {
    nts::Circuit circuit;
    circuit.addComponent("output", "Out1");
    // compute() should return a valid state (default UNDEFINED)
    nts::Tristate state = circuit.compute("Out1");
    // Replace nts::UNDEFINED with the appropriate default value if different.
    cr_assert_eq(state, nts::UNDEFINED);
}

// Test linking two output components.
Test(circuit, link_components) {
    nts::Circuit circuit;
    circuit.addComponent("output", "Out1");
    circuit.addComponent("output", "Out2");
    circuit.linkComponents("Out1", "Out2", 1, 1);
}

// Test simulate, display, and dump methods execute without error.
Test(circuit, simulate_display_dump) {
    cr_redirect_stdout();
    nts::Circuit circuit;
    circuit.addComponent("output", "Out1");
    circuit.simulate();
    circuit.display();
}

// Test setComponentState and compute.
Test(circuit, set_and_compute_state) {
    cr_redirect_stdout();
    nts::Circuit circuit;
    circuit.addComponent("output", "Out1");

    // Set a new state and then check compute returns that state.
    nts::Tristate newState = nts::FALSE;
    circuit.setComponentState("Out1", newState);
    nts::Tristate state = circuit.compute("Out1");
    cr_assert_eq(state, newState);
}

// Test for invalid component name.
Test(circuit, invalid_component_name) {
    nts::Circuit circuit;
    circuit.addComponent("output", "Out1");
    cr_assert_throw(circuit.compute("InvalidName"), std::out_of_range);
}

// Test for invalid component type.
Test(circuit, invalid_component_type) {
    nts::Circuit circuit;
    cr_assert_throw(circuit.addComponent("invalid", "Out1"), std::invalid_argument);
}
