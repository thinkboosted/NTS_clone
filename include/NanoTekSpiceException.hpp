/*
** EPITECH PROJECT, 2025
** NTS_clone
** File description:
** NanoTekSpiceException
*/

#pragma once

#include <exception>
#include <string>

class NanoTekSpiceException : public std::exception {
protected:
    std::string message;

public:
    // explicit keyword is used to avoid implicit conversions, good practice
    explicit NanoTekSpiceException(const std::string &msg) : message(msg) {}
    virtual ~NanoTekSpiceException() = default;
    const char* what() const noexcept override { return message.c_str(); }
};

class SyntaxError : public NanoTekSpiceException {
public:
    explicit SyntaxError(const std::string &line)
        : NanoTekSpiceException("Syntax error in line: " + line) {}
};

class UnknownComponentError : public NanoTekSpiceException {
public:
    explicit UnknownComponentError(const std::string &name)
        : NanoTekSpiceException("Unknown component: " + name) {}
};

class DuplicateComponentError : public NanoTekSpiceException {
public:
    explicit DuplicateComponentError(const std::string &name)
        : NanoTekSpiceException("Duplicate component name: " + name) {}
};

class InvalidPinError : public NanoTekSpiceException {
public:
    InvalidPinError(const std::string &comp, int pin)
        : NanoTekSpiceException("Invalid pin " + std::to_string(pin) + " for " + comp) {}
};

class NoChipsetError : public NanoTekSpiceException {
public:
    NoChipsetError() : NanoTekSpiceException("No chipsets defined in circuit") {}
};
