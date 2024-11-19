#include "modCipher.h"
#include <algorithm>
#include <cctype>

std::string prepareText(const std::string& text) {
    std::string prepared;
    for (char c : text) {
        if (isalpha(c)) {
            prepared += toupper(c);
        } else if (!isspace(c)) { 
            throw cipher_error("Текст должен содержать только алфавитные символы и пробелы");
        }
    }
    if (prepared.empty()) {
        throw cipher_error("Текст должен содержать хотя бы один алфавитный символ");
    }
    return prepared;
}

int getValidKey(int key, const std::string& text) {
    if ((size_t)key <= 0 || (size_t)key > text.length() / 2) {
        throw cipher_error("Неверный ключ");
    }
    return key;
}

std::string coder(int key, const std::string& text) {
    std::string preparedText = prepareText(text);
    size_t len = preparedText.length();
    size_t rows = (len + (size_t)key - 1) / (size_t)key;
    std::vector<std::vector<char>> matrix(rows, std::vector<char>((size_t)key, '\0'));

    size_t index = 0;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < (size_t)key; ++j) {
            if (index < len) {
                matrix[i][j] = preparedText[index++];
            }
        }
    }

    std::string coded;
    for (size_t j = 0; j < (size_t)key; ++j) {
        for (size_t i = 0; i < rows; ++i) {
            if (matrix[i][j] != '\0') {
                coded += matrix[i][j];
            }
        }
    }
    return coded;
}

std::string decoder(int key, const std::string& text) {
    std::string preparedText = prepareText(text); 
    size_t len = preparedText.length();
    size_t rows = (len + (size_t)key - 1) / (size_t)key;
    std::vector<std::vector<char>> matrix(rows, std::vector<char>((size_t)key, '\0'));

    size_t index = 0;
    for (size_t j = 0; j < (size_t)key; ++j) {
        for (size_t i = 0; i < rows; ++i) {
            if (index < len) {
                matrix[i][j] = preparedText[index++];
            }
        }
    }

    std::string decoded;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < (size_t)key; ++j) {
            if (matrix[i][j] != '\0') {
                decoded += matrix[i][j];
            }
        }
    }
    return decoded;
}
