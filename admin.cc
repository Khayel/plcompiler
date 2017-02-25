#include"token.h"
#include"admin.h"
#include"scanner.h"

//scanning is now part of the parser.....
//scan begins the parsing process
//New lines tokens are outputted to the token stream for testing but they should just set the next line of the admin. Also DOLLAR tokens are also  outputted in the stream for testing
//EOF token ends the loop...
int Admin::scan(Token newtok)
{
    // begins scanning
   // parse.program();
   if(newtok.getSymbol() == NEWLINE)
   {
      NewLine();
      // std::cout<<" <NEWLINE> ";
      // std::cout<<'\n';
      }
   if(newtok.getSymbol() == DOLLAR)
   {
      NewLine();
   }
   //  if(newtok.getSymbol() == EOFF)
   //     {
//	  std::cout<<" <EOF> ";
//	  break;
   //     }
   if(newtok.getSymbol() >= 287 && newtok.getSymbol() <= 290)
   {//error
	 error();
	 std::cout<<" Error at line "<<lineNum<<": ";
	 if (newtok.getSymbol() == 288)
	    std::cout<<newtok.getLexeme()<<". Out of Bounds."<<std::endl;
	 if (newtok.getSymbol() == 287)
	    std::cout<<newtok.getLexeme()<<" is an existing name"<<std::endl;
	 if (newtok.getSymbol()== 289)
	    std::cout<<newtok.getLexeme()<<" is not a valid symbol in PL"<<std::endl;
	 if (newtok.getSymbol() == 290)
	    std::cout<<newtok.getLexeme()<<" is not a valid sequence in PL"<<std::endl;
	 if (errCount>=MAXERRORS)
	 {
	    std::cout<<"Too many errors"<<std::endl;
	    return 0;
	 }
}
/*	 
	    
   if((newtok.getSymbol() >= 259 && newtok.getSymbol() <= 282)||(newtok.getSymbol() == 286))
      
      std::cout<<" <SYMBOL,"<<newtok.getSymbol()<<"> ";
   
   if (newtok.getSymbol() == 256)
      std::cout<<" <ID,"<<newtok.getSymbol()<<", "<<newtok.getLexeme()<<"> ";
   if (newtok.getSymbol() == 257)
	 std::cout<<" <NUM,"<<newtok.getSymbol()<<","<<newtok.getValue()<<"> ";
   if (newtok.getSymbol() == 258)
   std::cout<<" <WORD,"<<newtok.getLexeme()<<"> ";*/
   return errCount;
};
void Admin::error()
{
   errCount++;
};

void Admin::emit1(std::string opcode)
{
   (*outputfileptr)<<opcode<<"\n";
};
void Admin::emit2(std::string opcode, int x)
{
   (*outputfileptr)<<opcode<<"\n"<<x<<"\n";
};
void Admin::emit3(std::string opcode,int x, int y)
{
   (*outputfileptr)<<opcode<<"\n"<<x<<"\n"<<y<<"\n";
};
