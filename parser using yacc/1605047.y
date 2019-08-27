%{
#include "1605047_SymbolTable.h"
#define YYSTYPE SymbolInfo*

extern int yylineno; /* from lexer */
int yyparse(void);
int yylex(void);
extern FILE *yyin;

int cntt = 0;

FILE *fp;
FILE *errorFile = fopen("1605047_error.txt", "w");
FILE *logFile = fopen("1605047_log.txt", "w");

int line_count = 1;
int error_count = 0;
SymbolTable *symbolTable = new SymbolTable(97, logFile);

void yyerror(char *str) {
	fprintf(stderr, "Line no %d: %s\n\n", line_count, str);
}

deque<SymbolInfo*> paramList, argList, decList;
//paramList contains(name thakle save kore , type such as Identifier, declaration type such as void int float)
//decList contains(name like a/b/x/arr, type:ID/IDa, decType: int/float)

%}


%token IF ELSE FOR WHILE DO BREAK
%token INT CHAR FLOAT DOUBLE VOID
%token RETURN SWITCH CASE DEFAULT CONTINUE
%token CONST_INT CONST_FLOAT CONST_CHAR
%token ADDOP MULOP INCOP DECOP RELOP ASSIGNOP LOGICOP BITOP NOT
%token LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON
%token ID STRING PRINTLN

%left RELOP LOGICOP BITOP
%left ADDOP
%left MULOP

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE



%%


start :	program {	//okay
			//write your code/action in this block in all the similar blocks below
		}
	  ;


