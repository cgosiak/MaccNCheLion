/*	____________________________________________________________________________

	    Semantics and Coding Component Implementation for the Micro Compiler

	                               mcode.cpp

	                              Version 2007
 
	                           James L. Richards
	                     Last Update: August 28, 2007
	                     Update by M. J. Wolf: January 21,2016

	The routines in this unit are based on those provided in the book 
	"Crafting A Compiler" by Charles N. Fischer and Richard J. LeBlanc, Jr., 
	Benjamin Cummings Publishing Co. (1991).

	See Section 2.3-2.4, pp. 31-40.
	____________________________________________________________________________
*/

#include <iostream>
#include <fstream>
using namespace std;

extern ifstream sourceFile;
extern ofstream outFile, listFile;

#include "mncscan.h"   // Scanner class definition
#include "mnccode.h"
#include "SymbolTable.h"
#include "mncparse.h"

extern Scanner scan; // global Scanner object declared in micro.cpp
extern SymbolTable symbolTable;
extern Parser parse;

// *******************
// **  Constructor  **
// *******************

CodeGen::CodeGen()
{
	maxTemp = 0;
}

// *******************************
// ** Private Member Functions  **
// *******************************

void CodeGen::CheckId(const string & s)
{
	if (!LookUp(s))  // variable not declared yet
		Enter(s);
}

void CodeGen::Enter(const string & s)
{
	symbolTable_Vector.push_back(s);
}

void CodeGen::ExtractExpr(const ExprRec & e, string& s)
{
	string t;
	int k, n;

	switch (e.kind)
	{
	case ID_EXPR:
	case TEMP_EXPR:  // operand form: +k(R15)
		s = e.name;
		n = 0;
		while (symbolTable_Vector[n] != s) n++;
		k = 2 * n;  // offset: 2 bytes per variable
		IntToAlpha(k, t);
		s = "+" + t + "(R15)";
		break;
	case LITERAL_EXPR:
		IntToAlpha(e.val, t);
		s = "#" + t;
	}
}

string CodeGen::ExtractOp(const OpRec & o)
{
	if (o.op == PLUS)
		return "IA        ";
	else
		return "IS        ";
}

void CodeGen::Generate(const string & s1, const string & s2, const string & s3)
{
    if (parse.in_conditional) {
        std::string code_input = s1;
        if (s2.length() > 0)
        {
            code_input = code_input + s2;
            if (s3.length() > 0)
            {
                code_input = code_input + ", " + s3;
            }
        }
        cout << "CODE INPUT: " << code_input << endl;
        parse.cur_conditional->AddCommand(code_input);
    }
    else {
        listFile.width(20);
        listFile << ' ' << s1;
        outFile << s1;
        if (s2.length() > 0)
        {
            listFile << s2;
            outFile << s2;
            if (s3.length() > 0)
            {
                listFile << ',' << s3;
                outFile << ',' << s3;
            }
        }
        listFile << endl;
        outFile << endl;
    }
}

string CodeGen::GetTemp()
{
	string s;
	static string t;

	t = "Temp&";
	IntToAlpha(++maxTemp, s);
	t += s;
	CheckId(t);
	return t;
}

void CodeGen::IntToAlpha(int val, string& str)
{
	int k;
	char temp;

	str = "";
	if (val == 0) str = "0";
	while (val > 0)
	{
		str.append(1, (char)(val % 10 + (int)'0'));
		val /= 10;
	}
	k = int(str.length());
	for (int i = 0; i < k/2; i++)
	{
		temp = str[i];
		str[i] = str[k-i-1];
		str[k-i-1] = temp;
	}
}

bool CodeGen::LookUp(const string & s)
{
	for (unsigned i = 0; i < symbolTable_Vector.size(); i++)
	if (symbolTable_Vector[i] == s)
		return true;

	return false;
}

// ******************************
// ** Public Member Functions  **
// ******************************

void CodeGen::Assign(const ExprRec & target, const ExprRec & source)
{
	string s;

	ExtractExpr(source, s);
	Generate("LD        ", "R0", s);
	ExtractExpr(target, s);
	Generate("STO       ", "R0", s);
}

void CodeGen::Finish()
{
	string s;

	listFile.width(6);
	listFile << ++scan.lineNumber << "  " << scan.lineBuffer << endl;
	Generate("HALT      ", "", "");
	
	// Output Symbol Table
	Generate(symbolTable.FinishSymbolTable(),"","");

	Generate("LABEL     ", "VARS", "");
	IntToAlpha(int(2*(symbolTable_Vector.size()+1)), s);
	Generate("SKIP      ", s, "");
	outFile.close();
	listFile << endl << endl;
	listFile << " _____________________________________________\n";
	listFile << " <><><><>   S Y M B O L   T A B L E   <><><><>\n"
		<< endl;
	listFile << " Relative" << endl;
	listFile << " Address      Identifier" << endl;
	listFile << " --------     --------------------------------" 
		<< endl;
	for (unsigned i = 0; i < symbolTable_Vector.size(); i++)
	{
		listFile.width(7);
		listFile << 2*i << "       " << symbolTable_Vector[i] << endl;
	}
	listFile << " _____________________________________________" 
		<< endl;
	listFile << endl;
	listFile << " Normal successful compilation." << endl;
	listFile.close();
}

