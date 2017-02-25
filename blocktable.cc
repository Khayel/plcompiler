#include "blocktable.h"

Blocktable::BlockTable()
{levels = 0;}
void newLevel()
{
   Symtable newtable;
   btable.push(newtable);
};
int getLevel(Token t);
{
   int currlvl = 0;
   int index = btable.top.search(t.getLexeme());
   if ( index != -1) // found on the top level
      return index;
   else
   {
      std::stack<Symtable> tmp = btable;
      while( tmp.size() != 0 && index == -1) //while the stack is not empty and the index is not found
      {
	 
	 tmp.pop();
	 currlvl++;
	 index = tmp.top.search(t.getLexeme());
      }
      if(index == -1)
	 return -1;
      else
	 return currlvl;
   }
};

bool exists(Token t)
{
   int index = btable.top.search(t.getLexeme());
   if ( index != -1) // found on the top level
      return true;
   else
   {
      std::stack<Symtable> tmp = btable;
      while( tmp.size() != 0 && index == -1) //while the stack is not empty and the index is not found
      {
	 
	 tmp.pop();
	 index = tmp.top.search(t.getLexeme());
      }
      if (index == -1)
	 return false;
      else
      {
	 Token check = tmp.top.at(index);
	 if(t.getId() != check.getId() || t.getNameKind() != check.getNameKind() ||
	    t.getPL_type() != check.getPL_type())
	    return false;
	 else
	    return true;
	 
      }
   }
};

int insert(Token t)
{
   int tmp = btable.top.insert(t);
   return tmp;
};
