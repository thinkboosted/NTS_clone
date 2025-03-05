/*
** EPITECH PROJECT, 2025
** nts
** File description:
** Parser
*/

#include "../include/Parser.hpp"
#include "../include/NanoTekSpiceException.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>

Parser::Parser(const std::string& filename)
    : m_filename(filename)
{
}

Parser::~Parser()
{
}

std::vector<std::string> Parser::parse() const
{
    std::vector<std::string> lines;
    std::ifstream file(m_filename);
    std::string line;

    if (!file) {
        throw std::runtime_error("File not found");
    }
    while (std::getline(file, line)) {
        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            line.erase(commentPos);
        }
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    file.close();
    validateCircuit(lines);
    return lines;
}

void Parser::checkSyntax(const std::string& line) const
{
    std::regex chipsetRegex("^\\s*([a-zA-Z0-9]+)\\s+([a-zA-Z0-9_]+)(?:\\(([^)]+)\\))?\\s*$");
    std::regex linkRegex("^\\s*([a-zA-Z0-9_]+):([0-9]+)\\s+([a-zA-Z0-9_]+):([0-9]+)\\s*$");
    std::regex sectionRegex("^\\s*\\.([a-zA-Z]+):\\s*$");

    if (!std::regex_match(line, chipsetRegex) &&
        !std::regex_match(line, linkRegex) &&
        !std::regex_match(line, sectionRegex)) {
        throw SyntaxError(line);
    }
}

void Parser::checkComponentType(const std::string& type) const
{
    const std::vector<std::string> validTypes = {
        "2716", "4001", "4008", "4011", "4013", "4017",
        "4030", "4040", "4069", "4071", "4081", "4094", "4512", "4514", "4801",
        "input", "output", "true", "false", "clock", "and", "or", "xor", "not"
    };

    if (std::find(validTypes.begin(), validTypes.end(), type) == validTypes.end())
        throw UnknownComponentError(type);
}

std::map<std::string, std::string> Parser::extractComponents(const std::vector<std::string>& lines) const
{
    std::map<std::string, std::string> components;
    bool inChipsetSection = false;

    for (const auto& line : lines) {
        if (line == ".chipsets:") {
            inChipsetSection = true;
            continue;
        }
        if (line == ".links:") {
            inChipsetSection = false;
            continue;
        }
        if (inChipsetSection) {
            std::istringstream iss(line);
            std::string type, name;
            iss >> type >> name;
            if (components.find(name) != components.end())
                throw DuplicateComponentError(name);
            checkComponentType(type);
            components[name] = type;
        }
    }
    return components;
}

void Parser::validateChipsetSection(const std::vector<std::string>& lines) const
{
    bool hasChipsetSection = false;
    bool hasChipsets = false;

    for (const auto& line : lines) {
        if (line == ".chipsets:") {
            hasChipsetSection = true;
            continue;
        }
        if (hasChipsetSection && line != ".links:") {
            hasChipsets = true;
            break;
        }
        if (line == ".links:") {
            break;
        }
    }
    if (!hasChipsetSection || !hasChipsets)
        throw NoChipsetError();
}

void Parser::validateLinksSection(const std::vector<std::string>& lines) const
{
    auto components = extractComponents(lines);
    bool inLinkSection = false;

    for (const auto& line : lines) {
        if (line == ".links:") {
            inLinkSection = true;
            continue;
        }
        if (inLinkSection) {
            std::regex linkRegex("^\\s*([a-zA-Z0-9]+):([0-9]+)\\s+([a-zA-Z0-9]+):([0-9]+)\\s*$");
            std::smatch matches;

            if (std::regex_match(line, matches, linkRegex)) {
                std::string comp1 = matches[1];
                std::string comp2 = matches[3];
                int pin1 = std::stoi(matches[2]);
                int pin2 = std::stoi(matches[4]);
                if (components.find(comp1) == components.end()) {
                    throw UnknownComponentError(comp1);
                }
                if (components.find(comp2) == components.end()) {
                    throw UnknownComponentError(comp2);
                }
                // Next : check if the pins are valid
                if (pin1 <= 0 || pin2 <= 0)
                    throw InvalidPinError(comp1, pin1);
            }
        }
    }
}

void Parser::validateCircuit(const std::vector<std::string>& lines) const
{
    for (const auto& line : lines) {
        checkSyntax(line);
    }
    validateChipsetSection(lines);
    validateLinksSection(lines);
}