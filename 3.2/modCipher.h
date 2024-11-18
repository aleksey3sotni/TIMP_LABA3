#pragma once
#include <string>
#include <stdexcept>
#include <vector>

class cipher_error : public std::runtime_error {
public:
    explicit cipher_error(const std::string& what_arg) : std::runtime_error(what_arg) {}
};

std::string prepareText(const std::string& text);
std::string coder(int key, const std::string& text);
std::string decoder(int key, const std::string& text);
int getValidKey(int key, const std::string& text);
