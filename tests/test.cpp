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

// Utilitaire pour créer un fichier de test temporaire
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
    // Pas d'exception = test passé
}

// Test d'un fichier valide
Test(Parser, valid_file_parse)
{
    createTestFile("valid.nts",
        ".chipsets:\n"
        "input a\n"
        "output b\n"
        ".links:\n"
        "a:1 b:1\n"
    );

    Parser parser("valid.nts");
    std::vector<std::string> lines;

    lines = parser.parse();

    // Vérifie que le contenu est correct (sans les commentaires et lignes vides)
    cr_assert_eq(lines.size(), 5, "Should have 5 lines after parsing");
    cr_assert_eq(lines[0], ".chipsets:", "First line should be .chipsets:");

    std::remove("valid.nts");
}

// Test d'un fichier inexistant
Test(Parser, nonexistent_file)
{
    Parser parser("nonexistent_file.nts");

    // Vérifie que parse() lance une exception pour un fichier inexistant
    cr_assert_throw(parser.parse(), std::runtime_error, "Should throw for nonexistent file");
}

// Test de validation de type de composant
Test(Parser, invalid_component_type)
{
    createTestFile("invalid_component.nts",
        ".chipsets:\n"
        "invalid_type a\n"
        "output b\n"
        ".links:\n"
        "a:1 b:1\n"
    );

    Parser parser("invalid_component.nts");

    // Vérifie que parse() lance une exception pour un type de composant invalide
    cr_assert_throw(parser.parse(), SyntaxError, "Should throw for invalid component type");

    std::remove("invalid_component.nts");
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

    // Vérifie que parse() lance une exception pour un composant dupliqué
    cr_assert_throw(parser.parse(), DuplicateComponentError, "Should throw for duplicate component");

    std::remove("duplicate.nts");
}

// Test pour une syntaxe invalide
Test(Parser, invalid_syntax)
{
    createTestFile("invalid_syntax.nts",
        ".chipsets:\n"
        "input a\n"
        "output b\n"
        ".links:\n"
        "a-1 b-1\n"  // Syntaxe de lien incorrecte
    );

    Parser parser("invalid_syntax.nts");

    // Vérifie que parse() lance une exception pour une syntaxe invalide
    cr_assert_throw(parser.parse(), SyntaxError, "Should throw for invalid syntax");

    std::remove("invalid_syntax.nts");
}

// Test pour une section chipset manquante
Test(Parser, missing_chipset_section)
{
    createTestFile("missing_chipset.nts",
        ".links:\n"
        "a:1 b:1\n"
    );

    Parser parser("missing_chipset.nts");

    // Vérifie que parse() lance une exception pour une section chipset manquante
    cr_assert_throw(parser.parse(), NoChipsetError, "Should throw for missing chipset section");

    std::remove("missing_chipset.nts");
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

    // Vérifie que parse() lance une exception pour un composant non défini
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

    // Vérifie que parse() lance une exception pour un pin invalide
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

    // Vérifie que parse() traite correctement les commentaires et espaces
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

    // Vérifie que parse() lance une exception pour une section chipset vide
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

    // Devrait fonctionner sans section links
    lines = parser.parse();
    cr_assert_eq(lines.size(), 3, "Should have 3 non-empty lines");

    std::remove("missing_links.nts");
}

// Test de la section chipset vide (autre forme)
Test(Parser, chipset_section_without_components)
{
    createTestFile("empty_chipset_alt.nts",
        ".chipsets:\n"
        "\n"
        ".links:\n"
        "\n"
    );

    Parser parser("empty_chipset_alt.nts");

    // Devrait échouer car aucun composant
    cr_assert_throw(parser.parse(), NoChipsetError, "Should throw for chipset section without components");

    std::remove("empty_chipset_alt.nts");
}

