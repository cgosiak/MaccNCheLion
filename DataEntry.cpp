//
// Created by caleb on 4/6/16.
//

#include <iostream>
#include "DataEntry.h"
#include <algorithm>
#include <string>
#include <sstream>

DataEntry::DataEntry(std::string id, DataTypes type, std::string label_name, int lbl_used) {
    variable_name = id;
    entry_type = type;
    label_value = label_name;
    lbl = lbl_used;
}

void DataEntry::AssignValue(std::string val) {

    // Need to have case statement here to make sure assignment matches type
    std::string temp_name = "L" + std::to_string(lbl) + "T" + std::to_string(temps_used);
    temps_used++;
    DataEntry new_data(variable_name, entry_type, temp_name, lbl);
    cur_temp_assigned = temp_name;

    switch (entry_type) {
        case TYPE_INT_LIT:
            if (val == "") {
                val = "0";
            }
            if (DataEntry::isInt(val)) {
                value = val;
                data_line = "INT   0";
            }
            else {
                DataEntry::RaiseError_Assignment(val, "TYPE_INT_LIT");
            }
            break;
        case TYPE_BOOL_LIT:
            if (val == "") {
                val = "FALSE";
            }
            if (DataEntry::isBool(val)) {
                value = DataEntry::UpperCase(val);
                data_line = "INT   0";
            }
            else {
                DataEntry::RaiseError_Assignment(val, "TYPE_BOOL_LIT");
            }
            break;
        case TYPE_CHEESE_LIT:
            // should technically never be an error, any grouping of characters can be viewed as a string
            //DataEntry::RaiseError_Assignment(val, TYPE_CHEESE_LIT);
            value = val;
            data_line = "SKIP    50";
            break;
        case TYPE_FLOAT_LIT:
            // DataEntry::RaiseError_Assignment(val, "TYPE_FLOAT_LIT");
            if (val == "") {
                val = "0.0";
            }
            data_line = "REAL   0.0";
            break;
        default:
            DataEntry::RaiseError_Assignment(val, "TYPE_NONE");
            break;
    }

    new_data.AssignTempValue(val);
    temp_variables.push_back(new_data);

    entry_used = true;
    std::cout << "Value: " << val << " assigned." << std::endl;
}

DataTypes DataEntry::GetType() {
    return entry_type;
}

std::string DataEntry::GetValue() {
    return value;
}

std::string DataEntry::GetID() {
    return variable_name;
}

void DataEntry::RaiseError_Assignment(std::string in, std::string t) {
    std::cout << "Assignment Error: Cannot assign value " << in << " to type " << t << std::endl;
    exit(1); // exit and end program
}

bool DataEntry::isInt(const std::string &s) {
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

    char * p ;
    strtol(s.c_str(), &p, 10) ;

    return (*p == 0) ;
}

bool DataEntry::isBool(const std::string &s) {
    std::string uc = DataEntry::UpperCase(s);
    if (uc == "FALSE" || uc == "TRUE") {
        return true;
    }
    else {
        return false;
    }
}

std::string DataEntry::UpperCase(std::string sr) {
    std::string s = sr;
    for (auto & c: s) c = toupper(c);

    return s;
}

std::string DataEntry::GetDataLabel() {
    return label_value;
}

bool DataEntry::WasUsed() {
    return entry_used;
}

std::string DataEntry::GetDataLine() {
    return data_line;
}

bool DataEntry::isReal(const std::string &s) {
    std::string test = "";
    return true;
}

void DataEntry::AssignTempValue(std::string val) {
    // Need to have case statement here to make sure assignment matches type
    switch (entry_type) {
        case TYPE_INT_LIT:
            if (val == "") {
                val = "0";
            }
            if (DataEntry::isInt(val)) {
                value = val;
                data_line = "INT   0";
            }
            else {
                DataEntry::RaiseError_Assignment(val, "TYPE_INT_LIT");
            }
            break;
        case TYPE_BOOL_LIT:
            if (val == "") {
                val = "FALSE";
            }
            if (DataEntry::isBool(val)) {
                value = DataEntry::UpperCase(val);
                data_line = "INT   0";
                if (value == "FALSE") {
                    value = "0";
                }
                else {
                    value = "1";
                }
            }
            else {
                DataEntry::RaiseError_Assignment(val, "TYPE_BOOL_LIT");
            }
            break;
        case TYPE_CHEESE_LIT:
            // should technically never be an error, any grouping of characters can be viewed as a string
            //DataEntry::RaiseError_Assignment(val, TYPE_CHEESE_LIT);
            value = val;
            if (value.find(":") != std::string::npos) {
                value = ReplaceAll(value,":","::");
            }
            data_line = "STRING   \"\"";
            break;
        case TYPE_FLOAT_LIT:
            // DataEntry::RaiseError_Assignment(val, "TYPE_FLOAT_LIT");
            if (val == "") {
                val = "0.0";
            }
            data_line = "REAL   0.0";
            break;
        default:
            DataEntry::RaiseError_Assignment(val, "TYPE_NONE");
            break;
    }

    entry_used = true;
}

std::string DataEntry::GetTempLabels() {
    std::string temps = "";

    for (int i = 0; i < temps_used; ++i) {
        switch (temp_variables[i].GetType()) {
            case TYPE_CHEESE_LIT:
                temps = temps + "LABEL    " + temp_variables[i].GetDataLabel() + "\nSTRING    \"" + temp_variables[i].GetValue() + "\"\n";
                break;
            case TYPE_FLOAT_LIT:
                temps = temps + "LABEL    " + temp_variables[i].GetDataLabel() + "\nREAL      " + temp_variables[i].GetValue() + "\n";
                break;
            case TYPE_BOOL_LIT:
                temps = temps + "LABEL    " + temp_variables[i].GetDataLabel() + "\nINT       " + temp_variables[i].GetValue() + "\n";
                break;
            case TYPE_INT_LIT:
                temps = temps + "LABEL    " + temp_variables[i].GetDataLabel() + "\nINT       " + temp_variables[i].GetValue() + "\n";
                break;
        }
    }

    return temps;
}

std::string DataEntry::GetCurrentTempVar() {
    return cur_temp_assigned;
}

std::string DataEntry::ReplaceAll(std::string str, const std::string &from, const std::string &to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
