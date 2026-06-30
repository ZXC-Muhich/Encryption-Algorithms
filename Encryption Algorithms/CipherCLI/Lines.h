#pragma once
#include <iostream>
#include <string>

class Line {
public:
    virtual void print() const = 0;
    virtual std::string serialize() const = 0;
    virtual ~Line() {}
};

class TextLine : public Line {
    std::string text;
public:
    TextLine(const std::string& t) : text(t) {}

    void print() const override {
        std::cout << "Text: " << text << std::endl;
    }

    std::string serialize() const override {
        return "TEXT|" + text;
    }
};

class ContactLine : public Line {
    std::string name;
    std::string surname;
    std::string email;
public:
    ContactLine(const std::string& n, const std::string& s, const std::string& e)
        : name(n), surname(s), email(e) {
    }

    void print() const override {
        std::cout << "Contact - " << name << " " << surname << ", E-mail: " << email << std::endl;
    }

    std::string serialize() const override {
        return "CONTACT|" + name + "|" + surname + "|" + email;
    }
};

class ChecklistLine : public Line {
    std::string item;
    bool checked;
public:
    ChecklistLine(const std::string& i, bool c) : item(i), checked(c) {}

    void print() const override {
        std::cout << "[ " << (checked ? "x" : " ") << " ] " << item << std::endl;
    }

    std::string serialize() const override {
        return "CHECK|" + std::to_string(checked) + "|" + item;
    }
};