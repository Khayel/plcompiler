#ifndef SYMBOL_H
#define SYMBOL_H


enum Symbol {
  ID=256,NUM,WORD,DOT, //256-259
  COMMA,SQLEFT,SQRIGHT,AMPRSND,//260-263
  VLINE,TILDE,LESSTHAN,ASSIGNMENT,//264-267
  GREATERTHAN,PLUS,MINUS,TIMES,//268-271
  FSLASH,BSLASH,LEFTP,RIGHTP, //272-275
  COLEQ,SQ,ARROW,DOLLAR,//276-279
  LESSTHAN_EQ,GREATERTHAN_EQ,EQUALS,//280-282
  NONAME, EOFF, UNDERSCORE,SEMICOL, //283-286
  BAD_ID, BAD_NUMERAL, BAD_SYMBOL, BAD_CHAR, NEWLINE//287-290
};

enum PL_type{
   universal,integer,boolean};
enum PL_kind{
   undefined,variable,constant,procedure,array};


#endif

/*
//parser function implementations
#include "parser.h"
#include "scanner.h"
#include<iostream>
#include<stack>
void Parser::match(){
//   currTok = laTok;
   laTok = scannerhandle.nextToken();
   // std::cout<<"newlatok"<<laTok.getSymbol()<<laTok.getLexeme();
   while (laTok.getSymbol() == 291 || laTok.getSymbol() == 279 || laTok.getSymbol() == 283) // for now ignore newlines and comment
   {
      laTok = scannerhandle.nextToken();
   }
   
};
void Parser::syntaxError()
{
   std::cout<<"error";
   while(true)
   {
      if(laTok.getSymbol() == 286 || laTok.getSymbol() == 262 || laTok.getSymbol() == 259 || laTok.getSymbol() == 284 )
	  break;
       match();
       
   }
};
void Parser::Program()
{
      match();//get first token
   std::cout<<"Program -Token: "<<laTok.getLexeme()<<std::endl;
   std::cout<<laTok.getSymbol();
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "begin" ) // first block
   {
      Block();
      if(laTok.getSymbol() == 259)
      {
	 std::cout<<"End of file reached";
      }
      //next file should be end of file.
   }
   else
      std::cout<<"error at program"<<std::endl;
  void syntaxError(); //error
};

void Parser::Block()
{//when a new block is defined new btable for scope
   Symtable newbtable;
   blocktable.push(newbtable);
   
   std::cout<<"Block -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "begin") // begin
   {
      match(); // begin
      DefinitionPart();
      StatementPart();
      if(laTok.getSymbol() == 258 && laTok.getLexeme() == "end")
      {

	 match(); // end
	 blocktable.pop();
      }
      else
	 syntaxError();
   }
   else
      std::cout<<"error at block"<<std::endl;
};
void Parser::DefinitionPart()
{
   std::cout<<"DefinitionPart -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "const" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "integer"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "Boolean"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "proc")
   {
      DP2();
      
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "skip"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "read"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "write"||
	     laTok.getSymbol() == 258 && laTok.getLexeme() == "call" ||
	     laTok.getSymbol() == 258 && laTok.getLexeme() == "if"||
	     laTok.getSymbol() == 258 && laTok.getLexeme() == "do"||
	     laTok.getSymbol() == 258 && laTok.getLexeme() == "end"||
	   laTok.getSymbol() == 256)//epsilon so go to statementpart
   {
      
   }
   else
   {
      std::cout<<"defpart error"<<std::endl;
    void syntaxError();  //error
   }
};
void Parser::DP2()
{
   std::cout<<"DP2 -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "const" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "integer"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "Boolean"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "proc")
   {
      Definition();
      if(laTok.getSymbol() == 286) // ;
	 match();
      else
	 syntaxError();
      
      DP3();
      
   }
   else
  {
     std::cout<<"error at DP2"<<std::endl;
    void syntaxError(); //error
  }
};
void Parser::DP3()
{
   std::cout<<"DP3 -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "const" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "integer"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "Boolean"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "proc")
   {
      DP2();
      
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "skip" ||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "read"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "write"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "call"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "if"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "do"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "end"|| laTok.getSymbol() == 259 || // if there is no statementpart
      laTok.getSymbol() == 256)//epsilon //if after a definition can only have a statement or end
   {
      
   }
   else
    {std::cout<<"error at dp3"<<std::endl;
     void syntaxError();  //error
    }
};
void Parser::Definition()
{
   std::cout<<"Definition -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "const")
   {
      ConstantDefinition();
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "integer" ||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "Boolean")
   {
      VariableDefinition();
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "proc")
    {
       ProcedureDefinition();
    }
   else
   {
      std::cout<<"definition error"<<std::endl;
    void syntaxError();  //error
   }
};
void Parser::ConstantDefinition()
{
   std::cout<<"ConstantDefinition -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "const" )
   {
      match();//const
      
      Name(); // constant name
      if(laTok.getSymbol() == 267)
	 match(); // =
      else
	 syntaxError();
   
      Constant();
      
   }
   else
   {
      std::cout<<"error at constantdef"<<std::endl;
     void syntaxError(); //error
   }
};
void Parser::VariableDefinition()
{
   std::cout<<"VariableDefinition--"<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "integer" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "Boolean")
   {
      PL_type t = TypeSymbol();
      VD2(t);
    }
   else
   {
      std::cout<<"error at vardef"<<std::endl;
     void syntaxError(); //error
   }
};
void Parser::VD2(PL_type t)
{
   std::cout<<"VD2 -Token: "<<laTok.getSymbol()<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 256)// identifier
   {
      VariableList();
          
      
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "array")
   {
      match(); //array
      
      VariableList();
      if(laTok.getSymbol() == 261)
	 match(); //[
      else
	 syntaxError();
      
      Constant();
      
      if(laTok.getSymbol() == 262)
	 match(); // ]
      else syntaxError();
   }
   else
   {
     std::cout<<"error at vd2"<<std::endl;void syntaxError(); //error
   }
};
PL_type Parser::TypeSymbol()
{
   std::cout<<"TypeSymbol -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "integer")
   {
      
      match();
      return integer;
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "Boolean")
   {
      match();
      return boolean;
   }
   else
   {std::cout<<"error at type symbol"<<std::endl;
    void syntaxError();  //error
   }
};
void Parser::VariableList()//return vector of lexemes for variables ?
{
   std::cout<<"variablelist -Token: "<<laTok.getSymbol()<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 256) // name
   {
      //insert into symbol table here
      Name();
      VL2();
   }
   else
   {
     void syntaxError(); std::cout<<"error atvarlist"<<std::endl;//error
   }
};
void Parser::VL2()
{
   std::cout<<"vl2 -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 260)
   {
      match(); // ,
      VariableList();
   }
   else if(laTok.getSymbol() == 261 || laTok.getSymbol() == 286)//epsilon follow of Variablelist
   {
      //do nothing
   }
   else
   {
      std::cout<<"error at vl2"<<std::endl;
     void syntaxError(); //error
    }
};
void Parser::ProcedureDefinition()
{
   std::cout<<"proceduredefinition -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "proc")
   {
      match(); //proc
       std::cout<<"Inserting into symboltable"<<laTok.getLexeme()<<"  "<<laTok.getSymbol()<<std::endl;
      blocktable.top().insert(laTok); //insert into symbol table
      Name(); // procedure name
      Block();
   }
   else
   {
      std::cout<<"error at procdef"<<std::endl;
     void syntaxError(); //error
   }
};
void Parser::StatementPart()
{
   std::cout<<"statementpart -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "skip" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "read"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "write"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "call" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "if" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "do" || laTok.getSymbol() == 256)
   {
      SP2();
   }
   else if( laTok.getSymbol() == 259 || laTok.getSymbol() == 284 ||
	    (laTok.getSymbol() == 258 && laTok.getLexeme() == "end"))
   {
      // do nothing epsilon
   }
   else
      syntaxError();
										       
};
void Parser::SP2()
{
   std::cout<<"sp2 -Token: "<<laTok.getLexeme()<<std::endl;
  if(laTok.getSymbol() == 258 && laTok.getLexeme() == "skip" ||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "read"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "write"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "call"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "if"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "do"||
	   laTok.getSymbol() == 256)
   {
      Statement();
      if(laTok.getSymbol() == 286)
	 match(); //;
      else
	 syntaxError();
      
      SP3();
   }
   else
   {
      void syntaxError();  //error
   }
};
void Parser::SP3()
{
   std::cout<<"sp3 -Token: "<<laTok.getLexeme()<<laTok.getSymbol()<<std::endl;
   std::cout<<blocktable.top().search(laTok.getLexeme())<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "skip" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "read"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "write"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "call"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "if"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "do"||
      laTok.getSymbol() == 256)
   {
      SP2();
   }
   else if((laTok.getSymbol() == 258 && laTok.getLexeme() == "end") || (laTok.getSymbol() == 258 && laTok.getLexeme() == "fi") || (laTok.getSymbol() == 258 &&laTok.getLexeme() == "od" ))//epsilon
   {
      //do nothing
   }
   else
   {
    void syntaxError();  //error
   }
};
void Parser::Statement()
{
   std::cout<<"statement -Token: "<<laTok.getLexeme()<<laTok.getSymbol()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "skip")
   {
       EmptyStatement();
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "read")
   {
      ReadStatement();
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "write")
   {
      WriteStatement();
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "call")
   {
      ProcedureStatement();
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "if")
   {
      IfStatement();
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "do")
    {
       DoStatement();
    }
   else if(laTok.getSymbol() == 256)
   {
      AssignmentStatement();
   }
   else
   {
      //error
   }
};
void Parser::EmptyStatement()
{std::cout<<"emptystatement -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "skip")
   {
      match(); //skip
   }
   else
   {
     void syntaxError(); //error
   }
} ;
void Parser::ReadStatement()
{std::cout<<"readstatement -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "read")
   {
      match(); //read
      VariableAccessList();
   }
   else
   {
    void syntaxError();  //error
   }
};
void Parser::VariableAccessList()
{std::cout<<"variableaccesslist -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 256 ) //id
   {
      VariableAccess();
      VAL2();
   }
   else
   {
     void syntaxError(); //error
   }
};
void Parser::VAL2()
{std::cout<<"val2 -Token: "<<laTok.getLexeme()<<laTok.getSymbol()<<std::endl;
   if(laTok.getSymbol() == 260)// comma
   {
      match(); // ,
      VariableAccessList();
   }
   else if(laTok.getSymbol() == 276 || laTok.getSymbol() == 286 )//epsilon????? colequals // semicolon
    {
    }
   else
   {
   void syntaxError();   //error
   }
};

void Parser::ExpressionList()
{std::cout<<"expressionlist -Token: "<<laTok.getLexeme()<<std::endl;
   //- 270,num257,true258,false258,id256, (274, ~265
   if(laTok.getSymbol() == 270 || laTok.getSymbol() == 257||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "true") ||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "false")||
      laTok.getSymbol() == 256 || laTok.getSymbol() == 274|
      laTok.getSymbol() == 265)
   {
      Expression();
      std::cout<<"calling el2";
      EL2();
   }
  else
  {
  void syntaxError();  //error
  }
};
void Parser::WriteStatement()
{std::cout<<"writestatement -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "write")
   {
      match(); //write
      ExpressionList();
   }
   else
   {
    void syntaxError();  //error
   }
};
void Parser::EL2()
{std::cout<<"El2 -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 260)
   {
      match(); // ,
      ExpressionList();
    }
   else if(laTok.getSymbol() == 286)//epsilon // semicolon
   {
   }
   else
    {
      void syntaxError(); //error
    }
};
void Parser::AssignmentStatement()
{std::cout<<"Assignmentstatement -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 256) // id
   {
      VariableAccessList();
      if(laTok.getSymbol() == 276)
	 match(); // :=
      else
	 syntaxError();
      
      ExpressionList();
   }
   else
   {
     void syntaxError(); //error
   }
};
void Parser::ProcedureStatement()
{
   std::cout<<"procedurestatement -Token: "<<laTok.getLexeme()<<std::endl;
   
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "call")
   {
      match();//call
	 Name(); // Procedure Name
      
      }
   else
   {
    void syntaxError();  //error
   }
};
void Parser::IfStatement()
{std::cout<<"ifstatement -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "if")
   {
      match(); //if
      GuardedCommandList();std::cout<<"in if statement";
      if(laTok.getSymbol() == 258 && laTok.getLexeme() == "fi")
	 match(); //fi
      else
	 syntaxError();
   }
   else
   {
    void syntaxError();  //error
   }
};
void Parser::DoStatement()
{std::cout<<"dostatement-"<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "do")
    {std::cout<<"do token";
       match(); // do
       GuardedCommandList();
       if(laTok.getSymbol() == 258 && laTok.getLexeme() == "od")
	   match(); // od
	else
	   syntaxError();
    }
    else
    {
      void syntaxError(); //error
    }
};
void Parser::GuardedCommandList()
{std::cout<<"guardedcommandlist -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 270 || laTok.getSymbol() == 257||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "true") ||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "false")||
      laTok.getSymbol() == 256 || laTok.getSymbol() == 274|
      laTok.getSymbol() == 265)
   {
      GuardedCommand();
      GCL2();
      std::cout<<"DONE GCL";
   }
   else
   {
     void syntaxError(); //error
   }
};
void Parser::GCL2()
{std::cout<<"gcl2 -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 277) //[]
   {
      match();//[]
      GuardedCommandList();
   }
   else if((laTok.getSymbol() == 258 && laTok.getLexeme() == "fi") || (laTok.getSymbol() == 258 &&laTok.getLexeme() == "od" ))//epsilon
   {
   }
   else
    {
      void syntaxError(); //error
    }
};
void Parser::GuardedCommand()
{std::cout<<"guardedcommand -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 270 || laTok.getSymbol() == 257||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "true") ||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "false")||
      laTok.getSymbol() == 256 || laTok.getSymbol() == 274|
      laTok.getSymbol() == 265)
    {
       Expression();
       if(laTok.getSymbol() == 278)
	   match(); //->
       else
	  syntaxError();
       
       StatementPart();
    }
    else
    {
   void syntaxError(); //error
    }
};
void Parser::Expression()
{std::cout<<"expression -Token: "<<laTok.getLexeme()<<std::endl;
    if(laTok.getSymbol() == 270 || laTok.getSymbol() == 257||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "true") ||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "false")||
      laTok.getSymbol() == 256 || laTok.getSymbol() == 274|
      laTok.getSymbol() == 265)
    {
       PrimaryExpression();
       E2();
    }
    else
    {
     void syntaxError();  //error
    }
};
void Parser::E2()
{std::cout<<"e2 -Token: "<<laTok.getLexeme()<<laTok.getSymbol()<<std::endl;
   // &, |
   if(laTok.getSymbol() == 263 || laTok.getSymbol() == 264)
   {
       PrimaryOperator();
       Expression();
   }
   // ) , ], ->, , , ;
   else if(laTok.getSymbol() == 275 || laTok.getSymbol() == 262 || laTok.getSymbol() == 278 ||
	   laTok.getSymbol() == 260 || laTok.getSymbol() == 286)//epsilon //261 added
   {
      //only one expression.
   }
  else
  {
     std::cout<<"e2 err";
   void syntaxError(); //error
    }
};
void Parser::PrimaryOperator()
{std::cout<<"primaryoperator -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 263)
    {
       match(); //&
    }
   else if(laTok.getSymbol() == 264)
    {
       match(); // |
    }
  else
    {
   void syntaxError(); //error
    }
};
void Parser::PrimaryExpression()
{std::cout<<"primaryexpression -Token: "<<laTok.getLexeme()<<std::endl;
    if(laTok.getSymbol() == 270 || laTok.getSymbol() == 257||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "true") ||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "false")||
      laTok.getSymbol() == 256 || laTok.getSymbol() == 274|
       laTok.getSymbol() == 265)
    {
       SimpleExpression();
       PE2();
    }
  else
    {
   void syntaxError(); //error
    }
};
void Parser::PE2()
{std::cout<<"pe2 -Token: "<<laTok.getLexeme()<<std::endl;// < = >  <= ==maybenotnecessary   =>
   if(laTok.getSymbol() == 266 || laTok.getSymbol() == 267 ||
      laTok.getSymbol() == 268 || laTok.getSymbol() == 280 ||
      laTok.getSymbol() == 281 || laTok.getSymbol() == 282)
    {
       RelationalOperator();
       SimpleExpression();
       
    }
    else if(laTok.getSymbol() == 275 || laTok.getSymbol() == 262 || laTok.getSymbol() == 278 ||
	    laTok.getSymbol() == 263 || laTok.getSymbol() == 286 || laTok.getSymbol() == 263 ||
	    laTok.getSymbol() == 264 || laTok.getSymbol() == 260)//added COMMA//epsilon //same as eps of e2 but added primary operator first set
    {
    }
  else
  {
     std::cout<<"pe2 error";
    void syntaxError();//error
    }
};
void Parser::RelationalOperator()
{std::cout<<"relationaloperator -Token: "<<laTok.getLexeme()<<std::endl;
   if (laTok.getSymbol() == 266 || laTok.getSymbol() == 267 ||
      laTok.getSymbol() == 268 || laTok.getSymbol() == 280 ||
       laTok.getSymbol() == 281 || laTok.getSymbol() == 282)
   {
      match();
   }
  else
    {
   void syntaxError(); //error
    }
};
void Parser::SimpleExpression()
{std::cout<<"simpleexpression -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 270 ||laTok.getSymbol() == 257 ||
      laTok.getSymbol() == 258 ||laTok.getSymbol() == 258 ||
      laTok.getSymbol() == 256 ||laTok.getSymbol() == 274 ||
      laTok.getSymbol() == 265)// - or num true false id  id ( ~)
    {
       Neg();
       SE2();
    }
  else
    {
   void syntaxError(); //error
    }
};
void Parser::Neg()
{std::cout<<"neg-"<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 270)
    {
       match(); // -
    }
   else if(laTok.getSymbol() == 257 ||laTok.getSymbol() == 258 ||
	   laTok.getSymbol() == 258 ||laTok.getSymbol() == 256 ||
	   laTok.getSymbol() == 274 ||laTok.getSymbol() == 265)//epsilon
    {
    }
  else
    {
    void syntaxError();//error
    }
};
void Parser::SE2()
{std::cout<<"se2 -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 257 ||laTok.getSymbol() == 258 ||
      laTok.getSymbol() == 258 ||laTok.getSymbol() == 256 ||
      laTok.getSymbol() == 274 ||laTok.getSymbol() == 265)
    {
       Term();
       SE3();
    }
  else
    {
   void syntaxError(); //error
    }
};
void Parser::SE3()
{std::cout<<"se3 -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 269 || laTok.getSymbol() == 270)
   {
      AddingOperator();
      SE2();
   }
   else if(//relops primops -> , ; adding ops, ]??
      laTok.getSymbol() == 266 || laTok.getSymbol() == 267 || laTok.getSymbol() == 268 ||
      laTok.getSymbol() == 280 || laTok.getSymbol() == 281 || laTok.getSymbol() == 282  ||
      laTok.getSymbol() == 263 || laTok.getSymbol() == 264 || laTok.getSymbol() == 278 ||
      laTok.getSymbol() == 260 || laTok.getSymbol() == 286 || laTok.getSymbol() == 269 ||
      laTok.getSymbol() == 270 || laTok.getSymbol() == 261 || laTok.getSymbol() == 260 ||
      laTok.getSymbol() == 262 || laTok.getSymbol() == 275)// 262 IS ] -Token: // 275 is ) -Token:    //commadsadj)//epsilon
   {
    }
  else
  {
     std::cout<<"se3 error";
    void syntaxError();//error
    }
};
void Parser::AddingOperator()
{std::cout<<"addingoperator -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 269)
    {
       match(); // +
    }
   else if(laTok.getSymbol() == 270)
    {
       match(); // -
    }
    else
    {
    void syntaxError();   //error
    }
};
void Parser::Term()
{std::cout<<"term -Token: "<<laTok.getLexeme()<<std::endl;
   if(// num true false id ( ~
      laTok.getSymbol() == 257 ||laTok.getSymbol() == 258 ||laTok.getSymbol() == 258 ||
      laTok.getSymbol() == 256 ||laTok.getSymbol() == 274 ||laTok.getSymbol() == 265)
   {
      Factor();
      T2();
   }
   else
   {
    void syntaxError();  //error
   }
};
void Parser::T2()
{std::cout<<"t2"<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 271 || laTok.getSymbol() == 272 || laTok.getSymbol() == 273)
   {
      MultiplyingOperator();
      Term();
   }
   else if(//addind ops  rel ops    prim ope - > ,  ;
      laTok.getSymbol() == 269 ||laTok.getSymbol() == 270 || //addingops
      laTok.getSymbol() == 266 ||laTok.getSymbol() == 267 ||laTok.getSymbol() == 268 ||
      laTok.getSymbol() == 280|| laTok.getSymbol() == 281 ||laTok.getSymbol() == 282 || // relops
      laTok.getSymbol() == 263 ||laTok.getSymbol() == 264 || // primops
      laTok.getSymbol() == 278 ||laTok.getSymbol() == 260||laTok.getSymbol() ==286) // -> , ;
//epsilon
   {
   }
   else
   {
    void syntaxError();  //error
   }
};
void Parser::MultiplyingOperator()
{
   std::cout<<"multiplying operator -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 271 || laTok.getSymbol() == 272 || laTok.getSymbol() == 273)
      match();// * / \
   else
      void syntaxError();
};
void Parser::Factor()
{std::cout<<"factor -Token: "<<laTok.getLexeme()<<std::endl;
   //256 need to check whether id is a constant name or a variable name  instructions to ignore....
   if(laTok.getSymbol() == 257 || laTok.getSymbol() == 258 ||
      (laTok.getSymbol() == 256 && laTok.getNameKind() == 1) )
   {
        Constant();
   }
   else if(laTok.getSymbol() == 274)
   {
      match(); // (
      Expression();
      if(laTok.getSymbol() == 275)
	 match(); //)
      else
	 syntaxError();
   }
   else if(laTok.getSymbol() == 256)
   {
      std::cout<<"variable access";
      VariableAccess();
   }
   
   else if(laTok.getSymbol() == 265)
   {
      match(); // ~
      Factor();
   }
   else
   {
     void syntaxError(); //error
   }
};
void Parser::VariableAccess()
{std::cout<<"variableaccess -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 256)
   {
      Name();
      std::cout<<"calling va2";
      VA2();
   }
   else
   {
     void syntaxError(); //error
   }
};
void Parser::VA2()
{std::cout<<"va2 -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 261)
   {
      IndexedSelector();
   }
   else if(//addind ops  rel ops    prim ope - > ,  and multiplying ops ; ]
      laTok.getSymbol() == 269 ||laTok.getSymbol() == 270 ||laTok.getSymbol() == 266 ||
      laTok.getSymbol() == 267 ||laTok.getSymbol() == 268 ||laTok.getSymbol() == 280||
      laTok.getSymbol() == 281 ||laTok.getSymbol() == 282 ||laTok.getSymbol() == 263 ||
      laTok.getSymbol() == 264 ||laTok.getSymbol() == 278 ||laTok.getSymbol() == 260||
      laTok.getSymbol() ==286 || laTok.getSymbol() == 271 ||laTok.getSymbol() == 272 ||
      laTok.getSymbol() == 273 || laTok.getSymbol() == 261)//epsilon
   {
   }
   else
   {
    void syntaxError();  //error
   }
};
void Parser::IndexedSelector()
{std::cout<<"IndexedSelector -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 261)
   {
      match(); //[
      Expression();
      if(laTok.getSymbol() == 262)
	 match(); //]
      else
	 syntaxError();
   }
   else
   {
     void syntaxError(); //error
   }
};
void Parser::Constant()
{std::cout<<"Constant -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 257)
   {
      Numeral();
   }
   else if(laTok.getSymbol() == 258)
   {
      BooleanSymbol();
   }
   else if(laTok.getSymbol() == 256)
   {
      Name(); // constant name
   }
   else
   {
     void syntaxError(); //error
   }
};
void Parser::Numeral()
{std::cout<<"Numeral -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 257)
   {
      match(); ///? numtoken
	 }
   else
   {
    void syntaxError();  //error
   }
};
void Parser::BooleanSymbol()
{std::cout<<"BooleanSymbol -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && (laTok.getLexeme() == "true" || laTok.getLexeme() == "false"))
   {
      match(); //true
   }
   else
   {
    void syntaxError();  //error
   }
};


void Parser::Name()
{
   std::cout<<"Name -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 256)
      match();
   else
      syntaxError();
}

int Parser::matchName(std::vector<Symbol> s)
{
   int temp = -1;
   while(laTok.getSymbol() == 291 || laTok.getSymbol() == 279)
   {
      laTok = scannerhandle.nextToken();
   }//get rid of empty lines
   if(laTok.getSymbol() == 256)
   {
      temp = laTok.getId();
      laTok = scannerhandle.nextToken();
   }
   return temp;
};
*/

