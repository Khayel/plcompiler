#include"scanner.h"
#include"token.h"
#include"symtable.h"
#include<iostream>
#include<fstream>
#include<string>
Scanner::Scanner(std::ifstream &instream, Symtable &symboltable)
{
  symtableptr = &symboltable;
  inpfileptr = &instream;
};

//if the laCh is a whitespace then get until it isnt. then set currentch(current character)  to it and have laCh peek the next char
//if currentch is a letter then it must be a name or key word so get the rest of the lexeme then determine the proper action in the recognizeName() func.
//if currentch is a numeral then it must be a number. so get the lexeme of the number it represents and pass it on to the recognizeNumeral() func. It is possible that the number can have a letter, in this case a token with a BAD_NUMERAL symbol will be returned.
//if currentch is a valid symbol then check laCh if it is also a valid symbol. if it is then confirm it is a valid two char symbol in recognizeSymbol(). Otherwise pass in currentch to recognizeSymbol() where it will determine the corrext type of symbol
//if it is EOF NEWLINE or DOLLAR token then they should be recognized and returned
//if it is non of these tokens return a token with a badchar symbol
Token Scanner::nextToken()
{
   std::string lexeme = "";
   char currentch;
   if(isWhiteSpace(laCh))
   {
      while(isWhiteSpace(laCh))
      {
	 laCh = inpfileptr->get();
      }
      currentch = laCh;
      laCh = inpfileptr->peek();
   }
   else{
      
      currentch = inpfileptr->get();
      laCh= inpfileptr->peek();
   }
   
   //check for end of file
   if(currentch == EOF)
   {
      Token endtok(EOFF,0,"eof");
      return endtok;
   }
   else if(currentch == '\n')//ignore newlines
   {
      Token newlinetok(NEWLINE,0,lexeme);
      return newlinetok;
   }
   //At this point you have the first char of a symbol, number, or name
   //if the first character is an alphabet it must be a name or keyword so get the rest of the lexeme
   // name = alphabet (alphabet|num|'_')*
   else if(isAlpha(currentch))
   {
      while (isAlpha(laCh) || isNum(laCh) || laCh == '_')
      {
	 lexeme=lexeme + currentch;
	 currentch = inpfileptr->get();
	 laCh = inpfileptr->peek();
      }
      lexeme = lexeme + currentch;
      return recognizeName(lexeme);
   }
   //if first char is a numeral it must be a number. whitespace or special characters indicated the end to a number.
   else if(isNum(currentch))
   {
      while(isNum(laCh))
      {
	 lexeme = lexeme + currentch;
	 currentch = inpfileptr->get();
	 laCh = inpfileptr->peek();
      }
      lexeme= lexeme +currentch;
      return recognizeNumeral(lexeme);
   }

   //if a char is a special symbol, must check ahead incase it is a symbol with two chars then find appropriate symbol token
   else if (isSpecial(currentch))
   {
      if(isSpecial(laCh))
      {
	 lexeme = lexeme + currentch;
	 currentch = inpfileptr->get();
	 laCh = inpfileptr->peek();
	 lexeme = lexeme + currentch;
	 if( lexeme  =="<=" || lexeme ==">=" || lexeme =="==" ||
	     lexeme ==":=" || lexeme =="->" || lexeme =="[]" )
	 {
	    
	    return recognizeSpecial(lexeme);
	 }
	 else // 2 char symbol is invalid and should have a space
	 {
	    lexeme = currentch;;
	    return recognizeSpecial(lexeme);
	 }
      }
      else
      { 
	 lexeme = currentch;
	 return recognizeSpecial(lexeme);
      }
   }
   //if $ is found ignore the rest of the line up tp a newlinw 
   else if (currentch == '$')
   {
      
      Token comment(DOLLAR,0,"$");
      inpfileptr->ignore(200,'\n');
     
      return comment;
   }
   else
   { std::cout<<"bad char returned here"<<lexeme;
      //if the token does not match any of the previous patterns it is an invalid token
      laCh = inpfileptr->peek();
      Token errTok(BAD_CHAR, 0, lexeme);
      return errTok;
   }
};

//if the character is a blank space return true, false otherwise
bool Scanner::isWhiteSpace(char ch)
{
   if (ch ==' ' || ch == 9)
      return true;
   else
      return false;
};

//if the character is an alphabet( a-z, A-Z) return true, false otherwise
bool Scanner::isAlpha(char ch)
{
   if((ch >= 65 && ch <= 90) || (ch >= 97&& ch <= 122))
      return true;
   else
      return false;
};

//if the character is a digit(0-9) return true, false otherwise 
bool Scanner::isNum(char ch)
{
   if (ch >= 48 && ch <=57)
      return true;
   else
      return false;
};

