#include "cipher_api.h"
#include "Cipher.h"
#include <cstring>

extern "C" {

    EXPORT cipher_t* cipher_create_caesar(int key) {
        return new CaesarCipher(key);
    }

    EXPORT cipher_t* cipher_create_vigenere(const char* key) {
        return new VigenereCipher(std::string(key));
    }

    EXPORT cipher_t* cipher_create_a1z26() {
        return new A1Z26Cipher();
    }


    char* allocate_c_string(const std::string& str) {
        char* cstr = new char[str.length() + 1];
        std::strcpy(cstr, str.c_str());
        return cstr;
    }


    EXPORT char* cipher_encrypt(cipher_t* cipher, const char* text) {
        return allocate_c_string(static_cast<Cipher*>(cipher)->encrypt(text));
    }

    EXPORT char* cipher_decrypt(cipher_t* cipher, const char* text) {
        return allocate_c_string(static_cast<Cipher*>(cipher)->decrypt(text));
    }

    EXPORT void cipher_destroy(cipher_t* cipher) {
        delete static_cast<Cipher*>(cipher);
    }

    EXPORT void cipher_free(char* str) {
        delete[] str;
    }

}