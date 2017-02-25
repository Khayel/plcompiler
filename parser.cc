//parser function implementations
#include "parser.h"
#include "scanner.h"
#include<iostream>
#include<stack>
void Parser::match(){

   laTok = scannerhandle.nextToken();
   adminhandle.scan(laTok);
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

Token Parser::search(std::string lex)
{ 
   Token foundToken;
   std::stack<Symtable> tmp;
   int found; // if not -1 then found
   for(int i =0; i <blocktable.size(); i++)
   {
      Symtable a = blocktable.top();
      blocktable.pop();
      found = a.search(lex);
      if(found != -1)
      {
	 //std::cout<<"found";
	 foundToken = a.at(found);
	 break;
      }
      tmp.push(a);
      if(blocktable.empty())
      {
	 //std::cout<<"not found";
	 break;
      }
   }
   for(int i = 0 ; i < tmp.size(); i++)
   {
      blocktable.push(tmp.top());
      tmp.pop();
   }
   if(found == -1)
   {  Token notfound;
      return notfound;
   };
   return foundToken;
};
Token Parser::insert(tableEntry x)
{
   Token newTok(ID, 0, x.lexeme);
   newTok.setValue(x.value);
   newTok.setPL_type(x.type);
   newTok.setNameKind(x.kind);
   newTok.setArrsize(x.arrsize);
   newTok.setBlocklvl(blocktable.size()-1);
   if(blocktable.top().search(x.lexeme) != -1)//check if existing
   {
      std::cout<<"Identifier "<<x.lexeme<<" has been previously defined."<<std::endl;
      return newTok;
   }
/*  For arrays must allocat proper space
   if (newTok.getArrsize() > 1)
   {
      for(int i = 0 i < newTok.getArrsize(); i++)
      {
	     }
   };*/

   
   int index = blocktable.top().insert(newTok);

   Token insertedtoken = blocktable.top().at(index);
   std::cout<<"========================="<<std::endl
	    <<"SYMBOL TABLE INSERTION REPORT"<<std::endl
	    <<"Attributes of id inserted"<<std::endl
	    <<"Symbol: "<<insertedtoken.getSymbol()<<std::endl
	    <<"Lexeme: "<<insertedtoken.getLexeme()<<std::endl
	    <<"Value: "<<insertedtoken.getValue()<<std::endl
	    <<"PL_type and PL_kind"<<insertedtoken.getPL_type()
	    <<"  "<<insertedtoken.getNameKind()<<std::endl
	    <<"ID: "<<insertedtoken.getId()<<std::endl
	    <<"arrsize"<<insertedtoken.getArrsize()<<std::endl
	    <<"========================"<<std::endl;
   return insertedtoken;
};

void Parser::scopeError(Token t)
{
   std::cout<<"Scope Error: "<<t.getLexeme()<<" is an existing identifier.";

};
void Parser::Program()
{
      match();//get first token
   //std::cout<<"Program -Token: "<<laTok.getLexeme()<<std::endl;
   //std::cout<<laTok.getSymbol();
   
   ////////////////////////////////////////codegeneration code
   int startLabel = NewLabel(); // first address of program
   int varLabel = NewLabel(); // length of vars defined here
     adminhandle.emit3("PROG", varLabel, startLabel); //
   ////////////////////////////////////////////////

   
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "begin" ) // first block
   {
      Block(startLabel, varLabel);
      if(laTok.getSymbol() == 259)
      {
	 std::cout<<"End of file reached";
      }
      
      //next file should be end of file. emit endprog
      adminhandle.emit1("ENDPROG");
   }
   else
      std::cout<<"error at program"<<std::endl;
  void syntaxError(); //error
};

