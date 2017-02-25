compiler: plc.cc admin.cc symtable.cc scanner.cc
	g++ -o compile plc.cc admin.cc symtable.cc scanner.cc parser.cc