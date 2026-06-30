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

            size_t delimPos = lineStr.find('|');
            if (delimPos == std::string::npos) continue;

            std::string type = lineStr.substr(0, delimPos);
            std::string content = lineStr.substr(delimPos + 1);

            if (type == "TEXT") {
                addLine(new TextLine(content));
            }
            else if (type == "CHECK") {
                size_t nextDelim = content.find('|');
                bool checked = (content.substr(0, nextDelim) == "1");
                std::string item = content.substr(nextDelim + 1);
                addLine(new ChecklistLine(item, checked));
            }
            else if (type == "CONTACT") {
                size_t d1 = content.find('|');
                size_t d2 = content.find('|', d1 + 1);
                std::string n = content.substr(0, d1);
                std::string s = content.substr(d1 + 1, d2 - d1 - 1);
                std::string e = content.substr(d2 + 1);
                addLine(new ContactLine(n, s, e));
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