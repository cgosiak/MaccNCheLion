//
// Created by caleb on 4/6/16.string
//

#ifndef MNCLION_DATAENTRY_H
#define MNCLION_DATAENTRY_H

#include <string>
#include <vector>

enum DataTypes  { TYPE_BOOL_LIT, TYPE_CHEESE_LIT, TYPE_SPECIAL_CHEESE_LIT, TYPE_INT_LIT, TYPE_FLOAT_LIT, TYPE_NONE};

class DataEntry {

public:
    DataEntry(std::string id, DataTypes type, std::string label_name, int lbl_used); // initialization of entry

    // void AssignType(DataTypes type); // define the type of the object

    void AssignValue(std::string val); // assign a value to the variable

    void ReserveSpace(); // reserve space for string

    DataTypes GetType(); // return the type of the object

    std::string GetValue(); // return a string representation of the value stored in this variable

    std::string GetID(); // return id of object

    std::string GetDataLabel(); // return label name for assembly file

    bool WasUsed(); // basic method to return whether or not the variable was ever used

    std::string GetDataLine(); // return string for representing data in assembly

    std::string GetTempLabels(); // Returns the temp labels for the program

    std::string GetCurrentTempVar(); // returns the temp variable last assigned for this variable

private:
    DataTypes entry_type; // the type of the variable

    std::string ReplaceAll(std::string str, const std::string& from, const std::string& to); // Replaces strings with strings

    bool entry_used = false; // Test of whether the variable was ever assigned a value

    std::string cur_temp_assigned = "";
    int temps_used = 0;

    int lbl = 0;

    int string_reservation_space = 50;

    std::vector<DataEntry> temp_variables;

    void AssignTempValue(std::string val); // assign a value to the variable

    void ReserveCheeseSpace(); // reserve space for empty string assignment

    // Data line, for data section in assembly
    std::string data_line;

    // Name of variable
    std::string variable_name;

    // Name in data section of assembly language
    std::string label_value;

    // Value assigned to variable
    std::string value;

    // Some type checking
    bool isInt(const std::string & s); // checks if the string passed is of type int

    bool isBool(const std::string & s); // checks if the string passed is a valid bool

    bool isReal(const std::string &s); // checks if string is real

    // Type conversion
    std::string UpperCase(std::string s); // upper cases a string, returns upper cased string

    // Some error raising
    void RaiseError_Assignment(std::string in, std::string t); // assignment error

};


#endif //MNCLION_DATAENTRY_H
