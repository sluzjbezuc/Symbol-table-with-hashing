#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <list>

using namespace std;

const int TABLE_SIZE = 8;
const int MAX_SYMBOL_NAME_LENGTH = 30;

struct Symbol {
    string name;
    string type;
    string value;
};

class SymbolTable {
private:
    list<Symbol> table[TABLE_SIZE];

    // Hash function to calculate the index
    int hash(const string& name) {
        int sum = 0;
        for (char ch : name) {
            sum += static_cast<int>(ch);
        }
        return sum % TABLE_SIZE;
    }

    bool isValidInteger(const string& value) {
        regex integerRegex("[-+]?[0-9]+");
        return regex_match(value, integerRegex);
    }

    bool isValidFloat(const string& value) {
        regex floatRegex("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?");
        return regex_match(value, floatRegex);
    }

    bool isValidDouble(const string& value) {
        regex floatRegex("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?");
        return regex_match(value, floatRegex);
    }

    bool isValidChar(const string& value) {
        return value.length() == 1;
    }

    bool isValidString(const string& value) {
        // Strings can be of any length
        return true;
    }

    bool isValidBoolean(const string& value) {
        return value == "true" || value == "false";
    }

    bool isValidVoid(const string& value) {
        // Void symbols cannot have any assigned value
        return value.length() == 0;
    }

    bool isValidPointer(const string& value) {
        // Pointers cannot have an assigned value
        return value.empty();
    }

    bool isValidReference(const string& value) {
        // References cannot have an assigned value
        return value.empty();
    }


public:
    void insert_symbol(const string& name, const string& type, const string& value) {
        if (name.length() > MAX_SYMBOL_NAME_LENGTH) {
            cout << "ERROR: Symbol name exceeds the maximum length." << endl;
            return;
        }

        if (!regex_match(name, regex("^[a-zA-Z0-9_]*$"))) {
            cout << "ERROR: Symbol name contains special characters." << endl;
            return;
        }

        if (isdigit(name[0])) {
            cout << "ERROR: Symbol name cannot start with a digit." << endl;
            return;
        }
        Symbol* existingSymbol = find_symbol(name);

        bool isValidType = true;
        if (type == "int") {
            if (!value.empty()) {
                isValidType = isValidInteger(value);
            }
        }
        else if (type == "float") {
            if (!value.empty()) {
                isValidType = isValidFloat(value);
            }
        }
        else if (type == "double") {
            if (!value.empty()) {
                isValidType = isValidDouble(value);
            }
        }
        else if (type == "char") {
            if (!value.empty()) {
                isValidType = isValidChar(value);
            }
        }
        else if (type == "string") {
            // No validation needed for string type
        }
        else if (type == "bool") {
            if (!value.empty()) {
                isValidType = isValidBoolean(value);
            }
        }
        else if (type == "void") {
            if (!value.empty()) {
                isValidType = isValidVoid(value);
            }
        }
        else if (type.find('*') != string::npos) {
            // Handle pointer types
            if (!isValidPointer(value)) {
                isValidType = false;
            }
        }
        else if (type.find('&') != string::npos) {
            // Handle reference types
            if (!isValidReference(value)) {
                isValidType = false;
            }
        }
        else {
            // Add checks for more data types if needed
            isValidType = false;
        }

        if (!isValidType) {
            cout << "ERROR: Invalid data type or value for symbol '" << name << "'." << endl;
            return;
        }

        Symbol symbol;
        symbol.name = name;
        symbol.type = type;
        symbol.value = value;

        int index = hash(name);
        bool symbolUpdated = false;

        // Check if the symbol already exists in the linked list at the computed hash value
        for (Symbol& sym : table[index]) {
            if (sym.name == name) {
                // Update existing symbol
                sym = symbol;
                symbolUpdated = true;
                break;
            }
        }

        if (symbolUpdated) {
            cout << "Symbol '" << name << "' successfully updated." << endl;
        }
        else {
            // Insert the symbol at the end of the linked list
            table[index].push_back(symbol);
            cout << "Symbol '" << name << "' successfully inserted." << endl;
        }
    }

    Symbol* find_symbol(const string& name) {
        int index = hash(name);
        for (Symbol& symbol : table[index]) {
            if (symbol.name == name) {
                return &symbol;
            }
        }
        return nullptr;
    }

    void get_symbol(const string& name) {
        Symbol* symbol = find_symbol(name);
        if (symbol != nullptr) {
            cout << "Symbol Name: " << symbol->name << endl;
            cout << "Symbol Type: " << symbol->type << endl;
            cout << "Symbol Value: " << symbol->value << endl;
        }
        else {
            cout << "ERROR: Symbol not found." << endl;
        }
    }
};


#endif  // SYMBOL_TABLE_H