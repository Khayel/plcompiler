//Admin header file
#ifndef ADMIN_H
#define ADMIN_H

#include<string>
#include<iostream>
#include<fstream>
#include"scanner.h"
#define MAXERRORS 20

enum errortype{scan,pars,scope,type};

class Admin
{
 public:
  Admin(std::ifstream &in,std::ofstream& out,Scanner &sc) : infileptr(&in), scanr(sc), outputfileptr(&out), lineNum(1){};
  ~Admin(){};

  void NewLine(){lineNum++; correctline = true;};
  void error();
  void scopeError(std::string x){std::cout<<x<<std::endl; };
  void typeError(std::string x){std::cout<<x<<std::endl; };
  int scan(Token newtok);
  int parse();
  int getLine(){return lineNum;};
  void emit1(std::string);
  void emit2(std::string ,int);
  void emit3(std::string,int,int);
  private:
  std::ifstream *infileptr;
  std::ofstream *outputfileptr;
  Scanner &scanr;
  int lineNum;
  bool correctline;
  int errCount;

};
#endif
