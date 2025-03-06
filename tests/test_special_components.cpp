/*
** EPITECH PROJECT, 2025
** NTS_clone
** File description:
** test_special_components
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/specialComponents/True.hpp"
#include "../include/specialComponents/False.hpp"
#include "../include/specialComponents/Clock.hpp"
#include "../include/specialComponents/Input.hpp"
#include "../include/specialComponents/Output.hpp"
#include "../include/Circuit.hpp"
#include "../src/specialComponents/AND.hpp"

// Test(TrueComponent, initial_state)
// {
//     nts::TrueComponent trueComp("true");
//     cr_assert_eq(trueComp.compute(1), nts::TRUE, "TrueComponent should be initialized to TRUE but is %d", trueComp.getState());
// }

// Test(FalseComponent, initial_state)
// {
//     nts::FalseComponent falseComp("false");
//     cr_assert_eq(falseComp.compute(1), nts::FALSE, "FalseComponent should be initialized to FALSE but is %d", falseComp.getState());
// }

// Test(ClockComponent, initial_state)
// {
//     nts::ClockComponent clockComp("clock");
//     cr_assert_eq(clockComp.getState(), nts::UNDEFINED, "ClockComponent should be initialized to UNDEFINED but is %d", clockComp.getState());
// }

// Test(InputComponent, initial_state)
// {
//     nts::InputComponent inputComp("input");
//     cr_assert_eq(inputComp.getState(), nts::UNDEFINED, "InputComponent should be initialized to UNDEFINED but is %d", inputComp.getState());
// }

// Test(OutputComponent, initial_state)
// {
//     nts::OutputComponent outputComp("output");
//     cr_assert_eq(outputComp.getState(), nts::UNDEFINED, "OutputComponent should be initialized to UNDEFINED");
// }

// Test(InputComponent, set_state)
// {
//     nts::InputComponent inputComp("input");
//     inputComp.setState(nts::TRUE);
//     cr_assert_eq(inputComp.getState(), nts::TRUE, "InputComponent state should be set to TRUE");
// }

// Test(ClockComponent, toggle_state)
// {
//     nts::ClockComponent clockComp("clock");
//     clockComp.setState(nts::TRUE);
//     cr_assert_eq(clockComp.getState(), nts::TRUE, "ClockComponent state should be set to TRUE");
//     clockComp.setState(nts::FALSE);
//     cr_assert_eq(clockComp.getState(), nts::FALSE, "ClockComponent state should be set to FALSE");
// }

Test(Circuit, clock_behavior)
{
    nts::Circuit circuit;
    circuit.addComponent("clock", "clock");
    circuit.addComponent("output", "output");
    circuit.linkComponents("clock", "output", 1, 1);

    circuit.simulate(circuit.getTick() + 1);
    cr_assert_eq(circuit.compute("output"), nts::UNDEFINED, "Output should be UNDEFINED");
    circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("clock").get()), nts::TRUE);
    cr_assert_eq(circuit.compute("output"), nts::UNDEFINED, "Output should be UNDEFINED");
    circuit.simulate(circuit.getTick() + 1);
    cr_assert_eq(circuit.compute("output"), nts::TRUE, "Output should be TRUE but is %d while clock is %d", circuit.compute("output"), circuit.compute("clock"));
    circuit.simulate(circuit.getTick() + 1);
    cr_assert_eq(circuit.compute("output"), nts::FALSE, "Output should be FALSE");
}

// clock with 2 pins
Test(Circuit, clock_with_2_pins_behavior)
{
    nts::Circuit circuit;
    circuit.addComponent("clock", "clock");
    circuit.addComponent("output", "output");
    circuit.linkComponents("clock", "output", 1, 1);

    cr_assert_throw(circuit.linkComponents("clock", "output", 2, 1), std::invalid_argument, "Should throw for invalid pin");
}

// Test(Circuit, and_behavior)
// {
//     nts::Circuit circuit;
//     circuit.addComponent("input", "input1");
//     circuit.addComponent("input", "input2");
//     circuit.addComponent("and", "and");
//     circuit.addComponent("output", "output");

//     circuit.linkComponents("input1", "and", 1, 1);
//     circuit.linkComponents("input2", "and", 1, 2);
//     circuit.linkComponents("and", "output", 3, 1);

//     circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("input1").get()), nts::TRUE);
//     circuit.setInputState(*dynamic_cast<nts::InputComponent*>(circuit.getComponent("input2").get()), nts::TRUE);
//     circuit.simulate(1);
//     cr_assert_eq(circuit.compute("output"), nts::TRUE, "Output should be TRUE");
// }