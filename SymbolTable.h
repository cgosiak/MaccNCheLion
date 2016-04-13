//
// Created by gosi1cal on 4/4/16.
//

#ifndef FINAL_COMPILER_SYMBOLTABLE_H
#define FINAL_COMPILER_SYMBOLTABLE_H

#include "DataEntry.h"
#include <vector>

class SymbolTable {

public:
    SymbolTable(); // Initializes Symbol Table Object

    void AddEntry(std::string id, DataTypes type); // Add entry to symbol table

    bool EntryExists(std::string id); // Is the entry already in the table

    void UpdateEntry(std::string id, std::string entry_data); // If the entry already exists, and we need to update it

    int GetEntry(std::string id); // Get the location of the variable in or vector object

    DataEntry GetDataObject(std::string id); // returns the data entry object

    std::string FinishSymbolTable(); // Returns a string to write the symbol table to the output assembly file

private:
    int total_entries = 0; // Current amount of stored data entries

    std::vector<DataEntry> table_entries; // Vector object containing all entries

};


#endif //FINAL_COMPILER_SYMBOLTABLE_H
