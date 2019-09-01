%{
#include "1605047_SymbolTable.h"
#define YYSTYPE SymbolInfo*

using pss = pair < string, string >;
using dsim = deque < SymbolInfo* >;
using ds = deque < string >;
using vs = vector < string >;
using dss = deque < pss >;

extern int yylineno; /* from lexer */
int yyparse(void);
int yylex(void);
extern FILE *yyin;

FILE *fp;
//FILE *errorFile = fopen("1605047_error.txt", "w");
FILE *logFile = fopen("log.txt", "w");

int line_count = 1;
int error_count = 0;
SymbolTable *symbolTable = new SymbolTable(97, logFile);

void yyerror(const char *str) {
	fprintf(stderr, "Line no %d: %s\t(inside yyerror)\n\n", line_count, str);
}

int labelCount = 0, tempCount = 0;
template <typename T> string toString(T n) { stringstream ss; ss << n; return ss.str(); }

dsim paramList, argList, decList;
//paramList contains(name thakle save kore , type such as Identifier, declaration type such as void int float)
//decList contains(name like a/b/x/arr, type:ID/IDa, decType: int/float)
//------------------------------------------------------------------------
ds varDeclaration, funcVarDeclaration;//all variables created from newTemp are pushed here serially
dss arrVarDeclaration;	//all array variables
string currentFunction;	//currentFunction...need to be explained
map < string, bool > decLaredVar;
map < string, string > arrayMap;

template<typename T> ostream&
operator<<(ostream& os, const vector<T> &t) { unsigned n = t.size(); for(int i = 0; i < n; i++) os<<t[i]<<" "; return os; }
template<typename T, typename TT>
ostream& operator<<(ostream &os, const pair<T,TT> &t) { return os<<"("<<t.first<<", "<<t.second<<")"; }


char *newLabel()	//return format L0 / L1
{
	char *lb = new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()		//return format t0 / t3
{
	char *t = new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	return t;
}

//void optimization(FILE *asmcode);
string definedVariables();
string definedArrays();
string defineProcRINTLN();
void printICG(string icg);
void printOptimizedICG(string nonOptimizedICG);

//--------------------------------------------------------------------------
%}

%error-verbose
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


start :	program {	//okay.... asm baki ache
					//write your code/action in this block in all the similar blocks below
					if(!error_count) {
						string icg = ".MODEL SMALL\n\.STACK 100H\n\.DATA\n";
						icg += definedVariables();
						icg += definedArrays();
						icg += ".CODE\n" + $1->getAsmCode();//eikahne vitor theke code ra berate eshe bondi hoye jabe...
						icg += defineProcRINTLN();
						icg += "\t\tEND MAIN\n";
						printICG(icg);
						printOptimizedICG(icg);
					} else {
						cerr << "#[errors.....Segmentation Fault.....during code compilation]" << endl;
					}
				}
			;


program	:	program unit {	//okay....asm done..ymm
						//fprintf(logFile, "At line no: %d program : program unit\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName($1->getName() + "\n" + $2->getName());//newline added for simplicity?
						//fprintf(logFile, "%s\n\n", $$->getName().c_str());
						$$->setAsmCode($1->getAsmCode() + $2->getAsmCode());
					}
				|	unit {
						//fprintf(logFile, "At line no: %d program : unit\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName($1->getName());
						//fprintf(logFile, "%s\n\n", $$->getName().c_str());
						$$->setAsmCode($1->getAsmCode());
					}
				;


unit 	:	var_declaration {		//okay...asm done
					//fprintf(logFile, "At line no: %d unit : var_declaration\n\n", line_count);
					$$ = new SymbolInfo();
					$$->setName($1->getName() + "\n");
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					funcVarDeclaration.clear(); // keno korlam??
					$$->setAsmCode($1->getAsmCode());
				}
			|	func_declaration {
			 		//fprintf(logFile, "At line no: %d unit : func_declaration\n\n", line_count);
			 		$$ = new SymbolInfo();
					$$->setName($1->getName() + "\n");
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					$$->setAsmCode($1->getAsmCode());
			 	}
			|	func_definition {
			 		//fprintf(logFile, "At line no: %d unit : func_definition\n\n", line_count);
			 		$$ = new SymbolInfo();
					$$->setName($1->getName() + "\n");
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					$$->setAsmCode($1->getAsmCode());
			 	}
			;


func_declaration :	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON {	//okay...asm done...contains no asm actually
											//fprintf(logFile, "At line no: %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n", line_count);
											$$ = new SymbolInfo();
											SymbolInfo *symfo = symbolTable->lookUp($2->getName());
											if(symfo) {	//previously declared though redundant but okay for our grammar
										 		if(symfo->getFunctionDetails()->getParamCount() != paramList.size()) {
										 			error_count++;
										 			fprintf(logFile, "Error at line %d: Invalid number of parameters\n\n", line_count);
										 		} else {
										 			deque<string> paramTypeTempList = symfo->getFunctionDetails()->getArgTypeList();
													for(int i = 0; i < paramList.size(); i++) {
														if(paramList[i]->getDeclareType() != paramTypeTempList[i]) {
															error_count++;
															fprintf(logFile, "Error at line %d: Type Mismatch \n",line_count);
															break;
														}
													}
													if($1->getName() != symfo->getFunctionDetails()->getReturnType()) {
															error_count++;
															fprintf(logFile,"Error at line %d: Return Type Mismatch \n\n",line_count);
													}
										 		}
											} else {
												symbolTable->insert($2->getName(), "ID", "Function");
												symfo = symbolTable->lookUp($2->getName());
												for(int i = 0; i < paramList.size(); i++)
													symfo->getFunctionDetails()->addParameter(paramList[i]->getName(), paramList[i]->getDeclareType());
												symfo->getFunctionDetails()->setReturnType($1->getName());
											}
											$$->setName($1->getName()+" "+$2->getName()+"("+$4->getName()+");");
											//fprintf(logFile, "%s\n\n", $1->getName().c_str());
											//clear parameter list
											paramList.clear();
										}
								 |	type_specifier ID LPAREN RPAREN SEMICOLON {
									 		//fprintf(logFile, "At line no: %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n", line_count);
									 		$$ = new SymbolInfo();
											SymbolInfo *symfo = symbolTable->lookUp($2->getName());
											if(symfo) {
												if(symfo->getFunctionDetails()->getParamCount()) {
													error_count++;
													fprintf(logFile, "Error at line %d:  Invalid number of parameters \n\n", line_count);
												}
												if(symfo->getFunctionDetails()->getReturnType() !=  $1->getName()) {
													error_count++;
													fprintf(logFile, "Error at line %d: Return Type Mismatch \n\n", line_count);
												}
											} else {
												symbolTable->insert($2->getName(), "ID", "Function");
												symfo = symbolTable->lookUp($2->getName());
												symfo->getFunctionDetails()->setReturnType($1->getName());
											}
											$$->setName($1->getName() + " " + $2->getName() + "();");
											//fprintf(logFile, "%s\n\n", $$->getName().c_str());
											//clear parameter list redundant...anyway
											paramList.clear();
									 	}
									;

func_definition :	type_specifier ID LPAREN parameter_list RPAREN { //okay....asm done
										$$ = new SymbolInfo();
										SymbolInfo *symfo = symbolTable->lookUp($2->getName());
										if(symfo) {
											if(!symfo->getFunctionDetails()->isDefined1()) {
												$$->setDeclareType(symfo->getFunctionDetails()->getReturnType());
												if(paramList.size() != symfo->getFunctionDetails()->getParamCount()) {
													error_count++;
													fprintf(logFile, "Error at line %d: Invalid number of parameters\n\n", line_count);
												}
												else {
													//cout<<symfo->getFunctionDetails()->getArgTypeList().size() << " " << paramList.size()<<endl;
													ds paramTypeList = symfo->getFunctionDetails()->getArgTypeList();
													for(int i = 0; i < paramList.size(); i++) {
														if(paramList[i]->getDeclareType() != paramTypeList[i]) {
															error_count++;
															fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
															break;
														}
													}
													if(symfo->getFunctionDetails()->getReturnType() != $1->getName()) {
															error_count++;
															fprintf(logFile,"Error at line %d: Return Type Mismatch\n\n", line_count);
													}
												}
												symfo->getFunctionDetails()->clearFunction();
												for(int i = 0; i < paramList.size(); i++) {
													string procName = paramList[i]->getName() + toString(symbolTable->getNextScopeID());
													//cout<<procName<<endl;
													symfo->getFunctionDetails()->addParameter(procName, paramList[i]->getDeclareType());
												}
												symfo->getFunctionDetails()->setIsDefined(true);
											} else {
												error_count++;
												fprintf(logFile, "Error at line %d:  Multiple defination of function\t%s\n\n", line_count, $2->getName().c_str());
											}
										} else {
											symbolTable->insert($2->getName(), "ID", "Function");
											symfo = symbolTable->lookUp($2->getName());
											symfo->getFunctionDetails()->setIsDefined();
											for(int i = 0; i < paramList.size(); i++){
												string procName = paramList[i]->getName() + toString(symbolTable->getNextScopeID());
												//cout<<procName<<endl;
												symfo->getFunctionDetails()->addParameter(procName, paramList[i]->getDeclareType());
											}
											symfo->getFunctionDetails()->setReturnType($1->getName());
										}
										//cout<<"### : "+$2->getName() + "_FunRetVar"<<endl;
										if($1->getName() != "void ") {
											varDeclaration.push_back($2->getName() + "_FunRetVar");
											decLaredVar[$2->getName() + "_FunRetVar"] = true;
										}
										currentFunction = $2->getName();
										//cout<<currentFunction<<endl;
									} compound_statement {	//code kora holo
										//fprintf(logFile, "At line no: %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n", line_count);
										$$->setName($1->getName() + " " + $2->getName() + "(" + $4->getName() + ")" + $7->getName());
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										string codeSegment = $2->getName() + " PROC\n";
										if($2->getName() == "main") {
											codeSegment += "\tMOV AX, @DATA\n";
											codeSegment += "\tMOV DS, AX\n\n";
											codeSegment += $7->getAsmCode();
											codeSegment += "RETURN_LABEL_" + currentFunction + ":\n";
											codeSegment += "\n\tMOV AH, 4CH\n";
											codeSegment += "\tINT 21H\n";
											codeSegment += "main ENDP\n";
											$$->setAsmCode(codeSegment);
										}
										else {
											SymbolInfo *symfo = symbolTable->lookUp($2->getName());
											for(int i = 0; i < funcVarDeclaration.size(); i++) {
												symfo->getFunctionDetails()->addFuncVar(funcVarDeclaration[i]);
											}
											funcVarDeclaration.clear();
											codeSegment += "\tPUSH AX\n";
											codeSegment += "\tPUSH BX\n";
											codeSegment += "\tPUSH CX\n";
											codeSegment += "\tPUSH DX\n";
											ds tempParamList = symfo->getFunctionDetails()->getArgList();
											for(int i = 0; i < tempParamList.size(); i++) codeSegment += "\tPUSH " + tempParamList[i] + "\n";
											ds tempVarList = symfo->getFunctionDetails()->getFuncVarList();
											for(int i = 0; i < tempVarList.size(); i++) codeSegment += "\tPUSH " + tempVarList[i] + "\n";
											codeSegment += $7->getAsmCode();
											codeSegment += "RETURN_LABEL_" + currentFunction + ":\n";
											for(int i = 0; i < tempVarList.size(); i++) codeSegment += "\tPOP " + tempVarList[tempVarList.size()-1-i] + "\n";
											for(int i = 0; i < tempParamList.size(); i++) codeSegment += "\tPOP " + tempParamList[tempParamList.size()-1-i] + "\n";
											codeSegment += "\tPOP DX\n";
											codeSegment += "\tPOP CX\n";
											codeSegment += "\tPOP BX\n";
											codeSegment += "\tPOP AX\n";
											codeSegment += "\tret\n";
											$$->setAsmCode(codeSegment + $2->getName() + " ENDP\n\n");
										}
									}
								|	type_specifier ID LPAREN RPAREN {	//okay totally
										$$ = new SymbolInfo();
										SymbolInfo *symfo = symbolTable->lookUp($2->getName());
										if(!symfo){	//doesn't declared yet
											symbolTable->insert($2->getName(), "ID", "Function");
											symfo = symbolTable->lookUp($2->getName());
											symfo->getFunctionDetails()->setIsDefined();
											symfo->getFunctionDetails()->setReturnType($1->getName());
										}
										else if(!symfo->getFunctionDetails()->isDefined1()) { //doesn't defined yet
											if(symfo->getFunctionDetails()->getParamCount()) {
												error_count++;
												fprintf(logFile, "Error at line %d:  Invalid number of parameters\n\n", line_count);
											}
											if($1->getName() != symfo->getFunctionDetails()->getReturnType()) {
												error_count++;
												fprintf(logFile, "Error at line %d: Return Type Mismatch\n\n", line_count);
											}
											symfo->getFunctionDetails()->setIsDefined();
										}
										else {
											error_count++;
											fprintf(logFile, "Error at line %d:  Multiple defination of function %s\n\n", line_count, $2->getName().c_str());
										}
										$1->setName($1->getName() + " " + $2->getName() + "()");
										if($1->getName() != "void ") {
											varDeclaration.push_back($2->getName() + "_FunRetVar");
											decLaredVar[$2->getName() + "_FunRetVar"] = true;
										}
										currentFunction = $2->getName();

									} compound_statement {	//code kora holo
										//fprintf(logFile, "At line no: %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n", line_count);
										$$->setName($1->getName() + $6->getName());
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());

										string codeSegment = $2->getName() + " PROC\n";
										if($2->getName() == "main") {
											codeSegment += "\tMOV AX, @DATA\n";
											codeSegment += "\tMOV DS, AX\n\n";
											codeSegment += $6->getAsmCode();
											codeSegment += "RETURN_LABEL_" + currentFunction + ":\n";
											codeSegment += "\n\tMOV AH, 4CH\n";
											codeSegment += "\tINT 21H\n";
											codeSegment += "main ENDP\n";
											$$->setAsmCode(codeSegment);
										} else {
											SymbolInfo *symfo = symbolTable->lookUp($2->getName());
											for(int i = 0; i < funcVarDeclaration.size(); i++) {
												symfo->getFunctionDetails()->addFuncVar(funcVarDeclaration[i]);
											}
											funcVarDeclaration.clear();
											codeSegment += "\tPUSH AX\n";
											codeSegment += "\tPUSH BX\n";
											codeSegment += "\tPUSH CX\n";
											codeSegment += "\tPUSH DX\n";
											ds tempParamList = symfo->getFunctionDetails()->getArgList();
											ds tempVarList = symfo->getFunctionDetails()->getFuncVarList();
											for(int i = 0; i < tempParamList.size(); i++) codeSegment += "\tPUSH " + tempParamList[i] + "\n";
											for(int i = 0; i < tempVarList.size(); i++) codeSegment += "\tPUSH " + tempVarList[i] + "\n";
											codeSegment += $6->getAsmCode();
											codeSegment += "RETURN_LABEL_" + currentFunction + ":\n";
											for(int i = 0; i < tempVarList.size(); i++) codeSegment += "\tPOP " + tempVarList[tempVarList.size()-1-i] + "\n";
											for(int i = 0; i < tempParamList.size(); i++) codeSegment += "\tPOP " + tempParamList[tempParamList.size()-1-i] + "\n";
											codeSegment += "\tPOP DX\n";
											codeSegment += "\tPOP CX\n";
											codeSegment += "\tPOP BX\n";
											codeSegment += "\tPOP AX\n";
											codeSegment += "\tret\n";
											$$->setAsmCode(codeSegment + $2->getName() + " ENDP\n\n");
										}
								  }
				 				;