// if a valid symbol return true, false otherwise
bool Scanner::isSpecial(char ch)
{
   if(
      ch =='.'||ch ==','||ch ==';'||
      ch =='['||ch ==']'||ch =='&'||
      ch =='|'||ch =='~'||ch =='<'||
      ch =='='||ch =='>'||ch =='+'||
      ch =='-'||ch =='*'||ch =='/'||
      ch == 92 ||ch == 40||ch == 41||
      ch == ':')
      return true;
   else
      return false;
};

//if the lexeme is a word return a word token if a search in the symbol table returns -1 then insert the lexeme as a new name otherwise
Token Scanner::recognizeName(std::string lex)
{//since scope and type check the scanner no longer has anything to do with the symbol table except for checking that the lexeme is a word. so if it is a name pattern then if it does not extist it must be an id
         
   if (symtableptr->isWord(lex))
   {
      Token wordtok(WORD,0,lex);
      return wordtok;
   }
   
   /* else if (symtableptr->search(lex) == -1)
   {
      int index = symtableptr->insert(lex);
      Token idtok(ID,0,lex);
      return idtok;
      }*/
   else // htable entry exist so just return the token without inserting
   {
      Token id(ID,0,lex);
      return id;
   }
};
//takes the string lex and converts it into a numerical value
//assumes that entire string is a number
 //because of max int value it loops around so after every iteration check if value is negative if it is then the value is out of bounds so return a BAD_NUM
Token Scanner::recognizeNumeral(std::string lex)
{
   int tmp = 1;
   int value = 0;
   for( int i = lex.length()-1; i >=0; i--)
   {
      value = value + (lex[i]-48)*tmp;
     
      if (value<0)// need to get maxint value
      {
	 Token badnum(BAD_NUMERAL, value,lex);
	 return badnum;
      }
      tmp = tmp * 10;
   }
   Token numtok(NUM, value,lex);
   return numtok;     
};
//Recognize all special symbols and return the appropriate type of token
Token Scanner::recognizeSpecial(std::string lex)
{
   if(lex == "."){
      Token symtok(DOT,0,lex);
      return symtok;
   }
   else if (lex ==","){
      Token symtok(COMMA,0,lex);
      return symtok;
   }
   else if (lex ==";"){
      Token symtok(SEMICOL,0,lex);
      return symtok;
   }
   else if (lex =="["){
      Token symtok(SQLEFT,0,lex);
      return symtok;
   }
   else if (lex =="]"){
      Token symtok(SQRIGHT,0,lex);
      return symtok;
   }
   else if (lex =="&"){
      Token symtok(AMPRSND,0,lex);
      return symtok;
   }
   else if (lex =="|"){
      Token symtok(VLINE,0,lex);
      return symtok;
   }
   else if (lex =="~"){
      Token symtok(TILDE,0,lex);
      return symtok;
   }
  else if (lex =="<"){
      Token symtok(LESSTHAN,0,lex);
      return symtok;
   }
   else if (lex =="="){
      Token symtok(ASSIGNMENT,0,lex);
      return symtok;
   }
   else if (lex ==">"){
      Token symtok(GREATERTHAN,0,lex);
      return symtok;
   }
   else if (lex =="+"){
      Token symtok(PLUS,0,lex);
      return symtok;
   }
   else if (lex =="-"){
      Token symtok(MINUS,0,lex);
      return symtok;
   }
   else if (lex =="*"){
      Token symtok(TIMES,0,lex);
      return symtok;
   }
   else if (lex =="/"){
      Token symtok(FSLASH,0,lex);
      return symtok;
   }
   else if (lex[0] == 92){
      Token symtok(BSLASH,0,lex);
      return symtok;
   }
   else if (lex =="("){
      Token symtok(LEFTP,0,lex);
      return symtok;
   }
   else if (lex ==")"){
      Token symtok(RIGHTP,0,lex);
      return symtok;
   }
   else if (lex ==":="){
      Token symtok(COLEQ,0,lex);
      return symtok;
   }
   else if (lex =="[]"){
      Token symtok(SQ,0,lex);
      return symtok;
   }
   else if (lex =="->"){
      Token symtok(ARROW,0,lex);
      return symtok;
   }
   else if (lex =="<="){
      Token symtok(LESSTHAN_EQ,0,lex);
      return symtok;
   }
   else if (lex ==">="){
      Token symtok(GREATERTHAN_EQ,0,lex);
      return symtok;
   }
   else if(lex =="==")
   {
      Token symtok(EQUALS,0,lex);
      return symtok;
   }
   else
   {
      Token badsym(BAD_SYMBOL, 0, lex);
      return badsym;
   }
};

