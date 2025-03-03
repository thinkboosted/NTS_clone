/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Main
*/

#include <iostream>
#include <memory>
#include "../include/Factory.hpp"
#include "../include/Circuit.hpp"
#include "../include/ShellLoop.hpp"

void parse_smth()
{
	nts::Factory factory;
    nts::Circuit circuit;
    circuit.addComponent("clock", "c");
    circuit.addComponent("output", "s");
}

static int start(int ac, char **argv)
{
	// Parser parser;
	nts::Circuit circuit;
	int	ret = 0;

	try {
		// parser.parse(argv[1], circuit);
		// parser.parse_args(ac, argv, circuit);
		nts::ShellLoop shell(circuit);
		shell.run();
        parse_smth();
	}
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        ret = 84;
    }
	return ret;
}

int main(int ac, char **argv)
{
	if (ac < 2)
		return 84;
	else
		return start(ac, argv);
}