parameter_list	:	parameter_list COMMA type_specifier ID {	//okay....asm done
										//fprintf(logFile, "At line no: %d parameter_list : parameter_list COMMA type_specifier ID\n\n", line_count);
										$$ = new SymbolInfo();
										$$->setName($1->getName() + ", " + $3->getName()+" "+$4->getName());
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										paramList.push_back(new SymbolInfo($4->getName(), "ID", $3->getName()));
									}
						    |	parameter_list COMMA type_specifier {
						    		//fprintf(logFile, "At line no: %d parameter_list : parameter_list COMMA type_specifier\n\n", line_count);
										$$ = new SymbolInfo();
										$$->setName($1->getName()+", "+$3->getName());
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										paramList.push_back(new SymbolInfo("", "ID", $3->getName()));
						   		}
								|	type_specifier ID {
										//fprintf(logFile, "At line no: %d parameter_list : type_specifier ID\n\n", line_count);
										$$ = new SymbolInfo();
										$$->setName($1->getName() + " " + $2->getName());
						 				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										paramList.push_back(new SymbolInfo($2->getName(), "ID", $1->getName()));
									}
								|	type_specifier {
										//fprintf(logFile, "At line no: %d parameter_list : type_specifier\n\n", line_count);
										$$ = new SymbolInfo();
										$$->setName($1->getName()+" ");
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										paramList.push_back(new SymbolInfo("", "ID", $1->getName()));
									}
								;

