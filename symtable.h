#ifndef SYMTABLE_H
#define SYMTABLE_H
#include"token.h"
#include<vector>
#define SYMTABLESIZE 307

class Symtable {
  public:
   //Constructor inserts reserved keywords into the hash table
  Symtable();
  ~Symtable(){};

  int search(std::string s);
  int insert(std::string s);
  int  insert(Token s);
   Token& at(int index){return htable[index];};
  bool full(){return occupied == SYMTABLESIZE;};
  int getOC(){return occupied;};
  bool isWord(std::string lex);
  private:
  void resize(){ htable.resize(htable.size() * 2);};
  std::vector<Token> htable;
  int occupied;
  int hashfn(std::string);
};
#endif
