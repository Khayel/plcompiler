#ifndef PARSER_H
#define PARSER_H
#include "symbol.h"
#include "token.h"
#include "scanner.h"
#include "symtable.h"
#include "admin.h"
#include<stack>
class Parser {
  public:
  Parser(Scanner &sc, Admin &ad): scannerhandle(sc), adminhandle(ad) {Symtable i; blocktable.push(i);labelcount=0;};// parser constructor should initialize
   void match() ; // should consume the next token
   void Program();// in program when begin is seen inserta new ssymbol table in the block table before calling block
   Token  search(std::string lex); // searches all blocktables for  lexeme; returns the token
  private:
   struct tableEntry
   {
      int value;
      std::string lexeme;
      PL_type type;
      PL_kind kind;
      int arrsize;
   };
   int NewLabel(){ int tmp = labelcount; labelcount++; return tmp;};
   int labelcount;
   Token insert(tableEntry);//inserts values in the top of the blocktable
   std::stack<Symtable> blocktable;
   void syntaxError();
   void scopeError(Token t);
   void Block(int &startLabel, int &varLabel);
   int DefinitionPart();
   int  Definition(int &varStart);
   void ConstantDefinition();// properly inserts into the current block symboltable
   int VariableDefinition(int &varStart); // properly inserts into the current block symobl table with proper types
   int VD2(PL_type t, int &varStart);
   PL_type TypeSymbol();// returns the types of the variable list
   void VariableList(std::vector<tableEntry> &varlis);// fills variable defeinition tableentrys
   void VL2(std::vector<tableEntry> &varlis);
   void ProcedureDefinition();// identical to checks for program-> block except that the procname must be inserted in the current block//check blocks for the definition of the procedure in the closest enclosing block in the blocktable checkfor undefined nature
   void StatementPart();
   void SP2();
   void Statement();
   void EmptyStatement();
   void ReadStatement();
   void VariableAccessList(std::vector<PL_type> &val);//needs to return a vector of pltype objs corresponging to the variables in the list of variables in an assignment statement
   void VAL2(std::vector<PL_type> &val);//needs the vector that is to be returned
   void WriteStatement();
   void ExpressionList(std::vector<PL_type> &pltypes);//needs to return vector of pltype objects corresponding to the type of the expressions on the rhs of an assn statement.
   void EL2(std::vector<PL_type> &pltypes);
   void AssignmentStatement();//gets vectors from variableaccesslist and expressionlist. checks for the same vector size for parallel assignment
   void ProcedureStatement();//check the kind attributr of the name.. it should be procedure
   void IfStatement();
   void DoStatement();
   void GuardedCommandList(int &startLabel, int GoTo);
   void GCL2();
   void GuardedCommand(int &thisLabel, int GoTo);//verify that expression is a boolean
   PL_type Expression();//determine return and return type of expression form pe
   void E2(PL_type &t);
   Symbol PrimaryOperator();
   PL_type PrimaryExpression(); //return pltype
   void PE2(PL_type &t);
   Symbol RelationalOperator();
   PL_type SimpleExpression();//determine and return type of expression
   void Neg(PL_type &setype);
   void SE2(PL_type &setype);
   void SE3(PL_type &setype);
   Symbol AddingOperator();
   PL_type Term();//determine and return the type of term... show that type is integer??
   void T2(PL_type &t);
   Symbol MultiplyingOperator();
   PL_type Factor();//determine and return the type of factor,,, det and return the type ofvarname, ensure index selector is present is a type of integer
   PL_type VariableAccess(); // verify name exists and is correct type
   void VA2();
   PL_type IndexedSelector();
   void Constant(int & value, PL_type &type); 
   void Numeral();
   void BooleanSymbol();
   void Name(); // checks
   int matchName();//new function to fix ambiguity for names
   Token laTok;
   Scanner &scannerhandle;
   Admin &adminhandle;
  //should the parser be in the admin or main.....
//make sure to insert names in appropriate blocks
//check for multiply defined

};
#endif
