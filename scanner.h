#ifndef SCANNER_H
#define SCANNER_H
#include "token.h"
#include "symtable.h"
class Scanner{
 public:
  Scanner();
  Scanner(std::ifstream &instream, Symtable &symboltable);
  Token nextToken();
 private:
  std::ifstream *inpfileptr;
  Symtable *symtableptr;
  char laCh; //lookahead character
  bool isWhiteSpace(char ch);
  bool isAlpha(char ch);
  bool isNum(char ch);
  bool isSpecial(char ch);
  Token recognizeName(std::string lex);
  Token recognizeSpecial(std::string lex);
  Token recognizeNumeral(std::string lex);
};
#endif
