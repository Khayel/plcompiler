

CPSC4600 Compiler Construction
Kyle Chua

Program Files:
-plc.cc: Driver program which contains the main function. This also checks for proper command-line input.
-admin.h admin.cc: Responsible for errors and other services not related to main parts of the compiler
-token.h: Token class implementation.
-symbol.h: enumeration of symbols.
-symtable.h symtable.cc: Symbol table implementation,hash table.
-scanner.h scanner.cc: files for scanner implementation.
-test.txt: A test PL source code file.
-out.txt: token stream
-makefile: makefile to compile.
-parser.h class for the parser
- assembler: directory for the assembler- assembler.h/.cc, assemblerdriver.cc
-interpreter: directory for the interpreter- interp.h/.cc, interpreterdriver.cc
Compilation:
	To compile the assembler: 
	   make  (in the assembler directory)
	To compile the interpreter:
	   make (in the assembler directory
Running the program: 
-To compile and run a program. first you go to the assembler directory and run the assembler using:
    	     assemble sourcefile nameofasmfile
-the assemblefile will be created in the assembler directory
-after the machine code has been generated (nameofasmfile), you need to go to the interpreter and execute it:
       	   interpret ../assembler/nameofasmfile


input_files included-test.txt
output_files included-out.txt
-Errors are outputted by the admin in the console.

Errors: 
- when writing two continuous one character symbols they must have a space between them
- the parser has panic mode recovery.
- error reporting
- block table implementation- only local scope
- procedures
- Did not get to combine parsing,assembler,and interpreter in one main


