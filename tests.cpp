#include "SymbolTable.h"
#include <iostream>

void runSymbolTableTestCases() {
    SymbolTable symbolTable;

    // TEST1
    cout << endl << "Test 1: Insert a new symbol into an empty symbol table:" << endl;
    symbolTable.insert_symbol("x", "int", "5");

    // TEST 2
    cout << endl << "Test 2: Insert a symbol that already exists in the table:" << endl;
    symbolTable.insert_symbol("y", "float", "2.5");
    symbolTable.insert_symbol("y", "int", "5");

    // TEST 3
    cout << endl << "Test 3: Find a symbol that exists in the table:" << endl;
    Symbol* symbol = symbolTable.find_symbol("y");
    if (symbol != nullptr) {
        cout << "Test 3: Symbol found." << endl;
    }
    else {
        cout << "ERROR: Test 3: Symbol not found." << endl;
    }

    // TEST 4
    cout << endl << "Test 4: Find a symbol that does not exist in the table:" << endl;
    symbol = symbolTable.find_symbol("z");
    if (symbol != nullptr) {
        cout << "Test 4: Symbol found." << endl;
    }
    else {
        cout << "ERROR: Test 4: Symbol not found." << endl;
    }

    // TEST 5
    cout << endl << "Test 5: Get the information of a symbol that exists in the table:" << endl;
    symbolTable.get_symbol("x");

    // TEST 6
    cout << endl << "Test 6: Get the information of a symbol that does not exist in the table:" << endl;
    symbolTable.get_symbol("z");

    // TEST 7
    cout << endl << "Test 7: Test collision handling by adding multiple symbols with the same hash value:" << endl;
    symbolTable.insert_symbol("a", "int", "1");
    symbolTable.insert_symbol("b", "float", "2");
    symbolTable.insert_symbol("c", "string", "3");

    // TEST 8
    cout << endl << "Test 8: Test error handling by trying to add a symbol with an invalid data type:" << endl;
    symbolTable.insert_symbol("x", "invalid", "5");

    // TEST 9
    cout << endl << "Test 9: Test error handling by trying to add a symbol with an invalid value:" << endl;
    symbolTable.insert_symbol("x", "int", "invalid_value");

    // TEST 10
    cout << endl << "Test 10: Test error handling by trying to add a symbol with an invalid name (with special chars):" << endl;
    symbolTable.insert_symbol("x#", "int", "10");

    // TEST 11
    cout << endl << "Test 11: Test error handling by trying to add a symbol with an invalid name (too long):" << endl;
    symbolTable.insert_symbol("this_symbol_name_is_too_too_too_too_too_long", "int", "10");

    // TEST 12
    cout << endl << "Test 12: Symbol's name case sensitivity test:" << endl;
    symbolTable.insert_symbol("CaseSENSITIVE", "string", "CaseSENSISTIVEValue");
    symbolTable.get_symbol("CaseSENSITIVE");
    symbolTable.get_symbol("casesensitive");

    // TEST 13
    cout << endl << "Test 13: Symbol's name cannot start with a digit:" << endl;
    symbolTable.insert_symbol("5", "int", "15");




    cout << "Symbol table test cases completed." << endl << endl;
}