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

Test(TrueComponent, initial_state)
{
    nts::TrueComponent trueComp("true");
    cr_assert_eq(trueComp.compute(1), nts::TRUE, "TrueComponent should be initialized to TRUE but is %d", trueComp.getState());
}

Test(FalseComponent, initial_state)
{
    nts::FalseComponent falseComp("false");
    cr_assert_eq(falseComp.compute(1), nts::FALSE, "FalseComponent should be initialized to FALSE but is %d", falseComp.getState());
}

Test(ClockComponent, initial_state)
{
    nts::ClockComponent clockComp("clock");
    cr_assert_eq(clockComp.getState(), nts::UNDEFINED, "ClockComponent should be initialized to UNDEFINED but is %d", clockComp.getState());
}

Test(InputComponent, initial_state)
{
    nts::InputComponent inputComp("input");
    cr_assert_eq(inputComp.getState(), nts::UNDEFINED, "InputComponent should be initialized to UNDEFINED but is %d", inputComp.getState());
}

Test(OutputComponent, initial_state)
{
    nts::OutputComponent outputComp("output");
    cr_assert_eq(outputComp.getState(), nts::UNDEFINED, "OutputComponent should be initialized to UNDEFINED");
}

Test(InputComponent, set_state)
{
    nts::InputComponent inputComp("input");
    inputComp.setState(nts::TRUE);
    cr_assert_eq(inputComp.getState(), nts::TRUE, "InputComponent state should be set to TRUE");
}

Test(ClockComponent, toggle_state)
{
    nts::ClockComponent clockComp("clock");
    clockComp.setState(nts::TRUE);
    cr_assert_eq(clockComp.getState(), nts::TRUE, "ClockComponent state should be set to TRUE");
    clockComp.setState(nts::FALSE);
    cr_assert_eq(clockComp.getState(), nts::FALSE, "ClockComponent state should be set to FALSE");
}

Test(Circuit, clock_behavior)
{
    nts::ClockComponent clockComp("clock");
    nts::OutputComponent outputComp("output");

    outputComp.setLink(1, clockComp, 1);
    clockComp.setLink(1, outputComp, 1);

    cr_assert_eq(clockComp.getState(), nts::UNDEFINED, "ClockComponent should be initialized to UNDEFINED");
    cr_assert_eq(outputComp.getState(), nts::UNDEFINED, "OutputComponent should be initialized to UNDEFINED");

    outputComp.compute(1);
    cr_assert_eq(outputComp.getState(), nts::TRUE, "OutputComponent should reflect ClockComponent state TRUE");

    outputComp.compute(2);
    cr_assert_eq(outputComp.getState(), nts::FALSE, "OutputComponent should reflect ClockComponent state FALSE");

    outputComp.compute(3);
    cr_assert_eq(outputComp.getState(), nts::TRUE, "OutputComponent should reflect ClockComponent state TRUE");
}