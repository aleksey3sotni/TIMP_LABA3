#pragma once
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};

class Code {
private:
    int key;

    int getValidKey(int key, const std::string& text) {
        return key; 
    }

    std::string getValidOpenText(const std::string& s) {
        return s; 
    }
    
    std::string getValidCipherText(const std::string& s, const std::string& open_text) {     
        return s;
    }
    
public:
    Code() = delete;

    Code(int skey, const std::string& text) : key(getValidKey(skey, text)) {
    }

    std::string encryption(const std::string& text) {
        return text; 
    }

    std::string decrypt(const std::string& text, const std::string& open_text) {
        return text; 
    }
};
