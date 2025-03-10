/*
** EPITECH PROJECT, 2025
** NTS_clone
** File description:
** testCircuit
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/Circuit.hpp"



// Test(circuit, add_output_component) {
//     nts::Circuit circuit;
//     circuit.addComponent("output", "Out1");
//     // compute() should return a valid state (default UNDEFINED)
//     nts::Tristate state = circuit.compute("Out1");
//     // Replace nts::UNDEFINED with the appropriate default value if different.
//     cr_assert_eq(state, nts::UNDEFINED);
// }

// Test linking two output components.
Test(circuit, link_components) {
    nts::Circuit circuit;
    circuit.addComponent("output", "Out1");
    circuit.addComponent("output", "Out2");
    circuit.linkComponents("Out1", "Out2", 1, 1);
}

// // Test simulate, display, and dump methods execute without error.
// Test(circuit, simulate_display_dump) {
//     cr_redirect_stdout();
//     nts::Circuit circuit;
//     circuit.addComponent("output", "Out1");
//     circuit.simulate(circuit.getTick() + 1);
//     circuit.display();
// }

// Test for invalid component name.
Test(circuit, invalid_component_name) {
    nts::Circuit circuit;
    circuit.addComponent("output", "Out1");
    cr_assert_throw(circuit.compute("InvalidName"), std::out_of_range);
}