compound_statement	:	LCURL {		//okay....asm done
												symbolTable->enterScope();
												for(int i = 0; i < paramList.size(); i++) {
													symbolTable->insert(paramList[i]->getName(), "ID", paramList[i]->getDeclareType());
													varDeclaration.push_back(paramList[i]->getName() + toString(symbolTable->getCurrentScopeID()));
												}
												//clear the paramList
												paramList.clear();
											} statements RCURL {
												//fprintf(logFile, "At line no: %d compound_statement : LCURL statements RCURL\n\n", line_count);
												$$ = new SymbolInfo();
												$$->setName("{\n" + $3->getName() + "\n}");
												//fprintf(logFile, "%s\n\n", $$->getName().c_str());
												$$->setAsmCode($3->getAsmCode());
												//symbolTable->printAllScopeTable();
												symbolTable->exitScope();
											}
				 		    		|	LCURL RCURL {
												symbolTable->enterScope();
												for(int i = 0; i < paramList.size(); i++) {
													symbolTable->insert(paramList[i]->getName(), "ID", paramList[i]->getDeclareType());
													varDeclaration.push_back(paramList[i]->getName() + toString(symbolTable->getCurrentScopeID()));
												}
												//clear the paramList
												paramList.clear();
												//fprintf(logFile, "At line no: %d compound_statement : LCURL RCURL\n\n{}\n\n", line_count);
												$$ = new SymbolInfo();
												$$->setName("{}");
												//symbolTable->printAllScopeTable();
												symbolTable->exitScope();
				 		    			}
				 		    		;

var_declaration	:	type_specifier declaration_list SEMICOLON {		//okay....updated and asm done
						//fprintf(logFile, "At line no: %d var_declaration : type_specifier declaration_list SEMICOLON\n\n",line_count);
						if($1->getName() == "void "){
							error_count++;
							fprintf(logFile, "Error at line %d: TYpe specifier can not be void\n\n", line_count);
						} else for(int i = 0; i < decList.size(); i++) {
							if(symbolTable->lookUpCurrentScope(decList[i]->getName())) { //previously declared
								error_count++;
								fprintf(logFile, "Error at line %d:  Multiple Declaration of %s \n\n", line_count, decList[i]->getName().c_str());
							} else if(decList[i]->getType().length() >= 3) {		//eita kintu update korsi IDarray_length format theke ID array_lenght
								string arrType = decList[i]->getType().substr(0, 2);
								string arrLength = decList[i]->getType().substr(2);
								arrVarDeclaration.push_back({decList[i]->getName() + toString(symbolTable->getCurrentScopeID()), arrLength});
								decList[i]->setType(arrType);
								symbolTable->insert(decList[i]->getName(), decList[i]->getType(), $1->getName() + "array");
								//cout<<$1->getName() + "array"<<endl; // format be like int array or float array
							} else {
								funcVarDeclaration.push_back(decList[i]->getName() + toString(symbolTable->getCurrentScopeID()));
								symbolTable->insert(decList[i]->getName(), decList[i]->getType(), $1->getName());
								varDeclaration.push_back(decList[i]->getName() + toString(symbolTable->getCurrentScopeID()));
							}
						}
						$$ = new SymbolInfo();
						$$->setName($1->getName() + " " + $2->getName() + ";");
						//fprintf(logFile, "%s\n\n", $$->getName().c_str());
						//clear the decList
						decList.clear();
					}
 		 		;

type_specifier	:	INT {		//okay.....asm done
										//fprintf(logFile, "At line no: %d type_specifier : INT\n\n", line_count);
										$$ = new SymbolInfo();
										$$->setName("int ");
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
									}
				 				|	FLOAT {
										//fprintf(logFile, "At line no: %d type_specifier : FLOAT\n\n", line_count);
										$$ = new SymbolInfo();
										$$->setName("float ");
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				 					}
				 				|	VOID {
										//fprintf(logFile, "At line no: %d type_specifier : VOID\n\n", line_count);
										$$ = new SymbolInfo();
										$$->setName("void ");
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				 					}
				 				;

