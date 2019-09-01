# Simple-C-Compiler-
1. Contains a SymbolTable(and acciated files), a lexer, a parser, an input, a script.sh(bash) file.
2. lexer is flex/lex file which is acting as a lexical analyzer
3. parser is yacc/bison file whics acts as a syntax analyzer/parser
4. input.txt contains the c/c++ program that need to be matched by our grammar rule and regulations
5. script.sh is a bash file which can be run in terminal using "bash script.sh" command
6. after running it will produce a log file, an error file and associated files for lexing and parsing
7. now an ICG(intermediate assembly code generator) is provided which will take a c programm in input.c file
   and produce two file code.asm and Code.asm. You can emulate those assembly programm in your 8086 emulator.
   Do not forget that our grammar is not so elaborated so if you get syntax error from yyparse or custom segmentation 
   fault then use gdb(gnu debugger..instructed in debug.sh file) or check the log file which causes...and update your C code
8. ENJOY....!!!!
#you have to put all files together in same directory
#this project is an assignment purpose...you can take it as reference..but do not use and copy it blindly
#avoid plagiarism!!!