// Test avec un autre format de section
Test(Parser, different_section_format)
{
    createTestFile("different_section.nts",
        ".chipsets:\n"
        "input a\n"
        ".links:    \n"  // Espaces après le :
        "a:1 b:1\n"
    );

    Parser parser("different_section.nts");

    // Doit analyser correctement malgré les espaces
    cr_assert_throw(parser.parse(), UnknownComponentError, "Should process sections with trailing spaces");

    std::remove("different_section.nts");
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

    // Doit analyser correctement tous les types de composants
    lines = parser.parse();
    cr_assert_eq(lines.size(), 10, "Should parse all component types");

    std::remove("various_components.nts");
}

// Test pour vérifier la gestion de fichiers vides
Test(Parser, empty_file)
{
    createTestFile("empty.nts", "");

    Parser parser("empty.nts");

    // Devrait échouer car fichier vide = pas de section chipset
    cr_assert_throw(parser.parse(), NoChipsetError, "Should throw for empty file");

    std::remove("empty.nts");
}

// Test pour vérifier les pins élevés
Test(Parser, high_pin_number)
{
    createTestFile("high_pin.nts",
        ".chipsets:\n"
        "input a\n"
        "output b\n"
        ".links:\n"
        "a:999 b:999\n"  // Pins élevés
    );

    Parser parser("high_pin.nts");
    std::vector<std::string> lines;

    // Doit accepter des numéros de pin élevés
    lines = parser.parse();
    cr_assert_eq(lines.size(), 5, "Should accept high pin numbers");

    std::remove("high_pin.nts");
}

// Test pour cibler la ligne 71 (checkComponentType) en utilisant un composant presque valide
Test(Parser, edge_case_component_type)
{
    createTestFile("edge_case_type.nts",
        ".chipsets:\n"
        "inpu a\n"  // Presque "input" mais invalide
        "output b\n"
        ".links:\n"
        "a:1 b:1\n"
    );

    Parser parser("edge_case_type.nts");

    // Devrait lever une exception car "inpu" n'est pas un type valide
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

    // L'ordre des sections devrait être géré correctement
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

    // Devrait rejeter cette syntaxe de lien
    cr_assert_throw(parser.parse(), SyntaxError, "Parser should reject links without spaces");

    std::remove("link_variants.nts");
}

// Test pour les pins non-numériques
Test(Parser, non_numeric_pins)
{
    createTestFile("non_numeric_pins.nts",
        ".chipsets:\n"
        "input a\n"
        "output b\n"
        ".links:\n"
        "a:x b:1\n"  // Pin non-numérique
    );

    Parser parser("non_numeric_pins.nts");

    // Devrait rejeter les pins non-numériques
    cr_assert_throw(parser.parse(), SyntaxError, "Parser should reject non-numeric pins");

    std::remove("non_numeric_pins.nts");
}

// Test pour sections incomplètes/malformées
Test(Parser, malformed_sections)
{
    createTestFile("malformed_sections.nts",
        ".chipsets\n"  // Manque le :
        "input a\n"
        ".links:\n"
        "a:1 b:1\n"
    );

    Parser parser("malformed_sections.nts");

    // Devrait rejeter les sections malformées
    cr_assert_throw(parser.parse(), SyntaxError, "Parser should reject malformed section headers");

    std::remove("malformed_sections.nts");
}

// Test pour plusieurs sections identiques
Test(Parser, duplicate_sections)
{
    createTestFile("duplicate_sections.nts",
        ".chipsets:\n"
        "input a\n"
        ".chipsets:\n"  // Section en double
        "output b\n"
        ".links:\n"
        "a:1 b:1\n"
    );

    Parser parser("duplicate_sections.nts");

    // Le comportement attendu dépend de l'implémentation
    cr_assert_throw(parser.parse(), SyntaxError, "Parser should handle duplicate sections");

    std::remove("duplicate_sections.nts");
}

// Test pour composant multi-ligne
Test(Parser, multi_line_component)
{
    createTestFile("multi_line.nts",
        ".chipsets:\n"
        "input\n"  // Type et nom sur des lignes différentes
        "a\n"
        ".links:\n"
        "a:1 b:1\n"
    );

    Parser parser("multi_line.nts");

    // Devrait rejeter cette syntaxe
    cr_assert_throw(parser.parse(), SyntaxError, "Parser should reject multi-line component definitions");

    std::remove("multi_line.nts");
}