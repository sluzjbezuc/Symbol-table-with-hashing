#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>
#include <unordered_set>
#include "SymbolTable.h"
#include "tests.cpp"


bool loadAndParseInputFile(const string& filename, SymbolTable& symbolTable) {
    // Load the input file
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "ERROR: Failed to open the input file." << endl;
        return false;
    }

    cout << "Loading and parsing the input file..." << endl;

    // Regular expression pattern for matching variable declarations
    regex variableDeclarationPattern(
        "\\b(void|char|signed\\s?char|unsigned\\s?char|short|int|signed\\s?int|unsigned\\s?int|long|signed\\s?long|"
        "unsigned\\s?long|long\\s?long|signed\\s?long\\s?long|unsigned\\s?long\\s?long|float|double|long\\s?double|"
        "wchar_t|bool|size_t|string)\\s+(const\\s+)?([a-zA-Z_][a-zA-Z0-9_]*)\\s*(?:\\((.*)\\))?(?:\\s*=\\s*([^;]*))?(?:\\s*;)?");

    string line;
    while (getline(inputFile, line)) {
        // Remove leading and trailing whitespaces from the line
        line = regex_replace(line, regex("^\\s+|\\s+$"), "");

        // Skip empty lines and comments
        if (line.empty() || line.substr(0, 2) == "//") {
            continue;
        }

        // Match the line against the variable declaration pattern
        smatch match;
        if (regex_search(line, match, variableDeclarationPattern)) {
            // Extract the type, identifier, arguments, and value from the matched string
            string type = match[1];
            string identifier = match[3];
            string arguments = match[4];
            string value = match[5];

            // Remove leading and trailing whitespaces from the value
            value = regex_replace(value, regex("^\\s+|\\s+$"), "");

            // Remove quotation marks from string value if present
            if (!value.empty() && value.front() == '"' && value.back() == '"' && value.length() > 1) {
                value = value.substr(1, value.length() - 2);
            }
            // Remove single quotation marks from char value if present
            else if (!value.empty() && value.front() == '\'' && value.back() == '\'' && value.length() > 2) {
                value = value.substr(1, value.length() - 2);
            }

            // Insert the symbol into the symbol table
            symbolTable.insert_symbol(identifier, type, value);

            // Process function arguments
            if (!arguments.empty()) {
                // Split the arguments by commas
                stringstream ss(arguments);
                string argument;
                while (getline(ss, argument, ',')) {
                    // Remove leading and trailing whitespaces from the argument
                    argument = regex_replace(argument, regex("^\\s+|\\s+$"), "");
                    // Extract the type and identifier from the argument
                    size_t spacePos = argument.rfind(' ');
                    if (spacePos != string::npos) {
                        string argType = argument.substr(0, spacePos);
                        string argIdentifier = argument.substr(spacePos + 1);
                        // Insert the argument into the symbol table without a value
                        symbolTable.insert_symbol(argIdentifier, argType, "");
                    }
                }
            }
        }
    }

    cout << "Parsing complete. Symbol table updated." << endl << endl;

    // Close the input file
    inputFile.close();

    return true;
}

int main() {

    SymbolTable symbolTable;

    //User's Interface
    cout << "Welcome to the Symbol Table program!" << endl;
    cout << "Available commands:" << endl;
    cout << "- insert <symbol_name> <symbol_type> <symbol_value>" << endl;
    cout << "- find <symbol_name>" << endl;
    cout << "- get <symbol_name>" << endl;
    cout << "- load <input_file_name>" << endl;
    cout << "- run tests" << endl;
    cout << "Enter a command (or 'exit' to quit):" << endl;

    string input;
    while (getline(cin, input)) {
        if (input == "exit") {
            break;
        }

        // Parse the command and symbol details from the input line
        istringstream iss(input);
        string command, symbolName, symbolType, symbolValue;

        if (!(iss >> command)) {
            cout << "Invalid input format." << endl;
            continue;
        }

        // Process the command
        if (command == "insert") {
            if (!(iss >> symbolName >> symbolType)) {
                cout << "ERROR: Invalid input format." << endl;
                continue;
            }
            iss.ignore();  // Ignore leading whitespace
            getline(iss, symbolValue);
            symbolTable.insert_symbol(symbolName, symbolType, symbolValue);
        }
        else if (command == "find") {
            if (!(iss >> symbolName)) {
                cout << "ERROR: Invalid input format." << endl;
                continue;
            }
            Symbol* symbol = symbolTable.find_symbol(symbolName);
            if (symbol != nullptr) {
                cout << "Symbol found." << endl;
            }
            else {
                cout << "ERROR: Symbol not found." << endl;
            }
        }
        else if (command == "get") {
            if (!(iss >> symbolName)) {
                cout << "ERROR: Invalid input format." << endl;
                continue;
            }
            symbolTable.get_symbol(symbolName);
        }
        else if (command == "load") {
            string filename;
            if (!(iss >> filename)) {
                cout << "Invalid input format." << endl;
                continue;
            }

            else if (loadAndParseInputFile(filename, symbolTable)) {
                cout << "Input file loaded and parsed successfully." << endl;
            }
            else {
                cout << "Failed to load and parse the input file." << endl;
            }
        }
        else if (input == "run tests") {
            runSymbolTableTestCases();
        }
        else {
            cout << "ERROR: Unknown command." << endl;
            }
    }
        return 0;
}
    