//
// Created by gosi1cal on 4/26/16.
//

#ifndef NEWMACC_CONDITIONALENTRY_H
#define NEWMACC_CONDITIONALENTRY_H

#include <vector>
#include <string>

enum ConditionalType {FOR_LOOP, IF_ELSE, WHILE_LOOP};

class ConditionalEntry {
public:
    ConditionalEntry(int condition_num, ConditionalType type_used); // Constructor

    void AddCommand(std::string used); // add code to statement

    void Add_To_Statement_List(std::string used); // adds to statement list

    void Add_For_Updater(std::string used); // adds the updating command

    void Add_Conditional_Command(std::string used); // the checking condition

    void Add_End_Command(std::string used); // adds to the ending commands vector

    void Add_If_Command(std::string used); // adds to the if commands

    void Add_Else_Command(std::string used); // adds to the else command

    std::vector<std::string> GetCommands(); // get vector of all commands

    void Fix_For_Loop(std::string replace, std::string with);

    bool Replace(std::string& str, const std::string& from, const std::string& to); // function to replace substring found in string with new string

    bool WasUsed();

    void PrintEntries();

    int NumEntries();

    std::string GetLabelName();

    std::string GetAllCommands(); // returns the string that needs to be generated in the code file

    std::string cur_stmt_label = "";
    std::string cur_jmp_lbl = "";
    std::string cur_end_lbl = "";
    std::string cur_if_lbl = "";
    std::string cur_else_lbl = "";

    ConditionalType type_assigned;

private:
    bool commands_used = false;

    std::string label;
    std::vector<std::string> all_commands; // all commands

    // Break conitionals and loops into parts
    std::vector<std::string> statment_list_commands; // all commands, while in a loop/conditional
    std::vector<std::string> end_commands; // ending commands, any commands that run after the statement list
    std::vector<std::string> update_commands; // updaters, commands that update the case with each pass
    std::vector<std::string> conditional_commands; // conditonal commands, commands that check the case to see if it is supposed to run
    std::vector<std::string> if_commands; // if commands, for an if_else
    std::vector<std::string> else_commands; // else commands, for an if_else

};


#endif //NEWMACC_CONDITIONALENTRY_H
