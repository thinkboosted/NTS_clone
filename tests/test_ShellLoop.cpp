/*
** EPITECH PROJECT, 2025
** test_ShellLoop
** File description:
** Unit tests for ShellLoop class
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/ShellLoop.hpp"
#include "../include/Circuit.hpp"
#include "../include/specialComponents/Input.hpp"
#include <sstream>

class TestableShellLoop : public nts::ShellLoop {
    public:
        using nts::ShellLoop::ShellLoop;  // Hérite du constructeur

        // Exposer les méthodes privées
        using nts::ShellLoop::setComponentValue;
        using nts::ShellLoop::exit;
        using nts::ShellLoop::display;
        using nts::ShellLoop::simulate;
        using nts::ShellLoop::loop;

        // Accès aux membres privés
        bool isRunning() const { return _running; }
    };

// Mock classes to support testing
class MockCircuit : public nts::Circuit {
public:
    mutable int simulateCalls = 0;
    mutable int displayCalls = 0;

    void display() const override {
        displayCalls++;
    }

    // Ajouter également override ici
    void simulate(std::size_t tick) override {
        simulateCalls++;
        _tick = tick;
    }


    std::shared_ptr<nts::IComponent> createMockInput(const std::string &name) {
        auto input = std::make_shared<nts::InputComponent>(name);
        _components[name] = input;
        return input;
    }
};

// Redirect stdout for testing
void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ShellLoop, constructor_initializes_commands, .init = redirect_all_stdout)
{
    MockCircuit circuit;
    TestableShellLoop shell(circuit);

    cr_assert_eq(shell.isRunning(), true);
}

Test(ShellLoop, exit_command_sets_running_to_false, .init = redirect_all_stdout)
{
    MockCircuit circuit;
    TestableShellLoop shell(circuit);

    shell.exit(circuit);
    cr_assert_eq(shell.isRunning(), false);
}

Test(ShellLoop, display_command_calls_circuit_display)
{
    MockCircuit circuit;
    TestableShellLoop shell(circuit);

    shell.display(circuit);
    std::cout << "displayCalls: " << circuit.displayCalls << std::endl;
    cr_assert_eq(circuit.displayCalls, 1);
}

Test(ShellLoop, simulate_command_increases_tick)
{
    MockCircuit circuit;
    TestableShellLoop shell(circuit);

    shell.simulate(circuit);
    std::cout << "simulateCalls: " << circuit.simulateCalls << std::endl;
    //cr_assert_eq(circuit.simulateCalls, 1);
    cr_assert_eq(circuit.getTick(), 1);
}

Test(ShellLoop, setComponentValue_valid_input, .init = redirect_all_stdout)
{
    MockCircuit circuit;
    TestableShellLoop shell(circuit);

    auto inputComponent = circuit.createMockInput("input1");

    // Test setting to TRUE
    bool result = shell.setComponentValue("input1=1", circuit);
    cr_assert_eq(result, true);

    // Test setting to FALSE
    result = shell.setComponentValue("input1=0", circuit);
    cr_assert_eq(result, true);

    // Test setting to UNDEFINED
    result = shell.setComponentValue("input1=U", circuit);
    cr_assert_eq(result, true);
}

Test(ShellLoop, setComponentValue_invalid_input, .init = redirect_all_stdout)
{
    MockCircuit circuit;
    TestableShellLoop shell(circuit);

    // Test with non-existent component
    bool result = shell.setComponentValue("nonexistent=1", circuit);
    cr_assert_eq(result, false);

    // Test with invalid format
    result = shell.setComponentValue("invalidformat", circuit);
    cr_assert_eq(result, false);
}

Test(ShellLoop, setComponentValue_regex_matching, .init = redirect_all_stdout)
{
    MockCircuit circuit;
    TestableShellLoop shell(circuit);

    auto inputComponent = circuit.createMockInput("test_input");

    // Test that the regex properly extracts component name
    bool result = shell.setComponentValue("test_input=1", circuit);
    cr_assert_eq(result, true);

    // Test with numbers in name
    auto anotherInput = circuit.createMockInput("input123");
    result = shell.setComponentValue("input123=0", circuit);
    cr_assert_eq(result, true);
}

Test(ShellLoop, setanonInputComp, .init =redirect_all_stdout)
{
    MockCircuit circuit;
    TestableShellLoop shell(circuit);

    auto inputComponent = circuit.createMockInput("input1");

    // Test setting to TRUE
    bool result = shell.setComponentValue("input1=1", circuit);
    cr_assert_eq(result, true);

    // Test setting to FALSE
    result = shell.setComponentValue("input1=0", circuit);
    cr_assert_eq(result, true);

    // Test setting to UNDEFINED
    result = shell.setComponentValue("input1=U", circuit);
    cr_assert_eq(result, true);
}