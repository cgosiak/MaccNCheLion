//
// Created by gosi1cal on 4/26/16.
//


#include <iostream>
#include "ConditionalEntry.h"

ConditionalEntry::ConditionalEntry(int condition_num, ConditionalType type_used) {
    cur_end_lbl = "END" + std::to_string(condition_num);
    cur_jmp_lbl = "JMP" + std::to_string(condition_num);
    cur_stmt_label = "STM" + std::to_string(condition_num);
    cur_if_lbl = "IF" + std::to_string(condition_num);
    cur_else_lbl = "ELSE" + std::to_string(condition_num);

    // Put the labels into the correct vectors right away
    Add_Conditional_Command("LABEL\t" + cur_stmt_label); // the very first label showing the beginning of a condition/loop
    Add_If_Command("LABEL\t" + cur_if_lbl); // label for the top of the if statement
    Add_Else_Command("LABEL\t" + cur_else_lbl); // label for the else statement
    Add_To_Statement_List("LABEL\t" + cur_jmp_lbl);

    switch (type_used) {
        case IF_ELSE:{
            std::string jump_line = "JMP\t" + cur_jmp_lbl;
            std::string first_line = "LABEL\t" + cur_stmt_label;
            all_commands.push_back(jump_line);
            all_commands.push_back(first_line);
            break;
        }
        case FOR_LOOP:
        case WHILE_LOOP: {
            all_commands.push_back("LABEL    " + cur_stmt_label);
            break;
        }
    }
    commands_used = true;
    type_assigned = type_used;
}

void ConditionalEntry::AddCommand(std::string used) {
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
    return cur_stmt_label;
}

std::string ConditionalEntry::GetAllCommands() {
    std::string commands = "";

    switch (type_assigned) {
        case IF_ELSE: {
            Add_Conditional_Command("JMP\t" + cur_else_lbl); // condition not met jump to else
            Add_If_Command("JMP\t" + cur_end_lbl); // unconditional jump so the else is not run
            Add_Else_Command("LABEL\t" + cur_end_lbl); // Add the ending label to the bottom of the else

            for (int i = 0; i < conditional_commands.size(); ++i) {
                commands = commands + conditional_commands[i] + "\n";
            }

            for (int j = 0; j < if_commands.size(); ++j) {
                commands = commands + if_commands[j] + "\n";
            }

            for (int k = 0; k < else_commands.size(); ++k) {
                commands = commands + else_commands[k] + "\n";
            }

            break;
        }
        case WHILE_LOOP: {
            Add_Conditional_Command("JMP\t" + cur_end_lbl); // condition not met jump to end
            Add_To_Statement_List("JMP\t" + cur_stmt_label); // go back home to start again and check for conditional
            Add_To_Statement_List("LABEL\t" + cur_end_lbl); // end if condition not met

            for (int i = 0; i < conditional_commands.size(); ++i) {
                commands = commands + conditional_commands[i] + "\n";
            }

            for (int j = 0; j < statment_list_commands.size(); ++j) {
                commands = commands + statment_list_commands[j] + "\n";
            }

            break;
        }
        case FOR_LOOP: {
            Add_Conditional_Command("JMP\t" + cur_end_lbl); // condition not met jump to end
            Add_For_Updater("JMP\t" + cur_stmt_label); // always go back to the beginning of the statement, let the conditional take care of where to go
            Add_For_Updater("LABEL\t" + cur_end_lbl); // label to end goes after all other code in loop

            for (int i = 0; i < conditional_commands.size(); ++i) {
                commands = commands + conditional_commands[i] + "\n";
            }

            for (int j = 0; j < statment_list_commands.size(); ++j) {
                commands = commands + statment_list_commands[j] + "\n";
            }

            for (int k = 0; k < update_commands.size(); ++k) {
                commands = commands + update_commands[k] + "\n";
            }
            break;
        }
        case DO_LOOP: {
            Add_Conditional_Command("JMP\t" + cur_jmp_lbl); // back to top, if condition not met
            Add_Conditional_Command("LABEL\t" + cur_end_lbl); // end with the condition

            for (int i = 0; i < statment_list_commands.size(); ++i) {
                commands = commands + statment_list_commands[i] + "\n";
            }

            for (int j = 0; j < conditional_commands.size(); ++j) {
                commands = commands + conditional_commands[j] + "\n";
            }
        }
    }

    return commands;
}

void ConditionalEntry::Add_For_Updater(std::string used) {
    update_commands.push_back(used);
}

void ConditionalEntry::Add_To_Statement_List(std::string used) {
    statment_list_commands.push_back(used);
}

void ConditionalEntry::Add_Conditional_Command(std::string used) {
    conditional_commands.push_back(used);
}

void ConditionalEntry::Add_End_Command(std::string used) {
    end_commands.push_back(used);
}

void ConditionalEntry::Add_If_Command(std::string used) {
    if_commands.push_back(used);
}

void ConditionalEntry::Add_Else_Command(std::string used) {
    else_commands.push_back(used);
}


bool ConditionalEntry::Replace(std::string &str, const std::string &from, const std::string &to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void ConditionalEntry::Fix_Loop_Labels(std::string replace, std::string with) {
    if (type_assigned == FOR_LOOP) {
        for (int i = 0; i < statment_list_commands.size(); ++i) {
            if (statment_list_commands[i].find(replace) != std::string::npos) {
                Replace(statment_list_commands[i], replace, with);
            }
        }
    }
    if (type_assigned == DO_LOOP) {
        for (int i = 0; i < conditional_commands.size(); ++i) {
            if (conditional_commands[i].find(replace) != std::string::npos) {
                Replace(conditional_commands[i], replace, with);
            }
        }
    }
}