void Parser::Block(int &startLabel, int &varLabel)  ////////////////
{//when a new block is defined new btable for scope

   
   int varLength = 0; // determined by definition pary
   

   
   Symtable newbtable;
   blocktable.push(newbtable);
   
   //std::cout<<"Block -Token: "<<laTok.getLexeme()<<laTok.getSymbol()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "begin") // begin
   {
      match(); // begin

      varLength = DefinitionPart(); // number of definition to store

      /*define proc and prog labels
	output DEFARG to enter
	labelTable[vLabel] = varLength in pass1
	so that varLength replaces varLabel in the final
	code output in pass 2 of assembler
      */
      adminhandle.emit3("DEFARG",varLabel,varLength); // indicate space for vars

      adminhandle.emit2("DEFADDR",startLabel); //indicate first instruction 

      
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
int Parser::DefinitionPart()
{
   //need to get total storage of vars declared in this block
   int varLength = 0;
   //std::cout<<"DefinitionPart -Token: "<<laTok.getLexeme()<<std::endl; // if a first definition exists.. enter while loop for ALL definitions
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "const" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "integer"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "Boolean"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "proc")
   {


      int nextvarstart =3; //offset for dynamic link, static link, and ret addr
      while(laTok.getSymbol() == 258 && laTok.getLexeme() == "const" ||
	    laTok.getSymbol() == 258 && laTok.getLexeme() == "integer"||
	    laTok.getSymbol() == 258 && laTok.getLexeme() == "Boolean"||
	    laTok.getSymbol() == 258 && laTok.getLexeme() == "proc")
      {
	 varLength += Definition(nextvarstart);
	 if(laTok.getSymbol() == 286) // ;
	    match();
	 else
	    syntaxError();
      }
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "skip" ||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "read"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "write"||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "call" ||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "if" ||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "do" || laTok.getSymbol() == 256)
   {
      //no defpart do nothing and go to statementpart
   }
   else
   {
      //std::cout<<"defpart error"<<std::endl;
      void syntaxError();  //error
   }
   return varLength;
};
int Parser::Definition(int &varStart)
{
   //return 0 
   //std::cout<<"Definition -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "const")
   {
      ConstantDefinition();
      return 0;
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "integer" ||
	   laTok.getSymbol() == 258 && laTok.getLexeme() == "Boolean")
   {
     return VariableDefinition(varStart);
   }
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "proc")
    {
       ProcedureDefinition();
       return 0;
    }
   else
   {
      //std::cout<<"definition error"<<std::endl;
    void syntaxError();  //error
   }
};
void Parser::ConstantDefinition()
{
   ////first match the const word token, then start to build a  table entry constant object which will be inserted at the top of the blocktable. set the latoken's kind to be constant, for name check, and then get the latokens attributes and place it to the tableentry
   //then check if the variable has already been declared.
   //after, match the name  and the = token, then determine the tableentry's type and value based on the token after the =.
   //if the token is a number token then the constant is an integer,
   //if the token is a word token with lexeme true or false then the constant is of type constant
   //if the token is another identifier, verify the id  already exists and get its value and type
   //after the tableentry object is filled insert the table entry struct into the symbol table.
   //std::cout<<"ConstantDefinition -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "const" )
   {
      match();//const
      tableEntry constantObject;
      constantObject.arrsize = 1;
      laTok.setNameKind(constant);//set the latoken to be a constant kind so in name proper things can be done..
      constantObject.kind = constant;
      constantObject.lexeme = laTok.getLexeme();
      if(blocktable.top().search(laTok.getLexeme()) != -1)
	 std::cout<<"The variable has been previously defined."<<std::endl;
      
	 matchName();
	 if(laTok.getSymbol() == 267)
	    match(); // =
	 else
	    syntaxError();
      int constval;
      PL_type consttype;
      //set token with proper values for token to be inserted
      Constant(constval, consttype);// get from constant

      constantObject.value = constval;
      constantObject.type = consttype;
      if( blocktable.top().search(constantObject.lexeme)== -1)
      {
	 insert(constantObject); 
      }
      else
      {//error already exists
      }     
   
   }
   else
   {
      //std::cout<<"error at constantdef"<<std::endl;
      void syntaxError(); //error
   }
};
int Parser::VariableDefinition(int &varStart)
{
   //std::cout<<"VariableDefinition--"<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "integer" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "Boolean")
   {
      PL_type t = TypeSymbol();
     return VD2(t,varStart);
    }
   else
   {
      //std::cout<<"error at vardef"<<std::endl;
     void syntaxError(); //error
   }
};



