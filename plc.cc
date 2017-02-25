#include "scanner.h"
#include "token.h"
#include "admin.h"
#include "parser.h"
#include<iostream>
#include"symtable.h"
#include<fstream>
#include<string>
//main driver for scanning
//command line requires 3 args, executable,PLinputfile, and Outputfile.
int main(int argc, char *argv[]){
  
  //Requirement of 3 arguments in command line
  if (argc !=3){
    std::cout<<"Usage:"<<argv[0]<<"PL_file Output_file"<<std::endl;
    return 0;
  }
  //initialize inputfile PL file
  std::ifstream inputfile(argv[1],std::ifstream::in);
  if (!inputfile)
    {
      std::cerr<<"Inputfile could not be opened."<<std::endl;
      return 0;
    }

  //initialize output file 
  std::ofstream outputfile;
  outputfile.open(argv[2]);
  if (!outputfile)
  {
     std::cerr<<"Outputfile could not be opened."<<std::endl;
     return 0;
  }
  
  

  
  
  //make appropriate objects,
  Symtable st;
  Scanner scaner(inputfile,st);
  
  Admin compile(inputfile,outputfile,scaner);
  Parser parsr(scaner,compile);

  
  parsr.Program();
  //begins the scan of the input txt
  /*if (compile.scan() == 0)
     std::cout<<"Scanning finished successfully with no errors."<<std::endl;
  else
     std::cout<<"Scanning has some errors.";
  */
  return 0;
};
  