program	:	program unit {	//okay
				fprintf(logFile, "At line no: %d program : program unit\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setName($1->getName() + "\n" + $2->getName());
				fprintf(logFile, "%s\n\n", $$->getName().c_str());

			}
		|	unit {
				fprintf(logFile, "At line no: %d program : unit\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setName($1->getName());
				fprintf(logFile, "%s\n\n", $$->getName().c_str());
			}
		;
		

unit :	var_declaration {		//okay
			fprintf(logFile, "At line no: %d unit : var_declaration\n\n", line_count);
			$$ = new SymbolInfo();
			$$->setName($1->getName());
			fprintf(logFile, "%s\n\n", $$->getName().c_str());
		}
	 |	func_declaration {
	 		fprintf(logFile, "At line no: %d unit : func_declaration\n\n", line_count);
	 		$$ = new SymbolInfo();
			$$->setName($1->getName());
			fprintf(logFile, "%s\n\n", $$->getName().c_str());

	 	}
	 |	func_definition {
	 		fprintf(logFile, "At line no: %d unit : func_definition\n\n", line_count);
	 		$$ = new SymbolInfo();
			$$->setName($1->getName());
			fprintf(logFile, "%s\n\n", $$->getName().c_str());
	 	}
	 ;


func_declaration :	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON {	//okay
						fprintf(logFile, "At line no: %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n", line_count);
						$$ = new SymbolInfo();
						SymbolInfo *simfo = symbolTable->lookUp($2->getName());
						if(simfo) {	//previously declared though redundant but okay for our grammar
					 		if(simfo->getFunctionDetails()->getParamCount() != paramList.size()) {
					 			error_count++;
					 			fprintf(errorFile, "Error at line %d: Invalid number of parameters\n\n", line_count);
					 		} else {
					 			deque<string> paramType = simfo->getFunctionDetails()->getArgTypeList();
								for(int i = 0; i < paramList.size(); i++) {
									if(paramList[i]->getDeclareType() != paramType[i]) {
										error_count++;
										fprintf(errorFile, "Error at line %d: Type Mismatch \n",line_count);
										break;
									}
								}
								if(simfo->getFunctionDetails()->getReturnType() != $1->getName()) {
										error_count++;
										fprintf(errorFile,"Error at line %d: Return Type Mismatch \n\n",line_count);
								}
					 		}
						} else {
							symbolTable->insert($2->getName(), "ID", "Function");
							simfo = symbolTable->lookUp($2->getName());
							for(int i = 0; i < paramList.size(); i++) {
								simfo->getFunctionDetails()->addParameter(paramList[i]->getName(), paramList[i]->getDeclareType());
								simfo->getFunctionDetails()->setReturnType($1->getName());
							}
						}
						$$->setName($1->getName()+" "+$2->getName()+"("+$4->getName()+");");
						fprintf(logFile, "%s\n\n", $1->getName().c_str());
						//clear parameter list
						paramList.clear();
					}
				 |	type_specifier ID LPAREN RPAREN SEMICOLON {
				 		fprintf(logFile, "At line no: %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n", line_count);
				 		$$ = new SymbolInfo();
						SymbolInfo *simfo = symbolTable->lookUp($2->getName());
						if(simfo) {
							if(simfo->getFunctionDetails()->getParamCount() != 0) {
								error_count++;
								fprintf(errorFile, "Error at line %d:  Invalid number of parameters \n\n", line_count);
							}
							if(simfo->getFunctionDetails()->getReturnType() !=  $1->getName()) {
								error_count++;
								fprintf(errorFile, "Error at line %d: Return Type Mismatch \n\n", line_count);
							}
						}else {
							symbolTable->insert($2->getName(), "ID", "Function");
							simfo = symbolTable->lookUp($2->getName());
							simfo->getFunctionDetails()->setReturnType($1->getName());
						}
						$$->setName($1->getName()+" "+$2->getName()+"();");
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
						//clear parameter list redundant...anyway
						paramList.clear();
				 	}
				 ;

func_definition :	type_specifier ID LPAREN parameter_list RPAREN { //okay
						SymbolInfo *simfo = symbolTable->lookUp($2->getName());
						if(simfo) {
							if(!simfo->getFunctionDetails()->isDefined1()) {
								int num = simfo->getFunctionDetails()->getParamCount();
								$$->setDeclareType(simfo->getFunctionDetails()->getReturnType());
								if(num != paramList.size()) {
									error_count++;
									fprintf(errorFile, "Error at line %d: Invalid number of parameters\n\n", line_count);
								}
								else {
									deque<string> paramTypeList = simfo->getFunctionDetails()->getArgTypeList();
									for(int i = 0; i < paramList.size(); i++) {
										if(paramList[i]->getDeclareType() != paramTypeList[i]) {
											error_count++;
											fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
											break;
										}
									}
									if(simfo->getFunctionDetails()->getReturnType()!= $1->getName()) {
											error_count++;
											fprintf(errorFile,"Error at line %d: Return Type Mismatch1\n\n", line_count);
									}
								}
								simfo->getFunctionDetails()->setIsDefined();								
							} else {
								error_count++;
								fprintf(errorFile, "Error at line %d:  Multiple defination of function%s\n\n", line_count, $2->getName().c_str());
							}
						} else {
							symbolTable->insert($2->getName(), "ID", "Function");
							simfo = symbolTable->lookUp($2->getName());
							for(int i = 0; i < paramList.size(); i++){
								simfo->getFunctionDetails()->addParameter(paramList[i]->getName(),paramList[i]->getDeclareType());
							}
							simfo->getFunctionDetails()->setReturnType($1->getName());
							simfo->getFunctionDetails()->setIsDefined();
						}
					} compound_statement {
						fprintf(logFile, "At line no: %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName($1->getName() + " " + $2->getName() + "(" + $4->getName() + ")" + $7->getName());
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
					}
				|	type_specifier ID LPAREN RPAREN {	//okay totally
						SymbolInfo *simfo = symbolTable->lookUp($2->getName());
						if(!simfo){
							symbolTable->insert($2->getName(), "ID", "Function");
							simfo = symbolTable->lookUp($2->getName());
							simfo->getFunctionDetails()->setIsDefined();
							simfo->getFunctionDetails()->setReturnType($1->getName());
						}
						else if(!simfo->getFunctionDetails()->isDefined1()) {
							if(simfo->getFunctionDetails()->getParamCount()) {
								error_count++;
								fprintf(errorFile, "Error at line %d:  Invalid number of parameters\n\n", line_count);
							}
							if($1->getName() != simfo->getFunctionDetails()->getReturnType()){
								error_count++;
								fprintf(errorFile, "Error at line %d: Return Type Mismatch\n\n", line_count);
							}
							simfo->getFunctionDetails()->setIsDefined();
						}
						else{
							error_count++;
							fprintf(errorFile, "Error at line %d:  Multiple defination of function %s\n\n", line_count, $2->getName().c_str());
						}

						$1->setName($1->getName()+" "+$2->getName()+"()");
					} compound_statement {
						fprintf(logFile, "At line no: %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName($1->getName() + $6->getName());
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
				    }
 				;


parameter_list	:	parameter_list COMMA type_specifier ID {	//okay
						fprintf(logFile, "At line no: %d parameter_list : parameter_list COMMA type_specifier ID\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName($1->getName() + ", " + $3->getName()+" "+$4->getName());
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
						paramList.push_back(new SymbolInfo($4->getName(), "ID", $3->getName()));
					}
			    |	parameter_list COMMA type_specifier {
			    		fprintf(logFile, "At line no: %d parameter_list : parameter_list COMMA type_specifier\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName($1->getName()+", "+$3->getName());
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
						paramList.push_back(new SymbolInfo("", "ID", $3->getName()));
			   		}
 				|	type_specifier ID {
 						fprintf(logFile, "At line no: %d parameter_list : type_specifier ID\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName($1->getName() + " " + $2->getName());
		 				fprintf(logFile, "%s\n\n", $$->getName().c_str());
						paramList.push_back(new SymbolInfo($2->getName(), "ID", $1->getName()));
 					}
				|	type_specifier {
						fprintf(logFile, "At line no: %d parameter_list : type_specifier\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName($1->getName()+" ");
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
						paramList.push_back(new SymbolInfo("", "ID", $1->getName()));
					}
 				;

compound_statement	:	LCURL {		//okay
							symbolTable->enterScope();
							for(int i = 0; i < paramList.size(); i++)
								symbolTable->insert(paramList[i]->getName(), "ID", paramList[i]->getDeclareType());
							paramList.clear();
						} statements RCURL {
							fprintf(logFile, "At line no: %d compound_statement : LCURL statements RCURL\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setName("{\n" + $3->getName() + "\n}");
							fprintf(logFile, "%s\n\n", $$->getName().c_str());
							symbolTable->printAllScopeTable();
							symbolTable->exitScope();
						}
 		    		|	LCURL RCURL {
							symbolTable->enterScope();
							for(int i = 0; i < paramList.size(); i++)
								symbolTable->insert(paramList[i]->getName(), "ID", paramList[i]->getDeclareType());
							fprintf(logFile, "At line no: %d compound_statement : LCURL RCURL\n\n{}\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setName("{}");
							symbolTable->printAllScopeTable();
							symbolTable->exitScope();
							//clear the paramList
							paramList.clear();
 		    			}
 		    		;

var_declaration	:	type_specifier declaration_list SEMICOLON {		//okay
						fprintf(logFile, "At line no: %d var_declaration : type_specifier declaration_list SEMICOLON\n\n",line_count);
						if($1->getName() == "void "){
							error_count++;
							fprintf(errorFile, "Error at line %d: TYpe specifier can not be void\n\n", line_count);
						} else for(int i = 0; i < decList.size(); i++) {
							if(symbolTable->lookUpCurrentScope(decList[i]->getName())) { //previously declared
								error_count++;
								fprintf(errorFile, "Error at line %d:  Multiple Declaration of %s \n\n", line_count, decList[i]->getName().c_str());
							} else if(decList[i]->getType() == "array") {
								decList[i]->setType("ID");
								symbolTable->insert(decList[i]->getName(), decList[i]->getType(), $1->getName() + "array");
							} else symbolTable->insert(decList[i]->getName(), decList[i]->getType(), $1->getName());
						}
						$$ = new SymbolInfo();
						$$->setName($1->getName() + " " + $2->getName() + ";");
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
						//clear the decList
						decList.clear();
					}
 		 		;

type_specifier	:	INT {		//okay
						fprintf(logFile, "At line no: %d type_specifier : INT\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName("int ");
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
					}
 				|	FLOAT {
						fprintf(logFile, "At line no: %d type_specifier : FLOAT\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName("float ");
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
 					}
 				|	VOID {
						fprintf(logFile, "At line no: %d type_specifier : VOID\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName("void ");
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
 					}
 				;

declaration_list	:	declaration_list COMMA ID {		//okay
							fprintf(logFile, "At line no: %d declaration_list : declaration_list COMMA ID\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setName($1->getName() + "," + $3->getName());
							fprintf(logFile, "%s\n\n", $$->getName().c_str());
							decList.push_back(new SymbolInfo($3->getName(), "ID"));
						}
 		  			|	declaration_list COMMA ID LTHIRD CONST_INT RTHIRD {
 		  					fprintf(logFile, "At line no: %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setName($1->getName() + "," + $3->getName() + "[" + $5->getName() + "]");
							fprintf(logFile, "%s\n\n", $$->getName().c_str());
							decList.push_back(new SymbolInfo($3->getName(), "array"));
 		  				}
 		  			|	declaration_list COMMA ID LTHIRD CONST_INT RTHIRD ASSIGNOP LCURL lists RCURL {
 		  					fprintf(logFile, "At line no: %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD ASSIGNOP LCURL lists RCURL\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setName($1->getName()+","+$3->getName()+"["+$5->getName()+"] = { "+$9->getName()+" }");
							fprintf(logFile, "%s\n\n", $$->getName().c_str());
							decList.push_back(new SymbolInfo($3->getName(), "array"));
							int l1= $5->getName()[0]-'0';
			   				int l2 = cntt;
			   				cout<<l1<<" "<<l2<<endl;
			   				if(l1 != l2){
			   					error_count++;
			   					fprintf(errorFile, "Error at line %d: array size mismatch\n\n", line_count);
			   				}
			   				cntt = 0;
 		  				}
 		  			|	ID {
 		  					fprintf(logFile, "At line no: %d declaration_list : ID\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setName($1->getName());
							fprintf(logFile, "%s\n\n", $$->getName().c_str());
		   					decList.push_back(new SymbolInfo($1->getName(), "ID"));
 		  				}
 		  			|	ID LTHIRD CONST_INT RTHIRD {
 		  					fprintf(logFile, "At line no: %d declaration_list : ID LTHIRD CONST_INT RTHIRD\n%s\n\n", line_count, $3->getName().c_str());
							$$ = new SymbolInfo();
			   				$$->setName($1->getName()+"["+$3->getName()+"]");
			   				fprintf(logFile, "%s\n\n", $$->getName().c_str());
			   				decList.push_back(new SymbolInfo($1->getName(), "array"));
			   				//-----------------------------------------------------------------------
 		  				}
 		  			|	ID LTHIRD CONST_INT RTHIRD ASSIGNOP LCURL lists RCURL {
 		  					fprintf(logFile, "At line no: %d declaration_list : ID LTHIRD CONST_INT RTHIRD ASSIGNOP LCURL lists RCURL\n%s\n\n", line_count, $3->getName().c_str());
							$$ = new SymbolInfo();
			   				$$->setName($1->getName()+"["+$3->getName()+"]"+" = { "+$7->getName()+" }");
			   				fprintf(logFile, "%s\n\n", ($$->getName() ).c_str());
			   				decList.push_back(new SymbolInfo($1->getName(), "array"));
			   				int l1= $3->getName()[0]-'0';
			   				int l2 = cntt;
			   				cout<<l1<<" "<<l2<<endl;
			   				if(l1 != l2){
			   					error_count++;
			   					fprintf(errorFile, "Error at line %d: array size mismatch\n\n", line_count);
			   				}
			   				cntt = 0;
 		  				}
 		  			;

lists	:  	lists COMMA CONST_INT {
				fprintf(logFile, "\nAt line no: %d lists : lists COMMA CONST_INT\n\n",line_count);
				$$ = new SymbolInfo();
				$$->setName($1->getName() + ", " + $3->getName());
				fprintf(logFile, "%s\n\n", $$->getName().c_str());
				cntt++;
		   	}
		|	lists COMMA CONST_FLOAT {
				fprintf(logFile, "\nAt line no: %d lists : lists COMMA CONST_FLOAT\n\n",line_count);
				$$ = new SymbolInfo();
				$$->setName($1->getName() + ", " + $3->getName());
				fprintf(logFile, "%s\n\n", $$->getName().c_str());
				cntt++;
		   	}
		|   CONST_INT {
				fprintf(logFile, "\nAt line no: %d lists : CONST_INT\n\n",line_count);
				$$ = new SymbolInfo();
				$$->setName($1->getName());
				fprintf(logFile, "%s\n\n", $$->getName().c_str());
				cntt++;
			}
		|   CONST_FLOAT {
				fprintf(logFile, "\nAt line no: %d lists : CONST_FLOAT\n\n",line_count);
				$$ = new SymbolInfo();
				$$->setName($1->getName());
				fprintf(logFile, "%s\n\n", $$->getName().c_str());
				cntt++;
			}


statements	:	statement {		//okay
					fprintf(logFile, "\nAt line no: %d statements : statement\n\n",line_count);
					$$ = new SymbolInfo();
					$$->setName($1->getName());
					fprintf(logFile, "%s\n\n", $$->getName().c_str());
				}
	   		|	statements statement {
					fprintf(logFile, "At line no: %d statements : statements statement\n\n", line_count);
					$$ = new SymbolInfo();
					$$->setName($1->getName()+"\n"+$2->getName());
	   				fprintf(logFile, "%s\n\n", $$->getName().c_str());
	   			}
	   		;


statement 	:	var_declaration {	//okay
					fprintf(logFile, "At line no: %d statement : var_declaration\n\n", line_count);
					$$ = new SymbolInfo();
					$$->setName($1->getName());
					fprintf(logFile, "%s\n\n", $$->getName().c_str());
				}
	  		| 	expression_statement {
	  				fprintf(logFile, "At line no: %d statement : expression_statement\n\n", line_count);
	  				$$ = new SymbolInfo();
					$$->setName($1->getName());
					fprintf(logFile, "%s\n\n", $$->getName().c_str());
	  			}
	  		| 	compound_statement {
	 				fprintf(logFile, "At line no: %d statement : compound_statement\n\n", line_count);
	 				$$ = new SymbolInfo();
					$$->setName($1->getName());
					fprintf(logFile, "%s\n\n", $$->getName().c_str());
	  			}
	  		| 	FOR LPAREN expression_statement expression_statement expression RPAREN statement {
	  				fprintf(logFile, "At line no: %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n", line_count);
	  				$$ = new SymbolInfo();
					if($3->getDeclareType() == "void ") {
						error_count++;
						fprintf(errorFile, "Error at line %d:  Type Mismatch\n\n", line_count);
						$$->setDeclareType("int ");
					}
					$$->setName("for(" + $3->getName() + " " + $4->getName() + " " + $5->getName() + ")\n" + $5->getName());
					fprintf(logFile, "%s\n\n", $$->getName().c_str());
	  			}
	  		| 	IF LPAREN expression RPAREN statement			%prec LOWER_THAN_ELSE {
	  				fprintf(logFile, "At line no: %d statement : IF LPAREN expression RPAREN statement\n\n",line_count);
	  				$$ = new SymbolInfo();
	  				if($3->getDeclareType() == "void ") {
						error_count++;
						fprintf(errorFile, "Error at line %d: Type Mismatch\n\n",line_count);
						$$->setDeclareType("int ");
					}
					$$->setName("if(" + $3->getName() + ")\n" + $5->getName());
	  				fprintf(logFile, "%s\n\n", $$->getName().c_str());
	  			}
	  		| 	IF LPAREN expression RPAREN statement ELSE statement { // contains shift-reduce conflicts
	  				fprintf(logFile, "At line no: %d statement : IF LPAREN expression RPAREN statement ELSE statement\n\n", line_count);
	  				$$ = new SymbolInfo();
					if($3->getDeclareType() == "void "){
						error_count++;
						fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
						$$->setDeclareType("int ");
					}
					$$->setName("if(" + $3->getName() + ")\n" + $5->getName() + "\nelse\n" + $7->getName());
					fprintf(logFile, "%s\n\n", $$->getName().c_str());
	  			}
	  		| 	WHILE LPAREN expression RPAREN statement {
	  				fprintf(logFile, "At line no: %d statement : WHILE LPAREN expression RPAREN statement\n\n", line_count);
	  				$$ = new SymbolInfo();
				  	if($3->getDeclareType() == "void "){
						error_count++;
						fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
						$$->setDeclareType("int ");
					}
				  	$$->setName("while(" + $3->getName() + ")\n" + $5->getName());
	  				fprintf(logFile, "%s\n\n", $$->getName().c_str());
	  			}
	  		| 	PRINTLN LPAREN ID RPAREN SEMICOLON {
	  				fprintf(logFile, "At line no: %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n", line_count);
	  				$$ = new SymbolInfo();
					$$->setName("\n(" + $3->getName() + ")");
	  				fprintf(logFile, "%s;\n\n", $$->getName().c_str());
	  			}
	  		| 	RETURN expression SEMICOLON {
	  				fprintf(logFile, "At line no: %d statement : RETURN expression SEMICOLON\n\n", line_count);
	  				$$ = new SymbolInfo();
					if($2->getDeclareType() == "void ") {
						error_count++;
						fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
						$$->setDeclareType("int ");
					}
					$$->setName("return " + $2->getName() + ";");
	  				fprintf(logFile, "%s\n\n", $$->getName().c_str());
	  			}
	  		;


expression_statement	:	SEMICOLON {		//okay
								fprintf(logFile, "At line no: %d expression_statement : SEMICOLON\n\n", line_count);
								$$ = new SymbolInfo();
								$$->setName(";");
								fprintf(logFile, "%s\n\n", $$->getName().c_str());
							}
						|	expression SEMICOLON {
								fprintf(logFile, "At line no: %d expression_statement : expression SEMICOLON\n\n", line_count);
								$$ = new SymbolInfo();
								$$->setName($1->getName() + ";");
								fprintf(logFile, "%s\n\n", $$->getName().c_str());
							}
						;
						
						
variable	:	ID {	//okay
					fprintf(logFile, "At line no: %d variable : ID\n\n", line_count);
					$$ = new SymbolInfo();
					if(!symbolTable->lookUp($1->getName())) {//exist kore na
						error_count++;
						fprintf(errorFile, "Error at line %d: Undeclared Variable: %s\n\n", line_count, $1->getName().c_str());
					} else if(symbolTable->lookUp($1->getName())) {
						$$->setDeclareType(symbolTable->lookUp($1->getName())->getDeclareType());
					}
					$$->setName($1->getName());	//dorkar ache
					fprintf(logFile, "%s\n\n", $$->getName().c_str());
				}
	 		|	ID LTHIRD expression RTHIRD {	//okay
	 				fprintf(logFile, "At line no: %d variable : ID LTHIRD expression RTHIRD\n\n", line_count);
	 				$$ = new SymbolInfo();
					if(!symbolTable->lookUp($1->getName())){
						error_count++;
						fprintf(errorFile, "Error at line %d: Undeclared Variable: %s\n\n", line_count, $1->getName().c_str());
					}
					if($3->getDeclareType() != "int ") {
						error_count++;
						fprintf(errorFile, "Error at line %d: Non-integer Array Index\n\n", line_count);
					}
					if(symbolTable->lookUp($1->getName())) {
						if(symbolTable->lookUp($1->getName())->getDeclareType() != "int array" &&
							symbolTable->lookUp($1->getName())->getDeclareType() != "float array") {
							error_count++;
							fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
						}
						if(symbolTable->lookUp($1->getName())->getDeclareType() == "int array")
							$1->setDeclareType("int ");
						if(symbolTable->lookUp($1->getName())->getDeclareType() == "float array")
							$1->setDeclareType("float ");
						$$->setDeclareType($1->getDeclareType());
					}
	 				$$->setName($1->getName() + "[" + $3->getName() + "]");
	 				fprintf(logFile, "%s\n\n", $$->getName().c_str());
	 			}
	 		;
	 		
	 		
expression 	:	logic_expression {	//okay
					fprintf(logFile, "At line no: %d expression : logic_expression\n\n", line_count);
					$$ = new SymbolInfo();
					$$->setName($1->getName());
					$$->setDeclareType($1->getDeclareType());
					fprintf(logFile, "%s\n\n", $$->getName().c_str());
				}
			|	variable ASSIGNOP logic_expression {
					fprintf(logFile, "At line no: %d expression : variable ASSIGNOP logic_expression\n\n", line_count);
					$$ = new SymbolInfo();
				   	if($3->getDeclareType() == "void " || (symbolTable->lookUp($1->getName()) && (symbolTable->lookUp($1->getName())->getDeclareType() != $3->getDeclareType()))) {
						error_count++;
						fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
						//cout<<"#debug("<<13<<")"<<endl;
						$$->setDeclareType("int ");
					}
					$$->setDeclareType($1->getDeclareType());
					$$->setName($1->getName() + "=" + $3->getName());
					fprintf(logFile, "%s\n\n", $$->getName().c_str());
				}
			;


logic_expression	:	rel_expression {	//okay
							fprintf(logFile, "At line no: %d logic_expression : rel_expression\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setName($1->getName());
							$$->setDeclareType($1->getDeclareType());
							fprintf(logFile, "%s\n\n", $$->getName().c_str());
						}
		 			|	rel_expression LOGICOP rel_expression {
		 					fprintf(logFile, "At line no: %d logic_expression : rel_expression LOGICOP rel_expression\n\n", line_count);
		 					$$ = new SymbolInfo();
		 					if($1->getDeclareType()!= "int " || $3->getDeclareType()!= "int ") {
								error_count++;
								fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
								//cout<<"#debug("<<14<<")"<<endl;
								$$->setDeclareType("int ");
							} 
				 			$$->setDeclareType("int ");
							$$->setName($1->getName() + $2->getName() + $3->getName());
							fprintf(logFile, "%s\n\n", $$->getName().c_str());
		 				}
		 			;


rel_expression	:	simple_expression {	 //okay
						fprintf(logFile, "At line no: %d rel_expression : simple_expression\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName($1->getName());
						$$->setDeclareType($1->getDeclareType());
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
					}
				|	simple_expression RELOP simple_expression {
						fprintf(logFile, "At line no: %d rel_expression : simple_expression RELOP simple_expression\n\n", line_count);
						$$ = new SymbolInfo();
						if($1->getDeclareType() == "void " || $3->getDeclareType() == "void ") {
							error_count++;
							fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
							$$->setDeclareType("int ");
						}
			 			$$->setDeclareType("int ");
						$$->setName($1->getName() + $2->getName() + $3->getName());
						fprintf(logFile, "%s\n\n", $$->getName().c_str());
					}
				;


simple_expression	:	term {	//okay
							fprintf(logFile, "At line no: %d simple_expression : term\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setDeclareType($1->getDeclareType());
							$$->setName($1->getName());
							fprintf(logFile, "%s\n\n", $$->getName().c_str());
						}
		  			|	simple_expression ADDOP term {
							fprintf(logFile, "At line no: %d simple_expression : simple_expression ADDOP term\n\n", line_count);
							$$= new SymbolInfo();
							if($1->getDeclareType() == "void " || $3->getDeclareType() == "void ") {
								error_count++;
								fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
								$$->setDeclareType("int ");
							} else if($1->getDeclareType() == "float " || $3->getDeclareType() == "float ") {
								$$->setDeclareType("float ");
							} else $$->setDeclareType("int ");
	 						$$->setName($1->getName() + $2->getName() + $3->getName());
		  					fprintf(logFile, "%s\n", $$->getName().c_str());
		  				}
		  			;
		  			

term	:	unary_expression {	//okay
				fprintf(logFile, "At line no: %d term : unary_expression\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType($1->getDeclareType());
				$$->setName($1->getName());
				fprintf(logFile, "%s\n\n", $$->getName().c_str());
			}
     	|	term MULOP unary_expression {
				fprintf(logFile, "At line no: %d term : term MULOP unary_expression\n\n", line_count);
	 			$$ = new SymbolInfo();
	 			if($1->getDeclareType() == "void " || $3->getDeclareType() == "void ") {
				 	error_count++;
				 	fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
				 	$$->setDeclareType("int ");
				} else if($2->getName()=="%" && ($1->getDeclareType()!="int " || $3->getDeclareType()!="int ")) {
					error_count++;
					fprintf(errorFile, "Error at line %d: Integer operand on modulus operator\n\n", line_count);
					$$->setDeclareType("int ");
				} else if($2->getName() == "/") {
					if($1->getDeclareType() == "void " || $3->getDeclareType() == "void "){
						error_count++;
						fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
						$$->setDeclareType("int ");
					} else if($1->getDeclareType() == "int " && $3->getDeclareType() == "int ")
						$$->setDeclareType("int ");
					else $$->setDeclareType("float ");
				} else if($1->getDeclareType() == "float " || $3->getDeclareType() == "float ")
					 	$$->setDeclareType("float ");
				else $$->setDeclareType("int ");

				$$->setName($1->getName() + $2->getName() + $3->getName());
     			fprintf(logFile, "%s\n", $$->getName().c_str());
     		}
     	;


unary_expression	:	ADDOP unary_expression {	//done
							fprintf(logFile, "At line no: %d unary_expression : ADDOP unary_expression\n\n", line_count);
							$$ = new SymbolInfo();
							if($2->getDeclareType() == "void "){
								error_count++;
								fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
								//cout<<"#debug("<<20<<")"<<endl;
								$$->setDeclareType("int ");
							} else
								$$->setDeclareType($2->getDeclareType());
							$$->setName($1->getName() + $2->getName());
							fprintf(logFile, "%s%s\n", $$->getName().c_str());
						}
		 			|	NOT unary_expression {
		 					fprintf(logFile, "At line no: %d unary_expression : NOT unary_expression\n\n", line_count);
							$$ = new SymbolInfo();
							if($2->getDeclareType() == "void "){
								error_count++;
								fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
								$$->setDeclareType("int ");
							} else
								$$->setDeclareType($2->getDeclareType());
							$$->setName("!" + $2->getName());
							fprintf(logFile, "!%s\n\n", $$->getName().c_str());
		 				}
		 			|	factor {
		 					fprintf(logFile, "At line no: %d unary_expression : factor\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setDeclareType($1->getDeclareType());
							$$->setName($1->getName());
							fprintf(logFile, "%s\n\n", $$->getName().c_str());
		 				}
		 			;


factor	:	variable {	//done
				if($1->getDeclareType() == "int array")$1->setName("error"); // kind of error recovery
				//ERROR declared here.....
				fprintf(logFile, "At line no: %d factor : variable\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType($1->getDeclareType());
				$$->setName($1->getName());
				string str = "";
				for(int i = 0; i < $$->getName().size(); i++)
					if($$->getName()[i] == '[')break;
					else str += $$->getName()[i];
				$$->setName(str);
				fprintf(logFile, "%s\n\n", $$->getName().c_str());
			}
		|	ID LPAREN argument_list RPAREN {
				fprintf(logFile, "At line no: %d factor : ID LPAREN argument_list RPAREN\n\n", line_count);
				SymbolInfo* symfo = symbolTable->lookUp($1->getName());
				if(!symfo) { //nai
					error_count++;
					fprintf(errorFile, "Error at line %d:  Undefined Function\n\n", line_count);
					$$->setDeclareType("int ");
				}
				else if(!symfo->getFunctionDetails()) { //ache but func na
					error_count++;
					fprintf(errorFile, "Error at line %d:  Not A Function\n\n", line_count);
					$$->setDeclareType("int ");
				}
				else if(!symfo->getFunctionDetails()->isDefined1()) {
					error_count++;
					fprintf(errorFile, "Error at line %d: Undeclared Function\n\n", line_count);
				} else {
					int num = symfo->getFunctionDetails()->getParamCount();
					$$->setDeclareType(symfo->getFunctionDetails()->getReturnType());
					if(num != argList.size()){
						error_count++;
						fprintf(errorFile, "Error at line %d: Invalid number of arguments\n\n", line_count);

					}
					else{
						//cout<<symbolTable->lookUp($1->getName())->get_isFunction()->getReturnType()<<endl;
						deque<string> paramTypeTemp = symbolTable->lookUp($1->getName())->getFunctionDetails()->getArgTypeList();
						for(int i = 0; i < argList.size(); i++){
							if(argList[i]->getDeclareType() != paramTypeTemp[i]){
								error_count++;
								fprintf(errorFile, "Error at line %d: Type Mismatch\n\n", line_count);
								break;
							}
						}
					}
				}

				argList.clear();
				$$->setName($1->getName() + "( " + $3->getName() + " )");
				fprintf(logFile, "%s\n\n", $$->getName().c_str());
			}
		|	LPAREN expression RPAREN {
				fprintf(logFile, "At line no: %d factor : LPAREN expression RPAREN\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType($2->getDeclareType());
				$$->setName("(" + $2->getName() + ")");
				fprintf(logFile, "%s\n\n", $$->getName().c_str());
			}
		|	CONST_INT {
				fprintf(logFile, "At line no: %d factor : CONST_INT\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType("int ");
				$$->setName($1->getName());
				fprintf(logFile, "%s\n\n", $$->getName().c_str());
			}
		|	CONST_FLOAT {
				fprintf(logFile, "At line no: %d factor : CONST_FLOAT\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType("float ");
				$$->setName($1->getName());
				fprintf(logFile, "%s\n\n", $$->getName().c_str());
			}
		|	variable INCOP {
				fprintf(logFile, "At line no: %d factor : variable INCOP\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType($1->getDeclareType());
				$$->setName($1->getName() + "++");
				fprintf(logFile, "%s++\n\n", $$->getName().c_str());
			}
		|	variable DECOP {
				fprintf(logFile, "At line no: %d factor : variable DECOP\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType($1->getDeclareType());
				$$->setName($1->getName() + "--");
				fprintf(logFile, "%s--\n\n", $$->getName().c_str());
			}
		;


argument_list	:	arguments {  //okay
						//chanded
						//fprintf(logFile, "At line no: %d argument_list : arguments\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName($1->getName());
					}
			  	|	%empty {
			  			$$ = new SymbolInfo();
			  			$$->setName("");
			  			fprintf(logFile, "At line no: %d argument_list : \n\n", line_count);
			  		}
			  	;


arguments   :	arguments COMMA logic_expression {	//okay
					//changed
					fprintf(logFile, "At line no: %d argument_list : argument_list COMMA logic_expression\n\n", line_count);
					$$ = new SymbolInfo();
					$$->setName($1->getName() + " , " + $3->getName());
					fprintf(logFile, "%s, %s\n\n", $1->getName().c_str(), $3->getName().c_str());
					argList.push_back($3); //new argument as a logic_expression
				}
	      	|	logic_expression {
					fprintf(logFile, "At line no: %d argument_list : logic_expression\n\n", line_count);
					$$ = new SymbolInfo();
					$$->setName($1->getName());
					fprintf(logFile, "%s\n\n", $$->getName().c_str());
					argList.push_back(new SymbolInfo($1->getName(), $1->getType(), $1->getDeclareType()));	//first argument
	      		}
	      	;





%%


int main(int argc,char *argv[]) {

	if(!(fp = fopen(argv[1], "r"))) {
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	yyin = fp;
	yyparse();

	fprintf(logFile, "\n\n\n\n				Symbol Table: \n");
	symbolTable->printAllScopeTable();
	line_count--;
	fprintf(logFile, "\nTotal Lines : %d \n\n", line_count);
	fprintf(logFile, "Total Errors : %d \n\n", error_count);
	fprintf(errorFile, "Total Errors : %d \n\n", error_count);


	fclose(logFile);
	fclose(errorFile);

	return 0;
}