declaration_list	:	declaration_list COMMA ID {		//okay.....updated and asm done
							//fprintf(logFile, "At line no: %d declaration_list : declaration_list COMMA ID\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setName($1->getName() + "," + $3->getName());
							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
							decList.push_back(new SymbolInfo($3->getName(), "ID"));
						}
 		  			|	declaration_list COMMA ID LTHIRD CONST_INT RTHIRD {
	 		  				//fprintf(logFile, "At line no: %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n", line_count);
								$$ = new SymbolInfo();
								$$->setName($1->getName() + "," + $3->getName() + "[" + $5->getName() + "]");
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								//decList.push_back(new SymbolInfo($3->getName(), "array")); //....eita change korlam nicherta use kortesi
								decList.push_back(new SymbolInfo($3->getName(), "ID" + $5->getName()));
 		  				}
 		  			|	ID {
	 		  				//fprintf(logFile, "At line no: %d declaration_list : ID\n\n", line_count);
								$$ = new SymbolInfo();
								$$->setName($1->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
			   				decList.push_back(new SymbolInfo($1->getName(), "ID"));
 		  				}
 		  			|	ID LTHIRD CONST_INT RTHIRD {
	 		  				//fprintf(logFile, "At line no: %d declaration_list : ID LTHIRD CONST_INT RTHIRD\n%s\n\n", line_count, $3->getName().c_str());
								$$ = new SymbolInfo();
				   				$$->setName($1->getName() + "[" + $3->getName() + "]");
				   				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				   				//decList.push_back(new SymbolInfo($1->getName(), "array")); //....eita change korlam nicherta use kortesi
									decList.push_back(new SymbolInfo($1->getName(), "ID" + $3->getName()));
 		  				}
 		  			;


statements	:	statement {		//okay....asm done
								//fprintf(logFile, "\nAt line no: %d statements : statement\n\n",line_count);
								$$ = new SymbolInfo();
								$$->setName($1->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								$$->setAsmCode($1->getAsmCode());
							}
			   		|	statements statement {
								//fprintf(logFile, "At line no: %d statements : statements statement\n\n", line_count);
								$$ = new SymbolInfo();
								$$->setName($1->getName() + "\n" + $2->getName());
				   			//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				   			$$->setAsmCode($1->getAsmCode() + $2->getAsmCode());
			   			}
			   		;


statement 	:	var_declaration {	//okay.....asm done
								//fprintf(logFile, "At line no: %d statement : var_declaration\n\n", line_count);
								$$ = new SymbolInfo();
								$$->setName($1->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								//extra ASM is not needed...done using deque varDeclaration, arrVarDeclaration etc...
							}
			  		| expression_statement { //okay
			  				//fprintf(logFile, "At line no: %d statement : expression_statement\n\n", line_count);
			  				$$ = new SymbolInfo();
								$$->setName($1->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								$$->setAsmCode($1->getAsmCode());
			  			}
		  			| compound_statement { //okay
				 				//fprintf(logFile, "At line no: %d statement : compound_statement\n\n", line_count);
				 				$$ = new SymbolInfo();
								$$->setName($1->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								$$->setAsmCode($1->getAsmCode());
			  			}
	  				| FOR LPAREN expression_statement expression_statement expression RPAREN statement { //okay
			  				//fprintf(logFile, "At line no: %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n", line_count);
			  				$$ = new SymbolInfo();
								$$->setName("for(" + $3->getName() + " " + $4->getName() + " " + $5->getName() + ")\n" + $5->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								if($3->getDeclareType() == "void ") {
									error_count++;
									fprintf(logFile, "Error at line %d:  Type Mismatch\n\n", line_count);
								} else {
									string loopLabel = (string)newLabel(), endLabel = (string)newLabel();
									string codeSegment = $3->getAsmCode(); //$3's code at first, which is already done by assigning $$=$3
									codeSegment += loopLabel + ":\n";//create two labels and append one of them in $$->code
									codeSegment += $4->getAsmCode();
									codeSegment += "\tMOV AX, " + $4->getAsmSymbol() + "\n";
									codeSegment += "\tCMP AX, 0\n";//compare $4's symbol with 0
									codeSegment += "\tJE " + endLabel + "\n";//if equal jump to 2nd label
									codeSegment += $7->getAsmCode();//	append $7's code
									codeSegment += $5->getAsmCode();//	append $5's code
									//cout<<loopLabel<<endl;
									codeSegment += "\tJMP " + loopLabel + "\n";
									codeSegment += endLabel + ":\n";//append the second label in the code
									$$->setAsmCode(codeSegment);
								}
	  					}
			  		| IF LPAREN expression RPAREN statement	%prec	LOWER_THAN_ELSE { //okay
			  				//fprintf(logFile, "At line no: %d statement : IF LPAREN expression RPAREN statement\n\n",line_count);
			  				$$ = new SymbolInfo();
			  				if($3->getDeclareType() == "void ") {
									error_count++;
									fprintf(logFile, "Error at line %d: Type Mismatch\n\n",line_count);
									$$->setDeclareType("int ");
								} else {
									string endifLabel = (string)newLabel();
									//cout<<endifLabel<<endl;
									string codeSegment = $3->getAsmCode();
									codeSegment += "\tMOV AX, " + $3->getAsmSymbol() + "\n";
									codeSegment += "\tCMP AX, 0\n";
									codeSegment += "\tJE " + endifLabel + "\n";
									codeSegment += $5->getAsmCode();
									codeSegment += endifLabel + ":\n";
									$$->setAsmCode(codeSegment);
								}
								$$->setName("if(" + $3->getName() + ")\n" + $5->getName());
  							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
  						}
			  		| IF LPAREN expression RPAREN statement ELSE statement { // contains shift-reduce conflicts  //okay
			  				//fprintf(logFile, "At line no: %d statement : IF LPAREN expression RPAREN statement ELSE statement\n\n", line_count);
			  				$$ = new SymbolInfo();
								if($3->getDeclareType() == "void "){
									error_count++;
									fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
									$$->setDeclareType("int ");
								} else {
									string elseLabel = (string)newLabel(), endifLabel = (string)newLabel();
									string codeSegment = $3->getAsmCode();
									codeSegment += "\tMOV AX, " + $3->getAsmSymbol() + "\n";
									codeSegment += "\tCMP AX, 0\n";
									codeSegment += "\tJE " + elseLabel + "\n";
									codeSegment += $5->getAsmCode();
									codeSegment += "\tJMP " + endifLabel + "\n";
									codeSegment += elseLabel + ":\n";
									codeSegment += $7->getAsmCode();
									codeSegment += endifLabel + ":\n";
									$$->setAsmCode(codeSegment);
								}
								$$->setName("if(" + $3->getName() + ")\n" + $5->getName() + "\nelse\n" + $7->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
			  			}
		  			|	WHILE LPAREN expression RPAREN statement { //okay
			  				//fprintf(logFile, "At line no: %d statement : WHILE LPAREN expression RPAREN statement\n\n", line_count);
			  				$$ = new SymbolInfo();
						  	if($3->getDeclareType() == "void ") {
									error_count++;
									fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
									$$->setDeclareType("int ");
								} else {
									string whileLabel = (string)newLabel();
									string endWhileLabel = (string)newLabel();
									string codeSegment = whileLabel + ":\n";
								  codeSegment += $3->getAsmCode();
									codeSegment += "\tMOV AX, " + $3->getAsmSymbol() + "\n";
									codeSegment += "\tCMP AX, 0\n";
									codeSegment += "\tJE " + endWhileLabel + "\n";
									codeSegment += $5->getAsmCode();
									codeSegment += "\tJMP " + whileLabel + "\n";
									codeSegment += endWhileLabel + ":\n";
									$$->setAsmCode(codeSegment);
								}
						  	$$->setName("while(" + $3->getName() + ")\n" + $5->getName());
			  				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
  						}
			  		| PRINTLN LPAREN ID RPAREN SEMICOLON {	//okay
			  				//fprintf(logFile, "At line no: %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n", line_count);
			  				$$ = new SymbolInfo();
								$$->setName("\n(" + $3->getName() + ")");
			  				//fprintf(logFile, "%s;\n\n", $$->getName().c_str());
								// write code for printing an ID. You may assume that ID is an integer variable.
								if(symbolTable->getScopeID($3->getName()) == -1) {
									error_count++;
									fprintf(logFile, "Error at Line %d: Undeclared Variable: %s\n\n", line_count, $3->getName());
								}
								else{
									string assembledID = $3->getName() + toString(symbolTable->getScopeID($3->getName()));
									string codeSegment = "\tMOV AX, " + assembledID + "\n";
									$$->setAsmCode(codeSegment + "\tCALL PRINTLN\n");
								}
			  			}
  					| RETURN expression SEMICOLON { //okay
			  				//fprintf(logFile, "At line no: %d statement : RETURN expression SEMICOLON\n\n", line_count);
			  				$$ = new SymbolInfo();
								$$->setName("return " + $2->getName() + ";");
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								if($2->getDeclareType() == "void ") {
									error_count++;
									fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
									$$->setDeclareType("int ");
								} else {
									string codeSegment = $2->getAsmCode();
									codeSegment += "\tMOV AX, " + $2->getAsmSymbol() + "\n";
									//cout<<":::: "<<currentFunction<<" expression:::: "<<$2->getName()<<endl;
									string calleeRetVal = currentFunction + "_FunRetVar";
									if(decLaredVar.find(calleeRetVal) != decLaredVar.end())codeSegment += "\tMOV " + currentFunction + "_FunRetVar, AX\n"; // return na korle actually can't reach here
									codeSegment += "\tJMP RETURN_LABEL_" + currentFunction + "\n";
									$$->setAsmCode(codeSegment);
								}
							}
  					;


expression_statement	:	SEMICOLON {		//okay....asm done
													//fprintf(logFile, "At line no: %d expression_statement : SEMICOLON\n\n", line_count);
													$$ = new SymbolInfo();
													$$->setName(";");
													//fprintf(logFile, "%s\n\n", $$->getName().c_str());
												}
											|	expression SEMICOLON {
													//fprintf(logFile, "At line no: %d expression_statement : expression SEMICOLON\n\n", line_count);
													$$ = new SymbolInfo();
													$$->setName($1->getName() + ";");
													//fprintf(logFile, "%s\n\n", $$->getName().c_str());
													$$->setAsmCode($1->getAsmCode());
													$$->setAsmSymbol($1->getAsmSymbol());
												}
											;


variable	:	ID {	//okay....asm done
					//fprintf(logFile, "At line no: %d variable : ID\n\n", line_count);
					$$ = new SymbolInfo();
					if(!symbolTable->lookUp($1->getName()) || (symbolTable->lookUp($1->getName())->getDeclareType() == "int array" || symbolTable->lookUp($1->getName())->getDeclareType() == "float array")) {//exist kore na...ir array type
						error_count++;
						fprintf(logFile, "Error at line %d: Undeclared Variable / Non array assigning on array: %s\n\n", line_count, $1->getName().c_str());
					} else if(symbolTable->lookUp($1->getName())) {
						$$->setDeclareType(symbolTable->lookUp($1->getName())->getDeclareType());
						$$->setAsmSymbol( $1->getName() + toString(symbolTable->getScopeID($1->getName())));
					}
					$$->setName($1->getName());
					$$->setType("notarray");
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					//cout<<line_count<<":  "<<$$->getName()<<" "<<$$->getAsmCode()<< " " << $$->getAsmSymbol()<<" "<< $$->getType()<<endl;
				}
	 		|	ID LTHIRD expression RTHIRD {
	 				//fprintf(logFile, "At line no: %d variable : ID LTHIRD expression RTHIRD\n\n", line_count);
	 				$$ = new SymbolInfo();
					//$$->setType("array");
					if(!symbolTable->lookUp($1->getName())) {
						error_count++;
						fprintf(logFile, "Error at line %d: Undeclared Variable: %s\n\n", line_count, $1->getName().c_str());
					}
					if($3->getDeclareType() != "int ") {
						error_count++;
						fprintf(logFile, "Error at line %d: Non-integer Array Index\n\n", line_count);
					}
					if(symbolTable->lookUp($1->getName())) {
						if(symbolTable->lookUp($1->getName())->getDeclareType() != "int array" &&
							symbolTable->lookUp($1->getName())->getDeclareType() != "float array") {
							error_count++;
							fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
						} else {
							if(symbolTable->lookUp($1->getName())->getDeclareType() == "int array") $1->setDeclareType("int ");
							if(symbolTable->lookUp($1->getName())->getDeclareType() == "float array") $1->setDeclareType("float ");
							$$->setDeclareType($1->getDeclareType());
							//assembled
							$$->setAsmCode($3->getAsmCode() + "\tMOV BX, " + $3->getAsmSymbol() + "\n" + "\tADD BX, BX\n");
							$$->setAsmSymbol($1->getName() + toString(symbolTable->getScopeID($1->getName())));
							//map e BX er indx ta save kore rakhbo.............cause BX harai jacche
							string tempo = (string)newTemp();
							varDeclaration.push_back(tempo);
							$$->setAsmCode($$->getAsmCode() + "\tMOV " + tempo + ", BX\n");// temp variable
							//SymbolInfo* diye mapping hobe....anyway multiple array at multiple scope with same name can cause harm...not sure
							arrayMap[$1->getName() + "[" + $3->getName() + "]" + "array"] = tempo;// chine rakhlam
						}
					}
	 				$$->setName($1->getName() + "[" + $3->getName() + "]");
					//cout<<arrayMap[$$->getName()]<<endl;
					$$->setType("array");
					//cout<<line_count<< " " + $$->getAsmCode()<<" "<<$$->getAsmSymbol()<<endl;

	 				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
	 			}
	 		;


expression 	:	logic_expression {	//okay....asm done
					//fprintf(logFile, "At line no: %d expression : logic_expression\n\n", line_count);
					$$ = new SymbolInfo();
					$$->setName($1->getName());
					$$->setDeclareType($1->getDeclareType());
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					$$->setAsmCode($1->getAsmCode());
					$$->setAsmSymbol($1->getAsmSymbol());
				}
			|	variable ASSIGNOP logic_expression {
					//fprintf(logFile, "At line no: %d expression : variable ASSIGNOP logic_expression\n\n", line_count);
					$$ = new SymbolInfo();
				  if($3->getDeclareType() == "void " || (symbolTable->lookUp($1->getName()) && (symbolTable->lookUp($1->getName())->getDeclareType() != $3->getDeclareType()))) {
						error_count++;
						fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
						if($3->getDeclareType() == "void ") $$->setDeclareType("int ");
					} else {
						string codeSegment = $1->getAsmCode() + $3->getAsmCode() + "\tMOV AX, " + $3->getAsmSymbol()+"\n";
						if($1->getType() == "notarray")
							codeSegment += "\tMOV " + $1->getAsmSymbol() + ", AX\n";
						else {
							if(arrayMap.find($1->getName() + $1->getType()) != arrayMap.end())	//update korlam
								codeSegment += "\tMOV BX, " + arrayMap[$1->getName() + $1->getType()] + "\n"; // MOV BX, temp ; BX ke update kore dilum
							else cout<<$1->getName()<<endl;
							codeSegment += "\tMOV " + $1->getAsmSymbol() + "[BX], AX\n";
						}
						$$->setAsmCode(codeSegment);
						$$->setAsmSymbol($1->getAsmSymbol());
					}
					$$->setDeclareType($1->getDeclareType());
					$$->setName($1->getName() + "=" + $3->getName());
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				}
			;


logic_expression	:	rel_expression {	//okay....asm done
										//fprintf(logFile, "At line no: %d logic_expression : rel_expression\n\n", line_count);
										$$ = new SymbolInfo();
										$$->setName($1->getName());
										$$->setDeclareType($1->getDeclareType());
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										$$->setAsmCode($1->getAsmCode());
										$$->setAsmSymbol($1->getAsmSymbol());
									}
					 			|	rel_expression LOGICOP rel_expression {
					 					//fprintf(logFile, "At line no: %d logic_expression : rel_expression LOGICOP rel_expression\n\n", line_count);
					 					$$ = new SymbolInfo();
					 					if($1->getDeclareType()!= "int " || $3->getDeclareType()!= "int ") { // float is not accepted in our assumption
											error_count++;
											fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
											//cout<<"#debug("<<14<<")"<<endl;
											$$->setDeclareType("int ");
										} else {
											string codeSegment = $1->getAsmCode() + $3->getAsmCode();
											char *assignLabel = newLabel();
											char *endLabel = newLabel();
											char *tempSymbol = newTemp();
											if($2->getName() == "&&") {
												codeSegment += "\tMOV AX, " + $1->getAsmSymbol() + "\n";
												codeSegment += "\tCMP AX, 0\n";
												codeSegment += "\tJE " + (string)assignLabel + "\n";
												codeSegment += "\tMOV AX, " + $3->getAsmSymbol() + "\n";
												codeSegment += "\tCMP AX, 0\n";
												codeSegment += "\tJE " + (string)assignLabel + "\n";
												codeSegment += "\tMOV " + (string)tempSymbol + ", 1\n";
												codeSegment += "\tJMP " + (string)endLabel + "\n";
												codeSegment += (string)assignLabel + ": ";
												codeSegment += "\tMOV " + (string)tempSymbol + ", 0\n";
												codeSegment += (string)endLabel + ": ";
											} else if($2->getName() == "||") {
												codeSegment += "\tMOV AX, " + $1->getAsmSymbol() + "\n";
												codeSegment += "\tCMP AX, 0\n";
												codeSegment += "\tJNE " + (string)assignLabel + "\n";
												codeSegment += "\tMOV AX, " + $3->getAsmSymbol() + "\n";
												codeSegment += "\tCMP AX, 0\n";
												codeSegment += "\tJNE " + (string)assignLabel + "\n";
												codeSegment += "\tMOV " + (string)tempSymbol + ", 0\n";
												codeSegment += "\tJMP " + (string)endLabel + "\n";
												codeSegment += (string)assignLabel + ":\n\tMOV " + (string)tempSymbol + ", 1\n";
												codeSegment += (string)endLabel + ":\n";
											}
											$$->setAsmCode(codeSegment);
											$$->setAsmSymbol(tempSymbol);
											varDeclaration.push_back(tempSymbol);
										}
							 			$$->setDeclareType("int ");
							$$->setName($1->getName() + $2->getName() + $3->getName());
							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
		 				}
		 			;


rel_expression	:	simple_expression {	 //okay....asm done
						//fprintf(logFile, "At line no: %d rel_expression : simple_expression\n\n", line_count);
						$$ = new SymbolInfo();
						$$->setName($1->getName());
						$$->setDeclareType($1->getDeclareType());
						$$->setAsmCode($1->getAsmCode());
						$$->setAsmSymbol($1->getAsmSymbol());
						//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					}
				|	simple_expression RELOP simple_expression {
						//fprintf(logFile, "At line no: %d rel_expression : simple_expression RELOP simple_expression\n\n", line_count);
						$$ = new SymbolInfo();
						if($1->getDeclareType() == "void " || $3->getDeclareType() == "void ") {
							error_count++;
							fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
							$$->setDeclareType("int ");
						} else {
							string codeSegment = $1->getAsmCode() + $3->getAsmCode();
							codeSegment += "\tMOV AX, " + $1->getAsmSymbol() + "\n";
							codeSegment += "\tCMP AX, " + $3->getAsmSymbol() + "\n";
							char *tempSymbol = newTemp();
							char *assignLabel = newLabel();
							char *endLabel = newLabel();
							if($2->getName() == "<") {
								codeSegment += "\tJL " + (string)assignLabel + "\n";
							}
							else if($2->getName() == "<=") {
								codeSegment += "\tJLE " + (string)assignLabel + "\n";
								//cout<<(string)assignLabel<<endl;
							}
							else if($2->getName() == ">") {
								codeSegment += "\tJG " + (string)assignLabel + "\n";
							}
							else if($2->getName() == ">=") {
								codeSegment += "\tJGE " + (string)assignLabel + "\n";
							}
							else if($2->getName() == "==") {
								codeSegment += "\tJE " + (string)assignLabel + "\n";
							}
							else{
								codeSegment += "\tJNE " + (string)assignLabel + "\n";
							}
							codeSegment += "\tMOV " + string(tempSymbol) +", 0\n";
							codeSegment += "\tJMP " + string(endLabel) +"\n";
							codeSegment += (string)assignLabel + ":\n\tMOV " + string(tempSymbol) + ", 1\n";
							codeSegment += string(endLabel) + ":\n";
							$$->setAsmCode(codeSegment);
							$$->setAsmSymbol(tempSymbol);
							varDeclaration.push_back(tempSymbol);
						}
			 			$$->setDeclareType("int ");
						$$->setName($1->getName() + $2->getName() + $3->getName());
						//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					}
				;


simple_expression	:	term {	//okay.....asm done
							//fprintf(logFile, "At line no: %d simple_expression : term\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setDeclareType($1->getDeclareType());
							$$->setName($1->getName());
							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
							$$->setAsmCode($1->getAsmCode());
							$$->setAsmSymbol($1->getAsmSymbol());
						}
		  			|	simple_expression ADDOP term {
								//fprintf(logFile, "At line no: %d simple_expression : simple_expression ADDOP term\n\n", line_count);
								$$= new SymbolInfo();
								if($1->getDeclareType() == "void " || $3->getDeclareType() == "void ") {
									error_count++;
									fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
									$$->setDeclareType("int ");
								} else if($1->getDeclareType() == "float " || $3->getDeclareType() == "float ") {
									$$->setDeclareType("float ");
								} else $$->setDeclareType("int ");
								$$->setName($1->getName() + $2->getName() + $3->getName());
			  				//fprintf(logFile, "%s\n", $$->getName().c_str());
								string codeSegment = $1->getAsmCode() + $3->getAsmCode();
								codeSegment += "\tMOV AX, " + $1->getAsmSymbol() + "\n";
								char *tempSymbol = newTemp();
								if($2->getName() == "+")
									codeSegment += "\tADD AX, " + $3->getAsmSymbol() + "\n";
								else
									codeSegment += "\tSUB AX, " + $3->getAsmSymbol() + "\n";
								codeSegment += "\tMOV " + string(tempSymbol) + ", AX\n";
								$$->setAsmCode(codeSegment);
								$$->setAsmSymbol(tempSymbol);
								varDeclaration.push_back(tempSymbol);
		  				}
		  			;


term	:	unary_expression {	//okay....asm done
				//fprintf(logFile, "At line no: %d term : unary_expression\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType($1->getDeclareType());
				$$->setName($1->getName());
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				$$->setAsmCode($1->getAsmCode());
				$$->setAsmSymbol($1->getAsmSymbol());
			}
     	|	term MULOP unary_expression {
					//fprintf(logFile, "At line no: %d term : term MULOP unary_expression\n\n", line_count);
		 			$$ = new SymbolInfo();
		 			if($1->getDeclareType() == "void " || $3->getDeclareType() == "void ") {
					 	error_count++;
					 	fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
					 	$$->setDeclareType("int ");
					} else if($2->getName() == "%" && ($1->getDeclareType() != "int " || $3->getDeclareType() != "int ")) {
						error_count++;
						fprintf(logFile, "Error at line %d: Integer operand on modulus operator\n\n", line_count);
						$$->setDeclareType("int ");
					} else if($2->getName() == "/") {
						if($1->getDeclareType() == "void " || $3->getDeclareType() == "void ") {
							error_count++;
							fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
							$$->setDeclareType("int ");
						} else if($1->getDeclareType() == "int " && $3->getDeclareType() == "int ")
							$$->setDeclareType("int ");
						else $$->setDeclareType("float ");
					} else if($1->getDeclareType() == "float " || $3->getDeclareType() == "float ")
						 	$$->setDeclareType("float ");
					else $$->setDeclareType("int ");

					$$->setName($1->getName() + $2->getName() + $3->getName());
     			//fprintf(logFile, "%s\n", $$->getName().c_str());
					if(!($1->getDeclareType() == "void " || $3->getDeclareType() == "void ")) {
						string codeSegment = $1->getAsmCode() + $3->getAsmCode();
						codeSegment += "\tMOV AX, " + $1->getAsmSymbol() + "\n";
						codeSegment += "\tMOV BX, " + $3->getAsmSymbol() + "\n";
						char *tempSymbol = newTemp();
						if($2->getName() == "*"){
							codeSegment += "\tMUL BX\n";
							codeSegment += "\tMOV "+ string(tempSymbol) + ", AX\n";
						}
						else if($2->getName() == "/"){
							// clear dx, perform 'div bx' and mov ax to temp
							codeSegment += "\tMOV DX, 0\n";
							codeSegment += "\tDIV BX\n";
							codeSegment += "\tMOV " + string(tempSymbol) + ", AX\n";
						}
						else{
							// clear dx, perform 'div bx' and mov dx to temp
							codeSegment += "\tMOV DX, 0\n";
							codeSegment += "\tDIV BX\n";
							codeSegment += "\tMOV " + string(tempSymbol) + ", DX\n";
						}
						$$->setAsmSymbol(tempSymbol);
						$$->setAsmCode(codeSegment);
						varDeclaration.push_back(tempSymbol);
					}
     		}
     	;


unary_expression	:	ADDOP unary_expression {	//okay....asm done
							//fprintf(logFile, "At line no: %d unary_expression : ADDOP unary_expression\n\n", line_count);
							$$ = new SymbolInfo();
							if($2->getDeclareType() == "void "){
								error_count++;
								fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
								//cout<<"#debug("<<20<<")"<<endl;
								$$->setDeclareType("int ");
							} else {
								$$->setAsmSymbol($2->getAsmSymbol());
								string codeSegment = $2->getAsmCode();
								if($1->getName() == "-") {
									codeSegment += "\tMOV AX, " + $$->getAsmSymbol() + "\n\tNEG AX\n";
									codeSegment += "\tMOV " + $$->getAsmSymbol() + ", AX\n";
								}
								$$->setAsmCode(codeSegment);
								$$->setDeclareType($2->getDeclareType());
							}
							$$->setName($1->getName() + $2->getName());
							//fprintf(logFile, "%s%s\n", $$->getName().c_str());
						}
		 			|	NOT unary_expression {
		 					//fprintf(logFile, "At line no: %d unary_expression : NOT unary_expression\n\n", line_count);
							$$ = new SymbolInfo();
							if($2->getDeclareType() == "void "){
								error_count++;
								fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
								$$->setDeclareType("int ");
							} else {
								$$->setAsmSymbol($2->getAsmSymbol());
								string codeSegment = $2->getAsmCode();
								codeSegment += "\tMOV AX, " + $$->getAsmSymbol() + "\n\tNOT AX\n";
								codeSegment += "\tMOV " + $$->getAsmSymbol() + ", AX\n";
								$$->setAsmCode(codeSegment);
								$$->setDeclareType($2->getDeclareType());
							}
							$$->setName("!" + $2->getName());
							//fprintf(logFile, "!%s\n\n", $$->getName().c_str());
		 				}
		 			|	factor {
		 					//fprintf(logFile, "At line no: %d unary_expression : factor\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setDeclareType($1->getDeclareType());
							$$->setName($1->getName());
							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
							$$->setAsmCode($1->getAsmCode());
							$$->setAsmSymbol($1->getAsmSymbol());
		 				}
		 			;


factor	:	variable {	//okay.....asm done
				//ERROR declared here.....
				///if($1->getDeclareType() == "int array")$1->setName("error"); // kind of error recovery....but we consider no error in input.c file
				//fprintf(logFile, "At line no: %d factor : variable\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setName($1->getName());
				$$->setDeclareType($1->getDeclareType());
				//why we do that here
				string str = "";
				for(int i = 0; i < $$->getName().size(); i++)
					if($$->getName()[i] == '[')break;
					else str += $$->getName()[i];
				$$->setName(str);
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());

				//generate assembly code
				string codeSegment = $1->getAsmCode();
				if($1->getType() == "notarray") {
					$$->setAsmSymbol($1->getAsmSymbol());
				} else {
					char *tempSymbol = newTemp();
					codeSegment += "\tMOV AX, " + $1->getAsmSymbol() + "[BX]\n";
					codeSegment += "\tMOV " + string(tempSymbol) + ", AX\n";
					$$->setAsmSymbol(tempSymbol);
					varDeclaration.push_back(tempSymbol);
				}
				$$->setAsmCode(codeSegment);
			}
		|	ID LPAREN argument_list RPAREN {
				//fprintf(logFile, "At line no: %d factor : ID LPAREN argument_list RPAREN\n\n", line_count);
				SymbolInfo* symfo = symbolTable->lookUp($1->getName());
				if(!symfo) { //nai
					error_count++;
					fprintf(logFile, "Error at line %d:  Undefined Function\n\n", line_count);
					$$->setDeclareType("int ");
				}
				else if(!symfo->getFunctionDetails()) { //ache but func na
					error_count++;
					fprintf(logFile, "Error at line %d:  Not A Function\n\n", line_count);
					$$->setDeclareType("int ");
				}
				else if(!symfo->getFunctionDetails()->isDefined1()) {
					error_count++;
					fprintf(logFile, "Error at line %d: Undeclared Function\n\n", line_count);
				} else {
					int num = symfo->getFunctionDetails()->getParamCount();
					$$->setDeclareType(symfo->getFunctionDetails()->getReturnType());
					if(num != argList.size()) {
						error_count++;
						fprintf(logFile, "Error at line %d: Invalid number of arguments\n\n", line_count);
					} else{
						ds tempVarList = symbolTable->lookUp($1->getName())->getFunctionDetails()->getFuncVarList();
						ds tempParamTypeList = symbolTable->lookUp($1->getName())->getFunctionDetails()->getArgTypeList();
						ds tempParamList = symbolTable->lookUp($1->getName())->getFunctionDetails()->getArgList();
						string codeSegment = $3->getAsmCode();
						for(int i = 0; i < argList.size(); i++) {
							codeSegment += "\tMOV AX, " + argList[i]->getAsmSymbol() + "\n";
							codeSegment += "\tMOV " + tempParamList[i] + ", AX\n";
							if(argList[i]->getDeclareType() != tempParamTypeList[i]){
								error_count++;
								fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
								break;
							}
						}
						codeSegment += "\tCALL " + $1->getName() + "\n";
						string calleeRetVal = $1->getName() + "_FunRetVar";
						if(decLaredVar.find(calleeRetVal) != decLaredVar.end()) 	codeSegment += "\tMOV AX, " + calleeRetVal + "\n";
						//codeSegment += "\tMOV AX, " + $1->getName() + "_FunRetVar\n";
						string tempSymbol = (string)newTemp();
						codeSegment += "\tMOV " + tempSymbol + ", AX\n";
						$$->setAsmSymbol(tempSymbol);
						$$->setAsmCode(codeSegment);
						varDeclaration.push_back(tempSymbol);
					}
				}
				argList.clear();
				$$->setName($1->getName() + "( " + $3->getName() + " )");
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
			}
		|	LPAREN expression RPAREN {
				//fprintf(logFile, "At line no: %d factor : LPAREN expression RPAREN\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType($2->getDeclareType());
				$$->setName("(" + $2->getName() + ")");
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				$$->setAsmCode($2->getAsmCode());
				$$->setAsmSymbol($2->getAsmSymbol());
			}
		|	CONST_INT {
				//fprintf(logFile, "At line no: %d factor : CONST_INT\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType("int ");
				$$->setName($1->getName());
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				string tempSymbol = (string)newTemp();
				string codeSegment = "\tMOV " + tempSymbol + ", " + $1->getName() + "\n";
				$$->setAsmCode(codeSegment);
				$$->setAsmSymbol(tempSymbol);
				varDeclaration.push_back(tempSymbol);
			}
		|	CONST_FLOAT {
				//fprintf(logFile, "At line no: %d factor : CONST_FLOAT\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType("float ");
				$$->setName($1->getName());
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				string tempSymbol = (string)newTemp();
				string codeSegment = "\tMOV " + tempSymbol + ", " + $1->getName() + "\n";
				$$->setAsmCode(codeSegment);
				$$->setAsmSymbol(tempSymbol);
				varDeclaration.push_back(tempSymbol);
			}
		|	variable INCOP {
				//fprintf(logFile, "At line no: %d factor : variable INCOP\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType($1->getDeclareType());
				$$->setName($1->getName() + "++");
				//fprintf(logFile, "%s++\n\n", $$->getName().c_str());
				string tempSymbol = (string)newTemp();
				string codeSegment = "";
				if($1->getType() == "array") {
					codeSegment += "\tMOV AX, " + $1->getAsmSymbol() + "[BX]\n";
					codeSegment += "\tMOV "+ tempSymbol + ", AX\n";
					codeSegment += "\tINC AX\n";
					codeSegment += "\tMOV " + $1->getAsmSymbol() + "[BX], AX\n";
				} else {
					codeSegment += "\tMOV AX, " + $1->getAsmSymbol() + "\n\tMOV " + tempSymbol + ", AX\n\tINC " + $1->getAsmSymbol() + "\n";
				}
				$$->setAsmCode(codeSegment);
				$$->setAsmSymbol(tempSymbol);
				varDeclaration.push_back(tempSymbol);
			}
		|	variable DECOP {
				//fprintf(logFile, "At line no: %d factor : variable DECOP\n\n", line_count);
				$$ = new SymbolInfo();
				$$->setDeclareType($1->getDeclareType());
				$$->setName($1->getName() + "--");
				//fprintf(logFile, "%s--\n\n", $$->getName().c_str());
				string tempSymbol = (string)newTemp();
				string codeSegment = "";
				if($1->getType() == "array") {
					codeSegment += "\tMOV AX, " + $1->getAsmSymbol() + "[BX]\n";
					codeSegment += "\tMOV "+ tempSymbol + ", AX\n";
					codeSegment += "\tDEC AX\n";
					codeSegment += "\tMOV " + $1->getAsmSymbol() + "[BX], AX\n";
				} else {
					codeSegment += "\tMOV AX, " + $1->getAsmSymbol() + "\n\tMOV " + tempSymbol + ", AX\n\tDEC " + $1->getAsmSymbol() + "\n";
				}
				$$->setAsmCode(codeSegment);
				$$->setAsmSymbol(tempSymbol);
				varDeclaration.push_back(tempSymbol);
			}
		;


argument_list	:	arguments {  //okay...asm done
									//chanded
									////fprintf(logFile, "At line no: %d argument_list : arguments\n\n", line_count);
									$$ = new SymbolInfo();
									$$->setName($1->getName());
									$$->setAsmCode($1->getAsmCode());
								}
					  	|	%empty {
					  			$$ = new SymbolInfo();
					  			$$->setName("");
					  			//fprintf(logFile, "At line no: %d argument_list : \n\n", line_count);
					  		}
					  	;


arguments :	arguments COMMA logic_expression {	//okay....asm done
							//fprintf(logFile, "At line no: %d argument_list : argument_list COMMA logic_expression\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setName($1->getName() + " , " + $3->getName());
							//fprintf(logFile, "%s, %s\n\n", $1->getName().c_str(), $3->getName().c_str());
							argList.push_back($3); //new argument as a logic_expression...size and type matter kore only
							$$->setAsmCode($1->getAsmCode() + $3->getAsmCode());
						}
		      |	logic_expression {
							//fprintf(logFile, "At line no: %d argument_list : logic_expression\n\n", line_count);
							$$ = new SymbolInfo();
							$$->setName($1->getName());
							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
							argList.push_back($1);	//first argument
			      	$$->setAsmCode($1->getAsmCode());
		      	}
		      ;



%%


int main(int argc,char *argv[]) {

	if(!(fp = fopen(argv[1], "r"))) {
		printf("Please provide input file name and try again\n\n");
		exit(1);
	}

	yyin = fp;
	yyparse();

	//fprintf(logFile, "\n\n\n\nSymbol Table: \n");
	//symbolTable->printAllScopeTable();
	line_count--;
	fprintf(logFile, "\nTotal Lines : %d \n\n", line_count);
	fprintf(logFile, "Total Errors : %d \n\n", error_count);


	fclose(logFile);
	//fclose(errorFile);

	return 0;
}

string definedVariables() {
	string vars = "";
	for(int i = 0; i < varDeclaration.size(); i++) {
		vars += "\t" + varDeclaration[i] + " dw ?\n";
	}
	return vars;
}

string definedArrays() {
	string arrays = "";
	for(int i = 0; i < arrVarDeclaration.size(); i++) {
		arrays += "\t" + arrVarDeclaration[i].first + " dw " + arrVarDeclaration[i].second + " dup(?)\n";
	}
	return arrays;
}

string defineProcRINTLN() {
	return
	"\nPRINTLN PROC\n"
	"\tPUSH AX\n"
	"\tPUSH BX\n"
	"\tPUSH CX\n"
	"\tPUSH DX\n"
	"\tCMP AX,0\n"
	"\tJGE BEGIN\n"
	"\tPUSH AX\n"
	"\tMOV DX, '-'\n"
	"\tMOV AH, 2\n"
	"\tINT 21H\n"
	"\tPOP AX\n"
	"\tNEG AX\n"
	"BEGIN:\n"
	"\tXOR CX, CX\n"
	"\tMOV BX, 10\n"
	"REPEAT:\n"
	"\tXOR DX, DX\n"
	"\tDIV BX\n"
	"\tPUSH DX\n"
	"\tINC CX\n"
	"\tOR AX, AX\n"
	"\tJNE REPEAT\n"
	"\tMOV AH, 2\n"
	"PRINT_LOOP:\n"
	"\tPOP DX\n"
	"\tADD DX, 30H\n"
	"\tINT 21H\n"
	"\tLOOP PRINT_LOOP\n"
	"\tMOV AH, 2\n"
	"\tMOV DX, 10\n"
	"\tINT 21H\n"
	"\tMOV DX, 13\n"
	"\tINT 21H\n"
	"\tPOP DX\n"
	"\tPOP CX\n"
	"\tPOP BX\n"
	"\tPOP AX\n"
	"\tret\n"
	"PRINTLN ENDP\n";
}

void printICG(string icg) {
	ofstream asmOut;
	asmOut.open("code.asm");
	asmOut << "TITLE PGMx.x: ASSEMLY(8086) INTERMIDIATE CODE GENERATED(without PeepHole optimization) FOR C PROGRAM PROVIDED\n" << endl;
	asmOut << icg << endl;
	asmOut.close();
}

string removeWS(string str) {
	stringstream ss(str);
	string temp = "";
	while(ss >> str)temp = (temp == "")? str : temp + " " + str;
	return temp;
}

vs split_string(string str, string _dlm) {
    vs tokens; size_t prev = 0, pos = 0;
    do {
        pos = str.find(_dlm, prev);
        if (pos == string::npos) pos = str.size();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + _dlm.size();
    } while (pos < str.size() && prev < str.size());
    return tokens;
}

//MOV t0, 0
//MOV AX, t0.........eitype e optimize korle problem hoite pare...cause t0 use hoitese kina jani na
bool isAllDigits(const std::string &str) {	//ignored..not used at all
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

bool pushPeep(string s1, string s2, string s3) {
	vs token1 = split_string(removeWS(s1), " ");
	vs token2 = split_string(removeWS(s2), " ");
	vs token3 = split_string(removeWS(s3), " ");
	//cout<<token1<<"|"<<token2<<"|"<<token3<<"|"<<endl;
  return (token1.size() == 2 && token2.size() == 1 && token2[0][token2[0].size()-1] == ':' && token3.size() == 2 && token1[0] == "PUSH" && token3[0] == "POP" && token1[1] == token3[1]);
}

bool moveConflict(string s1, string s2) {
	vs token1 = split_string(removeWS(s1), " ");
	vs token2 = split_string(removeWS(s2), " ");
	return (token1.size() == 3 && token2.size() == 3 && token1[0] == "MOV" && token2[0] == "MOV" && token1[1] == (token2[2] + ",") && (token1[2] + ",") == token2[1]);
}

bool jumpConflict(string s1, string s2) {
	vs token1 = split_string(removeWS(s1), " ");
	vs token2 = split_string(removeWS(s2), " ");
	return token1.size() == 2 && token1[0] == "JMP" && token2.size() == 1 && (token1[1] + ":") == token2[0];
}

void printOptimizedICG(string nonOptimizedICG) {
	ifstream asmIn("code.asm");
	ofstream optOut("Code.asm");
	string currentLine;
	vs codeSegment;
	while(getline(asmIn, currentLine)) {

		if(codeSegment.empty())
		{
			codeSegment.push_back(currentLine);
		}
		else if(codeSegment.size() == 1)
		{
			if(moveConflict(codeSegment[codeSegment.size() - 1], currentLine));
			else if(jumpConflict(codeSegment[codeSegment.size() - 1], currentLine)) {
				codeSegment.pop_back();
				codeSegment.push_back(currentLine);
			} else codeSegment.push_back(currentLine);
		}
		else if(codeSegment.size() >= 2)
		{
			if(moveConflict(codeSegment.back(), currentLine));
			else if(jumpConflict(codeSegment[codeSegment.size() - 1], currentLine)) {
				codeSegment.pop_back();
				codeSegment.push_back(currentLine);
			} else if( pushPeep(codeSegment[codeSegment.size()-2], codeSegment[codeSegment.size()-1], currentLine) ) {
				codeSegment[codeSegment.size()-2] = codeSegment[codeSegment.size()-1];
				codeSegment.pop_back();
			} else codeSegment.push_back(currentLine);
		}

	}

	optOut << "TITLE PGMopt.opt: ASSEMLY(8086) INTERMIDIATE CODE GENERATED(with PeepHole optimization) FOR C PROGRAM PROVIDED\n" << endl;
	for(int i = 1; i < codeSegment.size(); i++) {
		optOut << codeSegment[i] << endl;
	}
	asmIn.close();
	optOut.close();
}