int Parser::VD2(PL_type t, int &varStart)
{
   //std::cout<<"VD2 -Token: "<<laTok.getSymbol()<<laTok.getLexeme()<<std::endl;
   //need to get list of ids returned by varlist....using the tableentry struct
   std::vector<int> listofids;
   std::vector<tableEntry> variableObjects;
   if(laTok.getSymbol() == 256)// identifier
   {
      VariableList(variableObjects); // variable objects is filled.
      Token id;
      for(int i = 0 ; i < variableObjects.size(); i ++)
      {
	 variableObjects[i].type = t;
	 variableObjects[i].arrsize = 1;
	 variableObjects[i].kind = variable;
	 id = insert(variableObjects[i]);
	 listofids.push_back(id.getId());
	 std::cout<<listofids[i];
	 
      }
      //need to define each one of them in the blocktable with DISPLACEMENT
      //if(/*ambigious definition*/)
      // scopeError();
      varStart++;
      return listofids.size(); 
      
   }
   
   else if(laTok.getSymbol() == 258 && laTok.getLexeme() == "array")
   {
      std::vector<tableEntry> arrayObjects;
      match(); //array
      
      VariableList(arrayObjects);
      
      //need to set kind to be variables 
      if(laTok.getSymbol() == 261)
	 match(); //[
      else
	 syntaxError();
      int arrval;
      PL_type constanttype;

      
      Constant(arrval, constanttype);//verify that the number is a valid array size >0 and an integer
  
	 
	 
      if(laTok.getSymbol() == 262)
	 match(); // ]
      else
	 syntaxError();

      
      if((arrval > 0) && (constanttype == integer))// if the constant type was valid then you can insert the array objects other wise you can't
      {
	 //arrids is vector of ids for the arrays. when inserting objects into btable add the id in the arrids list... a list of variables can only have one array size so for every array variable you incremenrvarstart by the array value....  
	 std::vector<int> arrids;
	 Token arrid;
     
	 for(int i = 0 ; i < arrayObjects.size(); i ++)
	 {
	    arrayObjects[i].kind = array;
	    arrayObjects[i].type = t;
	    arrayObjects[i].arrsize =arrval;
	    arrid = insert(arrayObjects[i]);
	    arrids.push_back(arrid.getId());
	    varStart +=arrval; // array size varstart
	 }
	 ///returning the displacement
	 return arrids.size() *arrval;
      }
      
   }
   else
   {
      //std::cout<<"error at vd2"<<std::endl;
      syntaxError(); //error
   }
};
PL_type Parser::TypeSymbol()
{
   //std::cout<<"TypeSymbol -Token: "<<laTok.getLexeme()<<std::endl;
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
   {//std::cout<<"error at type symbol"<<std::endl;
      void syntaxError();  //error
   }
};
void  Parser::VariableList(std::vector<tableEntry> &varlist)
{
   //std::cout<<"variablelist -Token: "<<laTok.getSymbol()<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 256) // name
   {
      tableEntry var;
      var.value = laTok.getValue();//not needed
      var.lexeme = laTok.getLexeme();
      varlist.push_back(var);

      matchName();
      
      VL2(varlist);
   }
   else
   {
      syntaxError();
      //std::cout<<"error atvarlist"<<std::endl;//error
   }
};
void Parser::VL2(std::vector<tableEntry> &varlist)
{
   //std::cout<<"vl2 -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 260)
   {
      match(); // ,
      VariableList(varlist);
   }
   else if(laTok.getSymbol() == 261 || laTok.getSymbol() == 286)//epsilon follow of Variablelist
   {
      //do nothing
   }
   else
   {
      //std::cout<<"error at vl2"<<std::endl;
      void syntaxError(); //error
    }
};
void Parser::ProcedureDefinition()
{
   //std::cout<<"proceduredefinition -Token: "<<laTok.getLexeme()<<std::endl;
   int procLabel = NewLabel();
   int varLabel = NewLabel();
   int startLabel = NewLabel();
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "proc")
   {
      match(); //proc
      tableEntry procedureName;
      procedureName.value = 0;
      procedureName.type = universal; //>?
      procedureName.kind = procedure;
      procedureName.arrsize = 1;
      
      std::cout<<"Inserting into symboltable"<<laTok.getLexeme()<<"  "<<laTok.getSymbol()<<std::endl;
      if(blocktable.top().search(laTok.getLexeme()) != -1)
	 std::cout<<"The identifier has been previously defined."<<std::endl;
      else
	 blocktable.top().insert(laTok); //insert into symbol table
      matchName(); // procedure name
      adminhandle.emit2("DEFADDR", procLabel);
      adminhandle.emit3("PROC", varLabel, startLabel);
      Block(startLabel,varLabel);
      adminhandle.emit1("ENDPROC");
      //end the block.. 
   }
   else
   {
      //std::cout<<"error at procdef"<<std::endl;
     void syntaxError(); //error
   }
};
void Parser::StatementPart()
{
   //std::cout<<"statementpart -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "skip" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "read"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "write"||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "call" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "if" ||
      laTok.getSymbol() == 258 && laTok.getLexeme() == "do" || laTok.getSymbol() == 256)
   {
      while(laTok.getSymbol() == 258 && laTok.getLexeme() == "skip" ||
	    laTok.getSymbol() == 258 && laTok.getLexeme() == "read"||
	    laTok.getSymbol() == 258 && laTok.getLexeme() == "write"||
	    laTok.getSymbol() == 258 && laTok.getLexeme() == "call" ||
	    laTok.getSymbol() == 258 && laTok.getLexeme() == "if" ||
	    laTok.getSymbol() == 258 && laTok.getLexeme() == "do" || laTok.getSymbol() == 256)
      {
	 
	 Statement();
	 if(laTok.getSymbol() == 286)
	    match();
	 else 
	    syntaxError();
      }
   }
   else if( laTok.getSymbol() == 259 || laTok.getSymbol() == 284 ||
	    (laTok.getSymbol() == 258 && laTok.getLexeme() == "end"))
   {
   }
   else
      syntaxError();
};
void Parser::Statement()
{
   //std::cout<<"statement -Token: "<<laTok.getLexeme()<<laTok.getSymbol()<<std::endl;
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
{//std::cout<<"emptystatement -Token: "<<laTok.getLexeme()<<std::endl;
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
{//std::cout<<"readstatement -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "read")
   {std::vector<PL_type> tmp;
      match(); //read
      VariableAccessList(tmp);
      adminhandle.emit2("READ", tmp.size());
      //output vector
   }
   else
   {
    void syntaxError();  //error
   }
};
void Parser::VariableAccessList(std::vector<PL_type> &val)
{//std::cout<<"variableaccesslist -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 256 ) //id
   {
      val.push_back(VariableAccess()); //va returns pl type of existing var
      VAL2(val);
   }
   else
   {
     void syntaxError(); //error
   }
};
void Parser::VAL2(std::vector<PL_type> &val)
{//std::cout<<"val2 -Token: "<<laTok.getLexeme()<<laTok.getSymbol()<<std::endl;
   if(laTok.getSymbol() == 260)// comma
   {
      match(); // ,
     VariableAccessList(val);
   }
   else if(laTok.getSymbol() == 276 || laTok.getSymbol() == 286 )//epsilon????? colequals // semicolon
    {
    }
   else
   {
   void syntaxError();   //error
   }
};

void Parser::ExpressionList(std::vector<PL_type> &pltypes)
{//std::cout<<"expressionlist -Token: "<<laTok.getLexeme()<<std::endl;
   //- 270,num257,true258,false258,id256, (274, ~265
   if(laTok.getSymbol() == 270 || laTok.getSymbol() == 257||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "true") ||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "false")||
      laTok.getSymbol() == 256 || laTok.getSymbol() == 274|
      laTok.getSymbol() == 265)
   {
      pltypes.push_back(Expression());
      EL2(pltypes);
   }
  else
  {
  void syntaxError();  //error
  }
};
void Parser::WriteStatement()
{//std::cout<<"writestatement -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "write")
   {
      match(); //write
      std::vector<PL_type> tmp;
      ExpressionList(tmp);
      adminhandle.emit2("WRITE",tmp.size());
   }
   else
   {
    void syntaxError();  //error
   }
};
void Parser::EL2(std::vector<PL_type> &pltypes)
{//std::cout<<"El2 -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 260)
   {
      match(); // ,
      ExpressionList(pltypes);
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
{//std::cout<<"Assignmentstatement -Token: "<<laTok.getLexeme()<<std::endl;
   
   if(laTok.getSymbol() == 256) // id
   {
      std::vector<PL_type> pltypesv;// pltypes of the list of variables to access
      //need to verify these are variables
      std::vector<PL_type> pltypese;//pltypes of the list of expressions
      //need to verify both vectors are the same size and match types
      VariableAccessList(pltypesv);
     

      
      if(laTok.getSymbol() == 276)
	 match(); // :=
      else
	 syntaxError();
      std::cout<<"======================="<<std::endl
	       <<"assignment statement vectors"<<std::endl
	       <<"NUMBER OF PLTYPES  VAL "<<pltypesv.size()<<std::endl;
      for(int i = 0 ; i < pltypesv.size(); i++)
      {
	 if(pltypesv[i] == 1)
	    std::cout<<"integer,";
	 else if(pltypesv[i] == 2)
	    std::cout<<"boolean,";
	 else
	    std::cout<<"universal";
      }
      std::cout<<std::endl;
      
      ExpressionList(pltypese); // need to get the right values
      std::cout<<"NUMBER OF PLTYPES EXPLIST"<<pltypese.size()<<std::endl;
        for(int i = 0 ; i < pltypesv.size(); i++)
	{
	 if(pltypese[i] == 1)
	    std::cout<<"integer,";
	 else if(pltypese[i] == 2)
	    std::cout<<"boolean,";
	 else
	    std::cout<<"universl";
	 std::cout<<std::endl;
	}
	std::cout<<"======================="<<std::endl;
	//type and scope checks
	if(pltypesv.size() != pltypese.size()) //if not equal size error
	{
	   if(pltypesv.size() > pltypese.size())
	      std::cout<<"Not enough variables in the left hand side."<<std::endl;
	   else
	      std::cout<<"Not enough expressions in the right hand side."<<std::endl;
	}
	else // evaluate types. they should match
	{
	   for(int i = 0; i < pltypesv.size(); i++)
	   {
	      if(pltypese[i] != pltypesv[i])// types do not match
		 std::cout<<"A variable and it's corresponding expression  types do not match."<<std::endl;
	   }
	   
	}
	   
	adminhandle.emit2("ASSIGN",pltypesv.size());
   }
   else
   {
     void syntaxError(); //error
   }
};
void Parser::ProcedureStatement()
{
   //std::cout<<"procedurestatement -Token: "<<laTok.getLexeme()<<std::endl;
   
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "call")
   {
      match();//call
      if(laTok.getSymbol() == 256)
      {// need to search for it not insert.../////////////////////////////////////////
	 tableEntry procobj;
	 procobj.value = laTok.getValue();
	 procobj.type = universal;
	 procobj.kind = procedure;
	 insert(procobj);
	 matchName(); // Procedure Name
	 
      }
   }
   else
   {
      void syntaxError();  //error
   }
};
void Parser::IfStatement()
{//std::cout<<"ifstatement -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "if")
   {
      match(); //if
      int startLabel = NewLabel();
      int doneLabel = NewLabel();
      GuardedCommandList(startLabel, doneLabel);
      adminhandle.emit2("DEFADDR", startLabel);
      adminhandle.emit2("FI", adminhandle.getLine());
      adminhandle.emit2("DEFADDR", doneLabel);
      
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
{//std::cout<<"dostatement-"<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 258 && laTok.getLexeme() == "do")
   {
      match(); // do
      int startLabel = NewLabel();
      int loopLabel = NewLabel();
      adminhandle.emit2("DEFADDR", loopLabel);
      GuardedCommandList(startLabel, loopLabel);

      adminhandle.emit2("DEFADDR",startLabel);
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
void Parser::GuardedCommandList(int &startLabel, int GoTo)
{//std::cout<<"guardedcommandlist -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 270 || laTok.getSymbol() == 257||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "true") ||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "false")||
      laTok.getSymbol() == 256 || laTok.getSymbol() == 274|
      laTok.getSymbol() == 265)
   {

      
      
      GuardedCommand(startLabel, GoTo);
      while (laTok.getSymbol() == 277)
      {
	 match(); // []
	 GuardedCommand(startLabel, GoTo);
      }
      
      
      //std::cout<<"DONE GCL";
   }
   else if((laTok.getSymbol() == 258 && laTok.getLexeme() == "fi") || (laTok.getSymbol() == 258 &&laTok.getLexeme() == "od" ))//epsilon
   {
   }
   else
   {
     void syntaxError(); //error
   }
};

void Parser::GuardedCommand(int &thisLabel, int GoTo)
{
   //std::cout<<"guardedcommand -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 270 || laTok.getSymbol() == 257||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "true") ||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "false")||
      laTok.getSymbol() == 256 || laTok.getSymbol() == 274|
      laTok.getSymbol() == 265)
   {
      adminhandle.emit2("DEFADDR",thisLabel);
      PL_type tmp;
      tmp = Expression();
      //  if(!tmp == Boolean)
//	 typeError();
      thisLabel = NewLabel();
      adminhandle.emit2("ARROW", thisLabel);
       if(laTok.getSymbol() == 278)
	   match(); //->
       else
	  syntaxError();
       
       StatementPart();
       adminhandle.emit2("BAR", GoTo);
    }
    else
    {
   void syntaxError(); //error
    }
};
PL_type Parser::Expression()
{//std::cout<<"expression -Token: "<<laTok.getLexeme()<<std::endl;
   PL_type tmp;  // type of expression is dependant on the type of primary expression
    if(laTok.getSymbol() == 270 || laTok.getSymbol() == 257||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "true") ||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "false")||
      laTok.getSymbol() == 256 || laTok.getSymbol() == 274|
      laTok.getSymbol() == 265)
    {
   
       tmp = PrimaryExpression();
       //if this loop is entered must be a boolean type or else error 
       while(laTok.getSymbol() == 263 || laTok.getSymbol() == 264)
       {
	  if(tmp != boolean && tmp != universal)
	  {
	     // adminhandle->typeError();
	     tmp = universal;
	  }
	  Symbol tempsym = PrimaryOperator();
	  PL_type type2 = PrimaryExpression();
	  if(type2 !=boolean && type2 != universal)
	  {
	     // adminhandle.typeError();
	     tmp = universal;
	  }
	  if(tempsym == AMPRSND)
	     adminhandle.emit1("AND");
	  else
	     adminhandle.emit1("OR");
       }
    }
    else
       syntaxError();
    
    return tmp;
    
};

Symbol Parser::PrimaryOperator()
{//std::cout<<"primaryoperator -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 263)
    {
       match(); //&
       return AMPRSND;
    }
   else if(laTok.getSymbol() == 264)
    {
       match(); // |
       return VLINE;
    }
  else
    {
   syntaxError(); //error
    }
};
PL_type Parser::PrimaryExpression()
{
   PL_type tmp;
   PL_type result;

   //std::cout<<"primaryexpression -Token: "<<laTok.getLexeme()<<std::endl;
    if(laTok.getSymbol() == 270 || laTok.getSymbol() == 257||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "true") ||
      (laTok.getSymbol() == 258 && laTok.getLexeme() == "false")||
      laTok.getSymbol() == 256 || laTok.getSymbol() == 274|
       laTok.getSymbol() == 265)
    {
       tmp =  SimpleExpression(); // type is whatever the simple exp will be
       result = tmp;

       while(laTok.getSymbol() == 266 || laTok.getSymbol() == 267 || // relational ops
	     laTok.getSymbol() == 268 || laTok.getSymbol() == 280 ||
	     laTok.getSymbol() == 281 || laTok.getSymbol() == 282)
       {
	  if(tmp != integer && tmp != universal)
	  {
	     adminhandle.typeError("Operand not integer");
	     tmp = universal;
	  }
	  Symbol tempsym = RelationalOperator();
	  PL_type type2 = SimpleExpression();
	  if(type2 != integer && type2 != universal)
	  {
	     adminhandle.typeError("Op not an integeR");
	     tmp = universal;
	  }
	  if(tempsym == LESSTHAN)
	     adminhandle.emit1("LESS");
	  else if(tempsym == EQUALS)
	     adminhandle.emit1("EQUALS");
	  else
	     adminhandle.emit1("GREATER");
	  ////need to add double character symbols
	  result = boolean;
       }
       
    }
    else
       syntaxError();
    
    return result;
};    
Symbol Parser::RelationalOperator()
{//std::cout<<"relationaloperator -Token: "<<laTok.getLexeme()<<std::endl;
   if (laTok.getSymbol() == 266 || laTok.getSymbol() == 267 ||
      laTok.getSymbol() == 268 || laTok.getSymbol() == 280 ||
       laTok.getSymbol() == 281 || laTok.getSymbol() == 282)
   {
      
      match();
      
   }
   if (laTok.getSymbol() == 266 ) // lessthan
   {
      match();
      return LESSTHAN;
      
   }
   else if (laTok.getSymbol() ==  267) //assignment???? not coleq
   {
      match();
      return ASSIGNMENT;
   }
   else if (laTok.getSymbol() == 268)
   {
      match();
      return GREATERTHAN;
   }/* 2 char symbols
   if (laTok.getSymbol() == )
   {
      match();
      return ss;
   }
   if (laTok.getSymbol() == )
   {
      match();
      return ss;
   }
   if (laTok.getSymbol() == )
   {
      match();
      return ss;
   }
   if (laTok.getSymbol() == )
   {
      match();
      return ss;
   }
   if (laTok.getSymbol() == )
   {
      match();
      return ss;
      }*/
  else
    {
       void syntaxError(); //error
       return BAD_SYMBOL;
    }
};


