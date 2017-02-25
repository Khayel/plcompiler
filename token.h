#ifndef TOKEN_H
#define TOKEN_H
#include"symbol.h"
#include<string>

class Token {
 public:
  //Constructors and destructor
 Token(): sname(NONAME), svalue(-1,std::string("noname")){};
  Token(Symbol s, int v, std::string l): sname(s), svalue(v,l), blocklevel(0){};
  ~Token(){};
  //helper funcs
  Symbol getSymbol() const {return sname;};
  void setSymbol(Symbol s){sname = s;};
  void setValue(int x){svalue.value = x;};
  int getValue() const {return svalue.value;};
  std::string getLexeme() const {return svalue.lexeme;};
  void setId(int i){ svalue.Id = i;};
  int getId() const { return svalue.Id;};
  void setNameKind(PL_kind x) { svalue.kind = x;};
  PL_kind getNameKind() const  {return svalue.kind;};
  void setPL_type(PL_type x){ svalue.type = x;};
  PL_type getPL_type() const {return svalue.type;};
  void setArrsize(int x){svalue.arraysize = x;};
  int getArrsize() const {return svalue.arraysize;};

  void setBlocklvl(int n){ blocklevel = n;};
  int getBlocklvl(){return blocklevel;};
  
 private:
  struct attributes
  {
  attributes(int val, std::string lex): value(val),lexeme(lex), kind(undefined),
	type(universal), arraysize(1), Id(-1) {};
     int value; // if the type is a boolean then 0 is false and 1 is true
     std::string lexeme;
     int Id; // unique id for names
     PL_type type; // 0 for universal, 1 for integer, 2 for boolean
     PL_kind kind; // 0 undefined, 1 variable, 2 constant, 3 procedure, 4 array
     int arraysize;
     
  };
  int blocklevel;
  attributes svalue;
  Symbol sname;
    

};
#endif
