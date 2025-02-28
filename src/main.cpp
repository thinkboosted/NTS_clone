/*
** EPITECH PROJECT, 2025
** nanoTekSpice
** File description:
** Main
*/

#include <iostream>
#include <sstream>
#include <regex>
#include "../include/Parser.hpp"
#include "../include/NanoTekSpiceException.hpp"

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

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <circuit_file>" << std::endl;
        return 84;
    }

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
    }
    catch (const NanoTekSpiceException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}