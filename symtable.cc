#include"symtable.h"
#include<string>
#include<iostream>
Symtable::Symtable()
{
   //initialize objects
  occupied = 0;
  htable.resize(SYMTABLESIZE);
  //insert reserved words into hashtable
  int tmp;
  tmp=insert("begin");
  htable[tmp].setSymbol(WORD);
  tmp=insert("end");
  htable[tmp].setSymbol(WORD);
  tmp=insert("const");
  htable[tmp].setSymbol(WORD);
  tmp=insert("array");
  htable[tmp].setSymbol(WORD);
  tmp=insert("integer");
  htable[tmp].setSymbol(WORD);
  tmp=insert("Boolean");
  htable[tmp].setSymbol(WORD);
  tmp=insert("proc");
  htable[tmp].setSymbol(WORD);
  tmp=insert("skip");
  htable[tmp].setSymbol(WORD);
  tmp=insert("read");
  htable[tmp].setSymbol(WORD);
  tmp=insert("write");
  htable[tmp].setSymbol(WORD);
  tmp=insert("call");
  htable[tmp].setSymbol(WORD);
  tmp=insert("if");
  htable[tmp].setSymbol(WORD);
  tmp=insert("do");
  htable[tmp].setSymbol(WORD);
  tmp=insert("fi");
  htable[tmp].setSymbol(WORD);
  tmp=insert("od");
  htable[tmp].setSymbol(WORD);
  tmp=insert("false");
  htable[tmp].setSymbol(WORD);
  tmp=insert("true");
  htable[tmp].setSymbol(WORD);
};

//hashfunction to search if elements exists if it does return the index else return -1
int Symtable::search(std::string s)
{
   
   // it is a name with matching lexeme then it already exists
   for (int i=0; i < SYMTABLESIZE; i++)
   {
      if(htable[i].getLexeme() == s )
      {
	 
	 return i;
      }
	
   }
   return -1;
};
//return the index that the element was inserted into or else it will return a -1
//if symtable is not full we can insert an element into it. newTok will get the properties of the string s determined by the scanner then using the hash function it will map it into the htable if the index of the hash function is occupioed then it will increment the hash number and try again until it finds ana available index where it will be stored into
//symbol table entries will only be identifiers
int Symtable::insert(Token s)
{
   if(s.getSymbol() == 258)
   {
      std::cout<<"tryinh to insert a word";
      return search(s.getLexeme());
   };
   int hashnum = hashfn(s.getLexeme());
   s.setId(hashnum);
 
   while(true)
   {
      if(htable[hashnum].getSymbol() == NONAME)
      {
	 htable[hashnum] = s;
	 occupied++;
	 if(full())
	    resize();
	 return hashnum;
      }
      else
      {
	 if(hashnum == htable.size())
	 {
	    hashnum == 0;
	 }
	 hashnum++;
      }
   }
   return -1;
};
int Symtable::insert(std::string s)
{
   if(isWord(s))
   {
      std::cout<<"Trying to insert a word";
   }
   int hashnum = hashfn(s);
   Token newTok(ID,0,s);
   newTok.setId(hashnum);
   while (true)
   {
      if (htable[hashnum].getSymbol() == NONAME)
      {
	 htable[hashnum] = newTok;
	 occupied++;
	 if(full())
	    resize();
	 return hashnum;
      }
      else
      {
	 if(hashnum == htable.size())
	 {
	    hashnum == 0;
	 }
	 hashnum++;
      }
   }
   
   return -1;
   
};

//hash function gets the sum of the ascii values of the chars of the string then mods it by 307.
int Symtable::hashfn(std::string str)
{
  int num = 0;
  for( int i =0; i < str.length(); i++)
    {
      num = num + str[i];
    }
  num = num%307;
  return num;
};

//determines if the lexeme is an existing keyword      
bool Symtable::isWord(std::string lex)
{
   int i = search(lex);
   
      if(htable[i].getSymbol() == 258 && htable[i].getLexeme() == lex)
      {
	 return true;
      }
      else
	 return false;
};