void CodeGen::Shout(Token type_used) {
	string s;

	if (!(symbolTable.EntryExists("DECS"))) {
			symbolTable.AddEntry("DECS",TYPE_CHEESE_LIT);
	}

	switch (type_used) {
		case CHEESE_LIT:
			s = scan.stringBuffer.data();
            WriteString(s);
			break;
		case INT_LIT:
		case FLOAT_LIT:
			IntToAlpha(atof(scan.tokenBuffer.data()), s);
            symbolTable.UpdateEntry("DECS",s);
            Shout_Variable("DECS");
			break;
	}
}

void CodeGen::Shout_Variable(std::string input_var) {
	DataEntry cur_entry = symbolTable.GetDataObject(input_var);

	switch (cur_entry.GetType()) {
		case TYPE_CHEESE_LIT:
			Generate("WRST      ", cur_entry.GetCurrentTempVar(), "");
			break;
		case TYPE_BOOL_LIT:
		case TYPE_INT_LIT:
			Generate("WRI       ", cur_entry.GetCurrentTempVar(), "");
			break;
		case TYPE_FLOAT_LIT:
			Generate("WRF       ", cur_entry.GetCurrentTempVar(), "");
			break;
	}
}

void CodeGen::Listen(std::string input_var) {
	symbolTable.UpdateEntry(input_var,"");

	DataEntry cur_entry = symbolTable.GetDataObject(input_var);

	switch (cur_entry.GetType()) {
		case TYPE_CHEESE_LIT:
            symbolTable.ReserveNewLabel(input_var);
            cur_entry = symbolTable.GetDataObject(input_var);
			Generate("RDST      ", cur_entry.GetCurrentTempVar(), "");
			break;
		case TYPE_BOOL_LIT:
		case TYPE_INT_LIT:
			Generate("RDI       ", cur_entry.GetCurrentTempVar(), "");
			break;
		case TYPE_FLOAT_LIT:
			Generate("RDF       ", cur_entry.GetCurrentTempVar(), "");
            Generate("RDNL       ", "", "");
			break;
	}
}

void CodeGen::GenInfix(const ExprRec & e1, const OpRec & op, 
                       const ExprRec & e2, ExprRec& e)
{
	string opnd;

	if (e1.kind == LITERAL_EXPR && e2.kind == LITERAL_EXPR)
	{
		e.kind = LITERAL_EXPR;
		switch (op.op)
		{
		case PLUS:
			e.val = e1.val + e2.val;
			break;
		case MINUS:
			e.val = e1.val - e2.val;
		}
	}
	else
	{
		e.kind = TEMP_EXPR;
		e.name = GetTemp();
		ExtractExpr(e1, opnd);
		Generate("LD        ", "R0", opnd);
		ExtractExpr(e2, opnd);
		Generate(ExtractOp(op), "R0", opnd);
		ExtractExpr(e, opnd);
		Generate("STO       ", "R0", opnd);
	}
}

void CodeGen::NewLine()
{
	Generate("WRNL      ", "", "");
}

void CodeGen::ProcessId(ExprRec& e)
{
	CheckId(scan.tokenBuffer);
	e.kind = ID_EXPR;
	e.name = scan.tokenBuffer;
}

void CodeGen::ProcessLiteral(ExprRec& e)
{
	e.kind = LITERAL_EXPR;
	e.val = atoi(scan.tokenBuffer.data());
	// cout << scan.tokenBuffer.data() << endl;
}

void CodeGen::ProcessOp(OpRec& o)
{
	if (scan.tokenBuffer == "+")
		o.op = PLUS;
	else
		o.op = MINUS;
}

void CodeGen::ReadId(const ExprRec & inVar)
{
	string s;

	ExtractExpr(inVar, s);
	Generate("RDI       ", s, "");
}

void CodeGen::Start()
{
	Generate("LDA       ", "R15", "VARS");
}

void CodeGen::WriteExpr(const ExprRec & outExpr)
{
	string s;

	ExtractExpr(outExpr, s);
	Generate("WRI       ", s, "");
}

void CodeGen::WriteString(string input)
{
	string s = "";
	for (int i = 0; i < input.length(); i++){

        if (input[i] == '\\' && i != input.length() - 1){
            if ( input[i + 1] == 'n') {
                cerr << s << endl;

                // symbolTable.UpdateEntry("DECS",s);
                // Shout_Variable("DECS");

                Generate("WRNL", "", "");
                i++;
                s = "";
            }
        }
        else {
            s += input[i];
        }
    }
    if (s.length()) {
        cerr << s << endl;
        symbolTable.UpdateEntry("DECS",s);
        Shout_Variable("DECS");
    }
}

