#include <iostream>
#include <string>
#include <windows.h>

typedef void* (*fn_create_caesar)(int);
typedef void* (*fn_create_vigenere)(const char*);
typedef void* (*fn_create_a1z26)();
typedef char* (*fn_process)(void*, const char*);
typedef void  (*fn_destroy)(void*);
typedef void  (*fn_free)(char*);

int main() {
    HMODULE hLib = LoadLibrary(TEXT("CipherLib.dll"));
    if (hLib == nullptr) {
        std::cout << "Error, there is no CipherLib.dll!" << std::endl;
        return 1;
    }


    auto create_caesar = (fn_create_caesar)GetProcAddress(hLib, "cipher_create_caesar");
    auto create_vigenere = (fn_create_vigenere)GetProcAddress(hLib, "cipher_create_vigenere");
    auto create_a1z26 = (fn_create_a1z26)GetProcAddress(hLib, "cipher_create_a1z26");

    auto encrypt_text = (fn_process)GetProcAddress(hLib, "cipher_encrypt");
    auto decrypt_text = (fn_process)GetProcAddress(hLib, "cipher_decrypt");

    auto destroy_cipher = (fn_destroy)GetProcAddress(hLib, "cipher_destroy");
    auto free_string = (fn_free)GetProcAddress(hLib, "cipher_free");


    std::cout << "Choose cipher:\n1: Caesar\n2: Vigenere\n3: A1Z26\nChoice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    void* my_cipher = nullptr;


    if (choice == 1) {
        int key;
        std::cout << "Enter integer key: ";
        std::cin >> key;
        std::cin.ignore();
        my_cipher = create_caesar(key);
    }
    else if (choice == 2) {
        std::string key;
        std::cout << "Enter text key: ";
        std::getline(std::cin, key);
        my_cipher = create_vigenere(key.c_str());
    }
    else if (choice == 3) {
        my_cipher = create_a1z26();
    }
    else {
        std::cout << "there is no such command!." << std::endl;
        FreeLibrary(hLib);
        return 1;
    }


    std::string text;
    std::cout << "Enter text: ";
    std::getline(std::cin, text);


    char* encrypted = encrypt_text(my_cipher, text.c_str());
    std::cout << "\nEncrypted: " << encrypted << std::endl;


    char* decrypted = decrypt_text(my_cipher, encrypted);
    std::cout << "Decrypted: " << decrypted << std::endl;


    free_string(encrypted);
    free_string(decrypted);
    destroy_cipher(my_cipher);

    FreeLibrary(hLib);

    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}