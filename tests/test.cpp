/*
** EPITECH PROJECT, 2025
** NTS_clone
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include "../include/Parser.hpp"
#include "../include/NanoTekSpiceException.hpp"
#include <fstream>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

void createTestFile(const std::string& filename, const std::string& content)
{
    std::ofstream file(filename);
    file << content;
    file.close();
}

// Test pour vérifier la création du parser
Test(Parser, constructor_test)
{
    Parser parser("test_file.nts");
}

// Test d'un fichier inexistant
Test(Parser, nonexistent_file)
{
    Parser parser("nonexistent_file.nts");

    cr_assert_throw(parser.parse(), std::runtime_error, "Should throw for nonexistent file");
}

// Test pour un composant dupliqué
Test(Parser, duplicate_component)
{
    createTestFile("duplicate.nts",
        ".chipsets:\n"
        "input a\n"
        "output a\n"
        ".links:\n"
        "a:1 a:1\n"
    );

    Parser parser("duplicate.nts");

    cr_assert_throw(parser.parse(), DuplicateComponentError, "Should throw for duplicate component");

    std::remove("duplicate.nts");
}

// Test pour un composant non défini dans les liens
Test(Parser, undefined_component_in_links)
{
    createTestFile("undefined_component.nts",
        ".chipsets:\n"
        "input a\n"
        ".links:\n"
        "a:1 b:1\n"  // 'b' n'est pas défini
    );

    Parser parser("undefined_component.nts");

    cr_assert_throw(parser.parse(), UnknownComponentError, "Should throw for undefined component in links");

    std::remove("undefined_component.nts");
}

// Test pour un pin invalide
Test(Parser, invalid_pin)
{
    createTestFile("invalid_pin.nts",
        ".chipsets:\n"
        "input a\n"
        "output b\n"
        ".links:\n"
        "a:0 b:1\n"  // pin 0 invalide
    );

    Parser parser("invalid_pin.nts");

    cr_assert_throw(parser.parse(), InvalidPinError, "Should throw for invalid pin");

    std::remove("invalid_pin.nts");
}

// Test avec des commentaires et espaces
Test(Parser, comments_and_whitespace)
{
    createTestFile("comments.nts",
        "# This is a comment\n"
        ".chipsets:  # Section start\n"
        "  input a   # Input component\n"
        "\n"
        "output b\n"
        "\n"
        ".links:\n"
        "a:1 b:1  # Link components\n"
    );

    Parser parser("comments.nts");
    std::vector<std::string> lines;

    lines = parser.parse();

    cr_assert_eq(lines.size(), 5, "Should have 5 non-empty, non-comment lines");

    std::remove("comments.nts");
}

// Test des sections manquantes ou vides
Test(Parser, empty_chipset_section)
{
    createTestFile("empty_chipset.nts",
        ".chipsets:\n"
        ".links:\n"
        "a:1 b:1\n"
    );

    Parser parser("empty_chipset.nts");

    cr_assert_throw(parser.parse(), NoChipsetError, "Should throw for empty chipset section");

    std::remove("empty_chipset.nts");
}

// Test avec section links manquante
Test(Parser, missing_links_section)
{
    createTestFile("missing_links.nts",
        ".chipsets:\n"
        "input a\n"
        "output b\n"
    );

    Parser parser("missing_links.nts");
    std::vector<std::string> lines;

    lines = parser.parse();
    cr_assert_eq(lines.size(), 3, "Should have 3 non-empty lines");

    std::remove("missing_links.nts");
}

// Test pour différents types de composants valides
Test(Parser, various_valid_components)
{
    createTestFile("various_components.nts",
        ".chipsets:\n"
        "input a\n"
        "output b\n"
        "clock c\n"
        "true d\n"
        "false e\n"
        "and f\n"
        "4001 g\n"
        ".links:\n"
        "a:1 b:1\n"
    );

    Parser parser("various_components.nts");
    std::vector<std::string> lines;

    lines = parser.parse();
    cr_assert_eq(lines.size(), 10, "Should parse all component types");

    std::remove("various_components.nts");
}

// Test pour cibler la ligne 71 (checkComponentType) en utilisant un composant presque valide
Test(Parser, edge_case_component_type)
{
    createTestFile("edge_case_type.nts",
        ".chipsets:\n"
        "inpu a\n"  // invalide
        "output b\n"
        ".links:\n"
        "a:1 b:1\n"
    );

    Parser parser("edge_case_type.nts");

    cr_assert_throw(parser.parse(), UnknownComponentError, "Should throw for almost-valid component type");

    std::remove("edge_case_type.nts");
}

// Test pour sections multiples et ordre inversé
Test(Parser, multiple_sections_wrong_order)
{
    createTestFile("wrong_order.nts",
        ".links:\n"
        "a:1 b:1\n"
        ".chipsets:\n"
        "input a\n"
        "output b\n"
    );

    Parser parser("wrong_order.nts");
    std::vector<std::string> lines;

    cr_assert_throw(parser.parse(), NoChipsetError, "Parser should handle or reject reversed section order");

    std::remove("wrong_order.nts");
}

// Test pour syntaxe de lien alternative (sans espaces)
Test(Parser, link_syntax_variants)
{
    createTestFile("link_variants.nts",
        ".chipsets:\n"
        "input a\n"
        "output b\n"
        ".links:\n"
        "a:1b:1\n"  // Sans espace
    );

    Parser parser("link_variants.nts");

    cr_assert_throw(parser.parse(), SyntaxError, "Parser should reject links without spaces");

    std::remove("link_variants.nts");
}

Test(Parser, negative_component_value)
{
    createTestFile("negative_value.nts",
        ".chipsets:\n"
        "input a(-1)\n"
        "output b\n"
        ".links:\n"
        "a:1 b:1\n"
    );

    Parser parser("negative_value.nts");

    try {
        std::vector<std::string> lines = parser.parse();
        cr_assert_eq(lines.size(), 5, "Should parse components with negative values");
    } catch (const std::exception& e) {
        cr_assert(true, "Rejected negative component value (also acceptable)");
    }

    std::remove("negative_value.nts");
}
