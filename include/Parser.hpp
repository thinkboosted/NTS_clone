/*
** EPITECH PROJECT, 2025
** nts
** File description:
** Parser
*/

#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "NanoTekSpiceException.hpp"

class Parser {
    public:
        Parser(const std::string& filename);
        ~Parser();

        std::vector<std::string> parse() const;
        void validateCircuit(const std::vector<std::string>& lines) const;

    private:
        std::string m_filename;
        void checkSyntax(const std::string& line) const;
        void checkComponentType(const std::string& type) const;
        void validateChipsetSection(const std::vector<std::string>& lines) const;
        void validateLinksSection(const std::vector<std::string>& lines) const;
        std::map<std::string, std::string> extractComponents(const std::vector<std::string>& lines) const;
};
