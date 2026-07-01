#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Lines.h"
#include "TextDocument.h"
#include "CipherHandler.h"

int main() {
    TextDocument textDoc;

    std::cout << " 1) Append text line\n 2) Add contact \n 3) Add checklist\n 4) Save file\n 5) Load file\n 6) Encrypt\n 7) Decrypt\n 8) Print text\n 9) Exit\n";

    while (true) {
        int command = 0;
        std::cout << "\nChoose the command: ";
        std::cin >> command;

        std::cin.ignore(10000, '\n');

        if (command == 1) {
            std::string input;
            std::cout << "Enter text to append: ";
            std::getline(std::cin, input);
            textDoc.addLine(new TextLine(input));
            std::cout << "Text line added\n";
        }
        else if (command == 2) {
            std::string n, s, e;
            std::cout << "Enter Name: "; std::getline(std::cin, n);
            std::cout << "Enter Surname: "; std::getline(std::cin, s);
            std::cout << "Enter Email: "; std::getline(std::cin, e);

            textDoc.addLine(new ContactLine(n, s, e));
            std::cout << "Contact added\n";
        }
        else if (command == 3) {
            std::string item;
            int checked = 0;
            std::cout << "Enter checklist item: "; std::getline(std::cin, item);
            std::cout << "Is it checked? (1 - YES, 0 - NO): ";
            std::cin >> checked;
            std::cin.ignore(10000, '\n');

            textDoc.addLine(new ChecklistLine(item, checked == 1));
            std::cout << "Checklist added\n";
        }
        else if (command == 4) {
            std::string path;
            std::cout << "Enter output file path: ";
            std::getline(std::cin, path);

            std::ofstream file(path);
            if (file.is_open()) {
                file << textDoc.serializeAll();
                file.close();
                std::cout << "Text saved successfully\n";
            }
            else {
                std::cout << "Error opening file for writing\n";
            }
        }
        else if (command == 5) {
            std::string path;
            std::cout << "Enter input file path: ";
            std::getline(std::cin, path);

            std::ifstream file(path);
            if (!file.is_open()) {
                std::cout << "Error opening file for reading\n";
            }
            else {
                std::stringstream buffer;
                buffer << file.rdbuf();
                textDoc.deserializeAll(buffer.str());
                file.close();
                std::cout << "Text loaded successfully\n";
            }
        }
        else if (command == 6) {
            std::string inPath, outPath, key;
            std::cout << "Enter INPUT file path: ";
            std::getline(std::cin, inPath);
            std::cout << "Enter OUTPUT file path: ";
            std::getline(std::cin, outPath);
            std::cout << "Enter Vigenere key: ";
            std::getline(std::cin, key);

            std::ifstream inFile(inPath);
            if (inFile.is_open()) {
                std::stringstream buffer;
                buffer << inFile.rdbuf();
                std::string rawData = buffer.str();
                inFile.close();

                std::string encrypted = CipherHandler::encryptData(rawData, key);

                std::cout << encrypted << "\n";

                std::ofstream outFile(outPath);
                if (outFile.is_open()) {
                    outFile << encrypted;
                    outFile.close();
                    std::cout << "File encrypted and saved successfully!\n";
                }
                else {
                    std::cout << "Error writing to output file.\n";
                }
            }
            else {
                std::cout << "Error reading input file.\n";
            }
        }
        else if (command == 7) {
            std::string inPath, outPath, key;
            std::cout << "Enter INPUT encrypted file path: ";
            std::getline(std::cin, inPath);
            std::cout << "Enter OUTPUT decrypted file path: ";
            std::getline(std::cin, outPath);
            std::cout << "Enter Vigenere key: ";
            std::getline(std::cin, key);

            std::ifstream inFile(inPath);
            if (inFile.is_open()) {
                std::stringstream buffer;
                buffer << inFile.rdbuf();
                std::string encryptedData = buffer.str();
                inFile.close();

                std::string decrypted = CipherHandler::decryptData(encryptedData, key);

                std::cout << decrypted << "\n";

                textDoc.deserializeAll(decrypted);

                std::ofstream outFile(outPath);
                if (outFile.is_open()) {
                    outFile << decrypted;
                    outFile.close();
                    std::cout << "File decrypted, loaded into editor and saved successfully!\n";
                }
                else {
                    std::cout << "Error writing to output file.\n";
                }
            }
            else {
                std::cout << "Error reading input file.\n";
            }
        }
        else if (command == 8) {
            textDoc.printAll();
        }
        else if (command == 9) {
            break;
        }
        else {
            std::cout << "Try again\n";
        }
    }

    return 0;
}