PL_type Parser::SimpleExpression()
{//std::cout<<"simpleexpression -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == MINUS)
      match(); // -
   PL_type simpletype = Term();
   while(laTok.getSymbol() == 269 || laTok.getSymbol() == 270)
   {
      if (simpletype != integer && simpletype != universal)
      {
//	 adminhandle.typeError("not integer type");
	 simpletype = universal;
      }
      Symbol addop = AddingOperator();
      PL_type simpletype2 = Term();
      if(simpletype2 != integer && simpletype2 != universal)
      {
//	 adminhandle.typeError("not integer type");
	 simpletype = universal;
      }
      if(addop == PLUS)
	 adminhandle.emit1("ADD");
      else
	 adminhandle.emit1("MINUS");
   }
   return simpletype;
};
   

Symbol Parser::AddingOperator()
{//std::cout<<"addingoperator -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 269)
    {
       match(); // +
       return PLUS;
    }
   else if(laTok.getSymbol() == 270)
    {
       match(); // -
       return MINUS;
    }
    else
    {
    void syntaxError();   //error
    }
};
PL_type Parser::Term()
{//std::cout<<"term -Token: "<<laTok.getLexeme()<<std::endl;
   if(// num true false id ( ~
      laTok.getSymbol() == 257 ||laTok.getSymbol() == 258 ||laTok.getSymbol() == 258 ||
      laTok.getSymbol() == 256 ||laTok.getSymbol() == 274 ||laTok.getSymbol() == 265)
   {
      PL_type tmp;
      tmp = Factor();//should be a num or a const
      while(laTok.getSymbol() == 271 || laTok.getSymbol() == 272 || laTok.getSymbol() == 273)
      {
	 if(tmp != integer && tmp != universal)
	 {
	    // adminhandle.typeError(" not integertype");
	    tmp = universal;
	 }
	 Symbol multop = MultiplyingOperator();
	 PL_type type2 = Factor();
	 if(type2 != integer && type2 != universal)
	 {
	    adminhandle.typeError("not integertype");
	    type2 = universal;
	 }
	 if(multop == TIMES)
	    adminhandle.emit1("MULTIPLY");
	 else if(multop == FSLASH)
	    adminhandle.emit1("DIVIDE");
	 else
	    adminhandle.emit1("MODULO");

      }
      return tmp;
   }
   else
   {
    void syntaxError();  //error
   }
};
Symbol Parser::MultiplyingOperator()
{
   //std::cout<<"multiplying operator -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 271)
   {
      match();
      return TIMES;
   }
   else if( laTok.getSymbol() == 272)
   {
      match();
      return FSLASH;
   }
   else if(laTok.getSymbol() == 273)
   {
      match();
      return BSLASH;
   }
   else
      void syntaxError();
};
PL_type Parser::Factor()// if the lexeme search is not -1 the factor token must be
//true,false, a constant, or a variable// so get the token from the symboltable if it is a constant go to constant if it is just a variable go
{
   
   //std::cout<<"factor -Token: "<<laTok.getLexeme()<<laTok.getSymbol()<<std::endl;
   int constind = blocktable.top().search(laTok.getLexeme());
   Token factorTok;
   if(constind != -1)
   {
	 factorTok = blocktable.top().at(constind);
   }
   //256 need to check whether id is a constant name or a variable name  instructions to ignore....
   if( laTok.getSymbol() == 258 || (factorTok.getSymbol() == 256 && factorTok.getNameKind() == 2) ) // if namekind is 2 then it is of type constant 
   {
      //std::cout<<"constant";
      int constval;
      PL_type consttype;
      Constant(constval, consttype);
      adminhandle.emit2("CONSTANT", constval);
      
      return consttype;
   }
   else if(laTok.getSymbol() == 274) 
   {
      match(); // (
      PL_type tmp;
      tmp = Expression();
      if(laTok.getSymbol() == 275)
	 match(); //)
      else
	 syntaxError();
      return tmp;
   }
   else if((factorTok.getSymbol() == 256) && (factorTok.getNameKind() == 1 || factorTok.getNameKind() == 4))
      //array variable or a variable
   {
      PL_type tmp;
      //std::cout<<"variable access";
      tmp =  VariableAccess();
      adminhandle.emit1("VALUE");
      return tmp;
   }
   
   else if(laTok.getSymbol() == 265)
   {
      PL_type tmp;
      match(); // ~
      tmp = Factor();
      if(tmp != boolean && tmp != universal)
      {
	 tmp = universal;
	 // adminhandle.typeError("~ must be used with a boolean expression");
      }
      adminhandle.emit1("NOT");
      return tmp;
   }
   else if(laTok.getSymbol() == 257) // number token
   {
      int constVal;
      PL_type tmp;
      Constant(constVal, tmp);
      adminhandle.emit2("CONSTANT",constVal);
      return tmp;
   }
   else
   {
      void syntaxError(); //error
   }
};
PL_type Parser::VariableAccess()
{//std::cout<<"variableaccess -Token: "<<laTok.getLexeme()<<std::endl;
   Token temptok;
   if(laTok.getSymbol() == 256)
   {
       PL_type tmp;
       int index = blocktable.top().search(laTok.getLexeme());

       if(index != -1) // verify existing;
       {

	  temptok = blocktable.top().at(index);
	  tmp = blocktable.top().at(index).getPL_type();
	  PL_kind name = blocktable.top().at(index).getNameKind();
	  
	  matchName();
	  if( name == array)
	  {
	     if(laTok.getSymbol() == 261)
	     {
		PL_type tp2 = IndexedSelector();
		if( tp2 != integer && tp2 == universal)
		   adminhandle.typeError("Array index not an integer");
		adminhandle.emit3("INDEX",temptok.getArrsize(), adminhandle.getLine());
	     }
	  }
	  
	  return tmp;
       }
       else
	  adminhandle.scopeError("Undefined variable");
       adminhandle.emit3("VARIABLE", (blocktable.size() - 1) - temptok.getBlocklvl(), 2);
       
   }
   else
   {
      void syntaxError(); //error
   }
};
void Parser::VA2()
{//std::cout<<"va2 -Token: "<<laTok.getLexeme()<<laTok.getSymbol()<<std::endl;
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
      laTok.getSymbol() == 273 || laTok.getSymbol() == 261 || laTok.getSymbol() == 276)//epsilon
   {
   }
   else
   {
      void syntaxError();  //error
   }
};
PL_type Parser::IndexedSelector()
{//std::cout<<"IndexedSelector -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 261)
   {
      PL_type tmp;
      match(); //[
      tmp = Expression();
      if(laTok.getSymbol() == 262)
	 match(); //]
      else
	 syntaxError();
      return tmp;
   }
   else
   {
     void syntaxError(); //error
   }
};
void Parser::Constant(int &value, PL_type &type)
{//std::cout<<"Constant -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 257) // if a number token
   {
      value = laTok.getValue();
      type = integer;
      Numeral();
   }
   else if(laTok.getSymbol() == 258) // if a word token.. toget here  it should be true or false
   {
      value = laTok.getValue();
      type = boolean;
      BooleanSymbol();
   }
   else if(laTok.getSymbol() == 256)
   {
      
      if(blocktable.top().search(laTok.getLexeme()) == -1)
	 std::cout<<"the variable has not been declared"<<std::endl;
      else
      {
	 Token tmp = blocktable.top().at(blocktable.top().search(laTok.getLexeme()));
	 value = tmp.getValue();
	 type = tmp.getPL_type();
	 matchName(); // constant name
      }
   }
   else
   {
     void syntaxError(); //error
   }
};
void Parser::Numeral()
{//std::cout<<"Numeral -Token: "<<laTok.getLexeme()<<std::endl;
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
{//std::cout<<"BooleanSymbol -Token: "<<laTok.getLexeme()<<std::endl;
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
   //std::cout<<"Name -Token: "<<laTok.getLexeme()<<std::endl;
   if(laTok.getSymbol() == 256)// verify that token is an identifier
   {
      
      //determine the type of id by its pl t
      
      matchName();
   }
   else
      syntaxError();
}

int Parser::matchName()
{
   int temp = -1;
   match();
   if(laTok.getSymbol() == 256)//id
   {
      temp = laTok.getId();//get the id 
      laTok = scannerhandle.nextToken();//then get the next token
   }
   return temp;//return the id of the previoud token id
};
