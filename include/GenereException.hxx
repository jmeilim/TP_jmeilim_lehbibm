#pragma once
#include <stdexcept>
#include <string>

class GenereException : public std::runtime_error {
public:
    explicit GenereException(const std::string& msg)
        : std::runtime_error("[Erreur] " + msg) {}
};