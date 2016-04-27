//
// Created by gosi1cal on 4/26/16.
//


#include <iostream>
#include "ConditionalEntry.h"

ConditionalEntry::ConditionalEntry(std::string label_name, std::string jmp_name) {
    label = label_name;
    std::string jump_line = "JMP    " + jmp_name;
    std::string first_line = "LABEL    " + label_name;
    all_commands.push_back(jump_line);
    all_commands.push_back(first_line);
    commands_used = true;
}

void ConditionalEntry::AddCommand(std::string used) {
    commands_used = true;
    all_commands.push_back(used);
}

std::vector<std::string> ConditionalEntry::GetCommands() {
    return all_commands;
}

bool ConditionalEntry::WasUsed() {
    return commands_used;
}

void ConditionalEntry::PrintEntries() {
    for (int i = 0; i < all_commands.size(); ++i) {
        std::cerr << all_commands[i] << std::endl;
    }
}

int ConditionalEntry::NumEntries() {
    return all_commands.size();
}

std::string ConditionalEntry::GetLabelName() {
    return label;
}

std::string ConditionalEntry::GetAllCommands() {
    std::string commands;

    for (int i = 0; i < all_commands.size(); ++i) {
        commands = commands + all_commands[i] + "\n";
    }

    return commands;
}
