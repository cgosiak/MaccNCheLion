//
// Created by gosi1cal on 4/4/16.
//

#ifndef FINAL_COMPILER_SYMBOLTABLE_H
#define FINAL_COMPILER_SYMBOLTABLE_H

#include "DataEntry.h"
#include <vector>
#include "ConditionalEntry.h"

class SymbolTable {

public:
    SymbolTable(); // Initializes Symbol Table Object

    ConditionalEntry CreateConditional(ConditionalType type_used); // create a new condtional

    void AddEntry(std::string id, DataTypes type); // Add entry to symbol table

    bool EntryExists(std::string id); // Is the entry already in the table

    void UpdateEntry(std::string id, std::string entry_data); // If the entry already exists, and we need to update it

    void ReserveNewLabel(std::string id); // need to add this to reserve space specifically for cheese_lit

    int GetEntry(std::string id); // Get the location of the variable in or vector object

    DataEntry GetDataObject(std::string id); // returns the data entry object

    ConditionalEntry GetCondObject(std::string id);

    std::string FinishSymbolTable(); // Returns a string to write the symbol table to the output assembly file

    void CloseConditional();

    std::string CloseElse();

    std::string GetCurrentConditionalLabel();

    ConditionalEntry *cur_cond;

private:
    int total_entries = 0; // Current amount of stored data entries
    int total_conditonals = 0;

    std::vector<DataEntry> table_entries; // Vector object containing all entries
    std::vector<ConditionalEntry> conditional_entries; // all conditionals

};


#endif //FINAL_COMPILER_SYMBOLTABLE_H
