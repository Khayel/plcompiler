#ifndef BLOCKTABLE_H
#define BLOCKTABLE_H

#include"symtable.h"
#include"token.h"
#include<stack>

class BlockTable
{
  public:
   BlockTable();
   ~BlockTable();
   void newLevel(); //called whenever a new block is called...
   int getLevel(Token);//return level of a token if found -1 if not
   bool exists(Token); // find Token at int level
   int insert(Token);
  private:
   std::stack<Symtable> btable;
   int levels;
};






#endif

