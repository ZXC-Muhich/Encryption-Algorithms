#pragma once
#include <string>
#include <windows.h>

class CipherHandler {
    typedef void* (*fn_create_vigenere)(const char*);
    typedef char* (*fn_process)(void*, const char*);
    typedef void  (*fn_destroy)(void*);
    typedef void  (*fn_free)(char*);

public:
    static std::string encryptData(const std::string& data, const std::string& key) {
        return processData(data, key, "cipher_encrypt");
    }

    static std::string decryptData(const std::string& data, const std::string& key) {
        return processData(data, key, "cipher_decrypt");
    }

private:
    static std::string processData(const std::string& data, const std::string& key, const char* operationName) {
        HMODULE hLib = LoadLibraryA("CipherLib.dll");
        if (!hLib) return "";

        auto create_vig = (fn_create_vigenere)GetProcAddress(hLib, "cipher_create_vigenere");
        auto process = (fn_process)GetProcAddress(hLib, operationName);
        auto destroy = (fn_destroy)GetProcAddress(hLib, "cipher_destroy");
        auto free_str = (fn_free)GetProcAddress(hLib, "cipher_free");

        if (!create_vig || !process || !destroy || !free_str) {
            FreeLibrary(hLib);
            return "";
        }

        void* cipher = create_vig(key.c_str());
        char* processedChars = process(cipher, data.c_str());

        std::string result(processedChars);

        free_str(processedChars);
        destroy(cipher);

        FreeLibrary(hLib);

        return result;
    }
};