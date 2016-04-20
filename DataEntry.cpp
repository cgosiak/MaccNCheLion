//
// Created by caleb on 4/6/16.
//

#include <iostream>
#include "DataEntry.h"
#include <algorithm>
#include <sstream>

DataEntry::DataEntry(std::string id, DataTypes type, std::string label_name) {
    variable_name = id;
    entry_type = type;
    label_value = label_name;
}

void DataEntry::AssignValue(std::string val) {

    // Need to have case statement here to make sure assignment matches type
    switch (entry_type) {
        case TYPE_INT_LIT:
            if (DataEntry::isInt(val)) {
                value = val;
                data_line = "INT   0";
            }
            else {
                DataEntry::RaiseError_Assignment(val, "TYPE_INT_LIT");
            }
            break;
        case TYPE_BOOL_LIT:
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
            data_line = "STRING   \"\"";
            break;
        case TYPE_FLOAT_LIT:
            // DataEntry::RaiseError_Assignment(val, "TYPE_FLOAT_LIT");
            data_line = "REAL   0.0";
            break;
        default:
            DataEntry::RaiseError_Assignment(val, "TYPE_NONE");
            break;
    }
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
