#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "Lines.h"

class TextDocument {
    std::vector<Line*> lines;
public:
    void addLine(Line* line) {
        lines.push_back(line);
    }

    void printAll() const {
        for (size_t i = 0; i < lines.size(); ++i) {
            lines[i]->print();
        }
    }

    std::string serializeAll() const {
        std::string result = "";
        for (size_t i = 0; i < lines.size(); ++i) {
            result += lines[i]->serialize() + "\n";
        }
        return result;
    }

    void deserializeAll(const std::string& data) {
        clear();
        std::stringstream ss(data);
        std::string lineStr;

        while (std::getline(ss, lineStr)) {
            if (lineStr.empty()) continue;

            if (lineStr.find("Text: ") == 0) {
                addLine(new TextLine(lineStr.substr(6)));
            }
            else if (lineStr.find("[ ") == 0 && lineStr.length() >= 6) {
                bool checked = (lineStr[2] == 'x' || lineStr[2] == 'X');
                std::string item = lineStr.substr(6);
                addLine(new ChecklistLine(item, checked));
            }
            else if (lineStr.find("Contact - ") == 0) {
                std::string content = lineStr.substr(10);
                size_t commaPos = content.find(", E-mail: ");

                if (commaPos != std::string::npos) {
                    std::string fullName = content.substr(0, commaPos);
                    std::string email = content.substr(commaPos + 10);

                    size_t spacePos = fullName.find(' ');
                    std::string n = (spacePos != std::string::npos) ? fullName.substr(0, spacePos) : fullName;
                    std::string s = (spacePos != std::string::npos) ? fullName.substr(spacePos + 1) : "";

                    addLine(new ContactLine(n, s, email));
                }
            }
        }
    }

    void clear() {
        for (size_t i = 0; i < lines.size(); ++i) {
            delete lines[i];
        }
        lines.clear();
    }

    ~TextDocument() {
        clear();
    }
};