void CodeGen::Assign_Var2Var(std::string target, std::string source) {
	DataEntry tar = symbolTable.GetDataObject(target);
	DataEntry sou = symbolTable.GetDataObject(source);

    if (sou.GetCurrentTempVar() == "") {
        symbolTable.UpdateEntry(source,"0");
    }
    if (tar.GetCurrentTempVar() == "") {
        symbolTable.UpdateEntry(target,"0");
    }
    tar = symbolTable.GetDataObject(target);
    sou = symbolTable.GetDataObject(source);

    if (tar.GetType() == TYPE_CHEESE_LIT) {
        symbolTable.ReserveNewLabel(target);
        tar = symbolTable.GetDataObject(target);
        Generate("LDA       ", "R0", sou.GetCurrentTempVar());
        Generate("LD        ", "R1", "#" + std::to_string(string_reservation_space));
        Generate("BKT       ", "R0", tar.GetCurrentTempVar());
    }
    else if (tar.GetType() == TYPE_FLOAT_LIT) {
        Generate("LDA       ", "R0", sou.GetCurrentTempVar());
        Generate("LD        ", "R1", "#4");
        Generate("BKT       ", "R0", tar.GetCurrentTempVar());
    }
    else {
        Generate("LD        ", "R0", sou.GetCurrentTempVar());
        Generate("STO       ", "R0", tar.GetCurrentTempVar());
    }
}

void CodeGen::ProcessOperation_SymbolTable(string id, string old_lbl, Token op_used) {
    string storage = "";
    switch (op_used) {
        case PLUS_OP:
            switch (symbolTable.GetDataObject(id).GetType()) {
                case TYPE_FLOAT_LIT:
                    Generate("LDA   ","R1",old_lbl);
                    Generate("LD    ","R7","+0(R1)");
                    Generate("LD    ","R8","+2(R1)");
                    Generate("FA    ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("LDA   ","R1",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("STO   ","R7","+0(R1)");
                    Generate("STO   ","R8","+2(R1)");
                    break;
                case TYPE_INT_LIT:
                    Generate("LD    ","R7",old_lbl);
                    Generate("IA    ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("STO   ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    break;
            }
            break;
        case MINUS_OP:
            switch (symbolTable.GetDataObject(id).GetType()) {
                case TYPE_FLOAT_LIT:
                    Generate("LDA   ","R1",old_lbl);
                    Generate("LD    ","R7","+0(R1)");
                    Generate("LD    ","R8","+2(R1)");
                    Generate("FS    ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("LDA   ","R1",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("STO   ","R7","+0(R1)");
                    Generate("STO   ","R8","+2(R1)");
                    break;
                case TYPE_INT_LIT:
                    Generate("LD    ","R7",old_lbl);
                    Generate("IS    ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("STO   ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    break;
            }
            break;
        case DIV_OP:
            switch (symbolTable.GetDataObject(id).GetType()) {
                case TYPE_FLOAT_LIT:
                    Generate("LDA   ","R1",old_lbl);
                    Generate("LD    ","R7","+0(R1)");
                    Generate("LD    ","R8","+2(R1)");
                    Generate("FD    ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("LDA   ","R1",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("STO   ","R7","+0(R1)");
                    Generate("STO   ","R8","+2(R1)");
                    break;
                case TYPE_INT_LIT:
                    Generate("LD    ","R7",old_lbl);
                    Generate("ID    ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("STO   ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    break;
            }
            break;
        case MULT_OP:
            switch (symbolTable.GetDataObject(id).GetType()) {
                case TYPE_FLOAT_LIT:
                    Generate("LDA   ","R1",old_lbl);
                    Generate("LD    ","R7","+0(R1)");
                    Generate("LD    ","R8","+2(R1)");
                    Generate("FM    ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("LDA   ","R1",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("STO   ","R7","+0(R1)");
                    Generate("STO   ","R8","+2(R1)");
                    break;
                case TYPE_INT_LIT:
                    Generate("LD    ","R7",old_lbl);
                    Generate("IM    ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    Generate("STO   ","R7",symbolTable.GetDataObject(id).GetCurrentTempVar());
                    break;
            }
            break;
        default:
            break;
    }
}

void CodeGen::Compare_Numbers(string lbl1, string lbl2, string jump_lbl, Token comp_op) {
	Generate("LD    ","R4",lbl1);
	Generate("LD    ","R5",lbl2);
	Generate("IC    ","R4","R5");
	switch (comp_op) {
		case LT_OP:
			Generate("JLT    ",jump_lbl,"");
			break;
		case LE_OP:
			Generate("JLE    ",jump_lbl,"");
			break;
		case GT_OP:
			Generate("JGT    ",jump_lbl,"");
			break;
		case GE_OP:
			Generate("JGE    ",jump_lbl,"");
			break;
		case EQ_OP1:
			Generate("JEQ    ",jump_lbl,"");
			break;
		case EQ_OP2:
			Generate("JEQ    ",jump_lbl,"");
			break;
		case NE_OP:
			Generate("JNE    ",jump_lbl,"");
			break;
	}
}

void CodeGen::CloseCondition(string condition_name) {
	Generate(symbolTable.GetCondObject(condition_name).GetAllCommands(),"","");
}

void CodeGen::Compare_Numbers_Else(string jump_lbl) {
	Generate("LABEL    ",jump_lbl,"");
}
