
/*
** EPITECH PROJECT, 2025
** NTS_clone
** File description:
** test basic circuit
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/Circuit.hpp"

Test(Circuit, add_input_component) {
    nts::Circuit circuit;
    circuit.addComponent("input", "In1");
    nts::Tristate state = circuit.compute("In1");
    cr_assert_eq(state, nts::UNDEFINED, "InputComponent should be initialized to UNDEFINED");
}

Test(Circuit, add_output_component) {
    nts::Circuit circuit;
    circuit.addComponent("output", "Out1");
    nts::Tristate state = circuit.compute("Out1");
    cr_assert_eq(state, nts::UNDEFINED, "OutputComponent should be initialized to UNDEFINED");
}

Test(Circuit, link_input_to_output) {
    nts::Circuit circuit;
    circuit.addComponent("input", "In1");
    circuit.addComponent("output", "Out1");
    circuit.linkComponents("In1", "Out1", 1, 1);
    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In1").get()), nts::TRUE);
    circuit.simulate(1);
    nts::Tristate state = circuit.compute("Out1");
    cr_assert_eq(state, nts::TRUE, "Output should be TRUE when input is TRUE");
}

Test(Circuit, and_gate_behavior) {
    nts::Circuit circuit;
    circuit.addComponent("input", "In1");
    circuit.addComponent("input", "In2");
    circuit.addComponent("and", "And1");
    circuit.addComponent("output", "Out1");

    circuit.linkComponents("In1", "And1", 1, 1);
    circuit.linkComponents("In2", "And1", 1, 2);
    circuit.linkComponents("And1", "Out1", 3, 1);

    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In1").get()), nts::TRUE);

    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In2").get()), nts::TRUE);
    circuit.simulate(1);
    nts::Tristate state = circuit.compute("Out1");
    cr_assert_eq(state, nts::TRUE, "Output should be TRUE when both inputs are TRUE");

    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In2").get()), nts::FALSE);
    circuit.simulate(2);
    state = circuit.compute("Out1");
    cr_assert_eq(state, nts::FALSE, "Output should be FALSE when one input is FALSE");
}

Test(Circuit, or_gate_behavior) {
    nts::Circuit circuit;
    circuit.addComponent("input", "In1");
    circuit.addComponent("input", "In2");
    circuit.addComponent("or", "Or1");
    circuit.addComponent("output", "Out1");

    circuit.linkComponents("In1", "Or1", 1, 1);
    circuit.linkComponents("In2", "Or1", 1, 2);
    circuit.linkComponents("Or1", "Out1", 3, 1);

    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In1").get()), nts::TRUE);
    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In2").get()), nts::FALSE);
    circuit.simulate(1);
    nts::Tristate state = circuit.compute("Out1");
    cr_assert_eq(state, nts::TRUE, "Output should be TRUE when one input is TRUE");

    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In1").get()), nts::FALSE);
    circuit.simulate(2);
    state = circuit.compute("Out1");
    cr_assert_eq(state, nts::FALSE, "Output should be FALSE when both inputs are FALSE");
}

Test(Circuit, not_gate_behavior) {
    nts::Circuit circuit;
    circuit.addComponent("input", "In1");
    circuit.addComponent("not", "Not1");
    circuit.addComponent("output", "Out1");

    circuit.linkComponents("In1", "Not1", 1, 1);
    circuit.linkComponents("Not1", "Out1", 2, 1);

    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In1").get()), nts::TRUE);
    circuit.simulate(1);
    nts::Tristate state = circuit.compute("Out1");
    cr_assert_eq(state, nts::FALSE, "Output should be FALSE when input is TRUE");

    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In1").get()), nts::FALSE);
    circuit.simulate(2);
    state = circuit.compute("Out1");
    cr_assert_eq(state, nts::TRUE, "Output should be TRUE when input is FALSE");
}

Test(Circuit, xor_gate_behavior) {
    nts::Circuit circuit;
    circuit.addComponent("input", "In1");
    circuit.addComponent("input", "In2");
    circuit.addComponent("xor", "Xor1");
    circuit.addComponent("output", "Out1");

    circuit.linkComponents("In1", "Xor1", 1, 1);
    circuit.linkComponents("In2", "Xor1", 1, 2);
    circuit.linkComponents("Xor1", "Out1", 3, 1);

    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In1").get()), nts::TRUE);
    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In2").get()), nts::FALSE);
    circuit.simulate(1);
    nts::Tristate state = circuit.compute("Out1");
    cr_assert_eq(state, nts::TRUE, "Output should be TRUE when inputs are different");

    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("In2").get()), nts::TRUE);
    circuit.simulate(2);
    state = circuit.compute("Out1");
    cr_assert_eq(state, nts::FALSE, "Output should be FALSE when inputs are the same");
}