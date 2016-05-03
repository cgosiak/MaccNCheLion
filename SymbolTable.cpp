//
// Created by gosi1cal on 4/4/16.
//

#include <iostream>
#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    // Initializes SymbolTable
}

void SymbolTable::AddEntry(std::string id, DataTypes type) {
    std::string type_string;
    std::string default_value;
    switch (type) {
        case TYPE_CHEESE_LIT:
            type_string = "CHEESE_LIT";
            default_value = "";
            break;
        case TYPE_FLOAT_LIT:
            type_string = "FLOAT_LIT";
            default_value = "0.00";
            break;
        case TYPE_INT_LIT:
            type_string = "INT_LIT";
            default_value = "0";
            break;
        case TYPE_BOOL_LIT:
            type_string = "BOOL_LIT";
            default_value = "FALSE";
            break;
        default:
        std::cerr << "Undefined type error" << std::endl;
    }

    // First Check if the entry exists
    if (SymbolTable::EntryExists(id)) {
        // Should update the entry, rather than create a new one
        std::cout << "Already Exists!" << std::endl;
    }
    else {
        // Add to total entries
        total_entries++;

        // Create label entry name
        std::string lbl_name = "LBL" + std::to_string(total_entries);

        // Create a new entry
        DataEntry my_entry(id, type, lbl_name, total_entries);
        table_entries.push_back(my_entry);
        // table_entries[SymbolTable::GetEntry(id)].AssignValue(default_value);
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
            symbol_table = symbol_table + "LABEL\t" + table_entries[i].GetDataLabel() + "\n" + table_entries[i].GetDataLine() + "\n";
            symbol_table = symbol_table + table_entries[i].GetTempLabels();
        }
    }

    return symbol_table;
}


void SymbolTable::ReserveNewLabel(std::string id) {
    if (SymbolTable::EntryExists(id)) {
        table_entries[SymbolTable::GetEntry(id)].ReserveSpace();
    }
    else {
        //some error
    }
}

ConditionalEntry SymbolTable::CreateConditional(ConditionalType type_used) {
    ConditionalEntry my_entry(total_conditonals, type_used);
    cur_cond = &my_entry;
    total_conditonals++;
    return my_entry;
}

void SymbolTable::CloseConditional() {
    cur_cond->AddCommand("JMP    " + cur_cond->cur_end_lbl);
    cur_cond->AddCommand("LABEL    " + cur_cond->cur_jmp_lbl);
    conditional_entries.push_back(*cur_cond);
}

std::string SymbolTable::GetCurrentConditionalLabel() {
    return cur_cond->cur_stmt_label;
}

ConditionalEntry SymbolTable::GetCondObject(std::string id) {
    ConditionalEntry *entry;
    for (int i = 0; i < conditional_entries.size(); ++i) {
        if (conditional_entries[i].GetLabelName() == id) {
            entry = &conditional_entries[i];
            return *entry;
        }
    }
}

std::string SymbolTable::CloseElse() {
    return cur_cond->cur_end_lbl;
}
