/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Main
*/

#include <iostream>
#include <sstream>
#include <regex>
#include <memory>
#include "../include/Parser.hpp"
#include "../include/NanoTekSpiceException.hpp"
#include "../include/Factory.hpp"
#include "../include/Circuit.hpp"
#include "../include/ShellLoop.hpp"

void displayComponents(const std::vector<std::string>& lines) {
    std::cout << "\n=== COMPONENTS ===\n";
    bool inChipsetSection = false;

    for (const auto& line : lines) {
        if (line == ".chipsets:") {
            inChipsetSection = true;
            continue;
        }
        if (line == ".links:") {
            inChipsetSection = false;
            break;
        }

        if (inChipsetSection) {
            std::istringstream iss(line);
            std::string type, name;
            iss >> type >> name;
            std::cout << "Type: " << type << ", Name: " << name << std::endl;
        }
    }
}

void displayLinks(const std::vector<std::string>& lines) {
    std::cout << "\n=== LINKS ===\n";
    bool inLinkSection = false;
    std::regex linkRegex("^\\s*([a-zA-Z0-9_]+):([0-9]+)\\s+([a-zA-Z0-9_]+):([0-9]+)\\s*$");

    for (const auto& line : lines) {
        if (line == ".links:") {
            inLinkSection = true;
            continue;
        }

        if (inLinkSection) {
            std::smatch matches;
            if (std::regex_match(line, matches, linkRegex)) {
                std::cout << "Connection: "
                        << matches[1] << ":" << matches[2] << " -> "
                        << matches[3] << ":" << matches[4] << std::endl;
            }
        }
    }
}

static int start(int ac, char **argv)
{
	nts::Circuit circuit;
	int	ret = 0;

	(void)ac;
	try {
		Parser myParser(argv[1]);
        std::vector<std::string> content = myParser.parse();

        std::cout << "Circuit successfully parsed!" << std::endl;
        std::cout << "Lines in file: " << content.size() << std::endl;

        std::cout << "\n=== RAW CONTENT ===\n";
        for (size_t i = 0; i < content.size(); i++) {
            std::cout << "[" << i << "] " << content[i] << std::endl;
        }
        displayComponents(content);
        displayLinks(content);
        for (const auto& line : content) {
            if (line == ".chipsets:") {
                continue;
            }
            if (line == ".links:") {
                break;
            }
            std::istringstream iss(line);
            std::string type, name;
            iss >> type >> name;
            circuit.addComponent(type, name);
        }
        for (const auto& line : content) {
            if (line == ".links:") {
                continue;
            }
            std::regex linkRegex("^\\s*([a-zA-Z0-9_]+):([0-9]+)\\s+([a-zA-Z0-9_]+):([0-9]+)\\s*$");
            std::smatch matches;
            if (std::regex_match(line, matches, linkRegex)) {
                std::string comp1 = matches[1];
                std::string comp2 = matches[3];
                int pin1 = std::stoi(matches[2]);
                int pin2 = std::stoi(matches[4]);
                circuit.linkComponents(comp1, comp2, pin1, pin2);
            }
        }
		nts::ShellLoop shell(circuit);
		shell.run();
    }
    catch (const NanoTekSpiceException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
	return ret;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <circuit_file>" << std::endl;
        return 84;
    } else {
		return start(argc, argv);
	}
}
