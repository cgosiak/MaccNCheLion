//
// Created by gosi1cal on 4/26/16.
//

#ifndef NEWMACC_CONDITIONALENTRY_H
#define NEWMACC_CONDITIONALENTRY_H

#include <vector>
#include <string>



class ConditionalEntry {
public:
    ConditionalEntry(std::string label_name, std::string jmp_name); // Constructor

    void AddCommand(std::string used); // add code to statement

    std::vector<std::string> GetCommands(); // get vector of all commands

    bool WasUsed();

    void PrintEntries();

    int NumEntries();

    std::string GetLabelName();

    std::string GetAllCommands();

private:
    bool commands_used = false;

    std::string label;
    std::vector<std::string> all_commands; // all commands
};


#endif //NEWMACC_CONDITIONALENTRY_H
