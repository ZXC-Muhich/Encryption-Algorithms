#include "Cipher.h"
#include <cctype>
#include <string>


CaesarCipher::CaesarCipher(int key) : key_(key) {}

std::string CaesarCipher::encrypt(const std::string& text) {
    std::string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';

            int shift = (c - base + key_) % 26;
            if (shift < 0) {
                shift += 26;
            }

            result += (char)(base + shift);
        }
        else {
            result += c;
        }
    }
    return result;
}

std::string CaesarCipher::decrypt(const std::string& text) {
    CaesarCipher reverseCipher(-key_);
    return reverseCipher.encrypt(text);
}



VigenereCipher::VigenereCipher(const std::string& key) : key_(key) {}

std::string VigenereCipher::encrypt(const std::string& text) {
    std::string result = "";
    int keyIndex = 0;
    int keyLength = key_.length();

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            char keyChar = toupper(key_[keyIndex % keyLength]);

            int shiftAmount = keyChar - 'A';
            int shift = (c - base + shiftAmount) % 26;

            if (shift < 0) {
                shift += 26;
            }

            result += (char)(base + shift);
            keyIndex++;
        }
        else {
            result += c;
        }
    }
    return result;
}

std::string VigenereCipher::decrypt(const std::string& text) {
    std::string result = "";
    int keyIndex = 0;
    int keyLength = key_.length();

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            char keyChar = toupper(key_[keyIndex % keyLength]);

            int shiftAmount = keyChar - 'A';
            int shift = (c - base - shiftAmount) % 26;

            if (shift < 0) {
                shift += 26;
            }

            result += (char)(base + shift);
            keyIndex++;
        }
        else {
            result += c;
        }
    }
    return result;
}



std::string A1Z26Cipher::encrypt(const std::string& text) {
    std::string result = "";

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];

        if (isalpha(c)) {
            int letterNumber = (tolower(c) - 'a') + 1;
            result += std::to_string(letterNumber);

            if (i + 1 < text.length() && isalpha(text[i + 1])) {
                result += "-";
            }
        }
        else {
            result += c;
        }
    }
    return result;
}

std::string A1Z26Cipher::decrypt(const std::string& text) {
    std::string result = "";
    std::string num = "";

    for (char c : text) {
        if (isdigit(c)) {
            num += c;
        }
        else {
            if (!num.empty()) {
                int numberValue = std::stoi(num);
                result += (char)('a' - 1 + numberValue);
                num.clear();
            }

            if (c != '-') {
                result += c;
            }
        }
    }

    if (!num.empty()) {
        int numberValue = std::stoi(num);
        result += (char)('a' - 1 + numberValue);
    }

    return result;
}