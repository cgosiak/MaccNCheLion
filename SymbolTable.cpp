//
// Created by gosi1cal on 4/4/16.
//

#include <iostream>
#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    // Initializes SymbolTable
}

void SymbolTable::AddEntry(std::string id, DataTypes type) {
    // First Check if the entry exists
    if (SymbolTable::EntryExists(id)) {
        // Should update the entry, rather than create a new one
        std::cout << "Already Exists!" << std::endl;
    }
    else {
        // Add to total entries
        total_entries++;

        // Create label entry name
        std::string lbl_name = "lbl" + std::to_string(total_entries);

        // Create a new entry
        std::cout << "Added entry!" << std::endl;
        DataEntry my_entry(id, type, lbl_name);
        table_entries.push_back(my_entry);
    }
}

void SymbolTable::UpdateEntry(std::string id, std::string entry_data) {
    if (SymbolTable::EntryExists(id)) {
        table_entries[SymbolTable::GetEntry(id)].AssignValue(entry_data);
    }
    else {
        //some error
    }
}

bool SymbolTable::EntryExists(std::string id) {
    // Loop through all vector entries to find if the id is already used
    for (int i = 0; i < table_entries.size(); ++i) {
        if  (table_entries[i].GetID() == id) {
            return true;
        }
    }
    return false;
}

int SymbolTable::GetEntry(std::string id) {
    if (SymbolTable::EntryExists(id)) {
        // Loop through all vector entries to find if the id is already used
        for (int i = 0; i < table_entries.size(); ++i) {
            if  (table_entries[i].GetID() == id) {
                return i;
            }
        }
    }
    else {
        // Error because entry does not yet exist
    }
}

DataEntry SymbolTable::GetDataObject(std::string id) {
    DataEntry* pointed_object;
    if (SymbolTable::EntryExists(id)) {
        pointed_object = &table_entries[SymbolTable::GetEntry(id)];
    }
    else {
        pointed_object = nullptr;
    }
    return *pointed_object;
}

std::string SymbolTable::FinishSymbolTable() {
    std::string symbol_table = "% Data Area ------------\n% ----------------------\n";

    for (int i = 0; i < total_entries; ++i) {
        if (table_entries[i].WasUsed()) {
            // Add entry to finished symbol table
            symbol_table = symbol_table + "LABEL    " + table_entries[i].GetDataLabel() + "\n" + table_entries[i].GetDataLine() + "\n";
        }
    }

    return symbol_table;
}
