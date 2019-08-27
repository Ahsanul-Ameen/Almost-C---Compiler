%{
#define YYSTYPE SymbolInfo*
#include "1605047_SymbolTable.h"
#include "y.tab.h"

void yyerror(char *);
extern YYSTYPE yylval;			//sould we use it
extern FILE *errorFile;
extern SymbolTable *symbolTable;
extern int line_count, error_count;

bool flag;
string name,type;
int temp;

string updateString(string str){
	string upd = "";
	int temp = str.length();
	for(int i = 0; i < temp; i++){
		if(str[i]=='\n')line_count++;
		else if(str[i]=='\\'){
			if(i+1<temp){
				if(str[i+1]=='t')upd+='\t',i++;
				else if(str[i+1]=='n')upd+='\n',i++;
				else if(str[i+1]=='\\')upd+='\\',i++;
				else if(str[i+1]=='\'')upd+='\'',i++;
				else if(str[i+1]=='b')upd+='b',i++;
				else if(str[i+1]=='r')upd+='\r',i++;
				else if(str[i+1]=='f')upd+='\f',i++;
				else if(str[i+1]=='a')upd+='\a',i++;
				else if(str[i+1]=='v')upd+='\v',i++;
				else if(str[i+1]=='\"')upd+='\"',i++;
				else if(str[i+1]=='\0')upd+='\0',i++;
				else if(str[i+1] == '\n')line_count++,i++;
			}
		}
		else upd+=str[i];
	}
	return upd;
}

%}


WHITESPACE 		[ \t\f\r\v]+
LETTER 			[a-zA-Z]
DIGIT 			[0-9]
NEWLINE 		\n
ANYTHING        .

INTEGERLITERALS 		({DIGIT}+)
FLOATINGPOINTLITERALS 	(([0-9]*\.?[0-9]+|[0-9]+\.)([eE][-+]?[0-9]+)?)
CHARACTERLITERALS 		([']([ -~]{-}['\\])['])
EXCEPTIONALCHARACTERS	([']\\[\\"ntafrbv0]['])



IDENTIFIRES			 ([a-zA-Z_][a-zA-Z0-9_]*)

STRINGS			 	 (\"(\\[\n]?.|[^\"\\\n])*\")

SINGLELINECOMMENT 	 (\/\/((.*\\\n.*)|(.*))*)
MULTILINECOMMENT 	 (\/\*(("*"[^/]|[^*]))*\*\/)

DECIMALPOINTERROR	 [0-9]*\.[0-9]*(\.[0-9]*)+
ILLFORMATEDNUMBER	 (([0-9]+|[0-9]*\.[0-9]+)*([eE][-+]?[0-9]+)(\.[0-9]+)*)
INVALIDSUFFIX 		 [0-9]+[a-zA-Z0-9_]+
MULTICHARCONSTERROR  ([']((\\[\\"ntafrbv0]|[ -~]{-}[']){2,})['])
UNFINISHEDCHARACTER  (['](([ -~]{-}['\\])|(\\[\\"ntafrbv0])|(\\['])))
EMPTYCHARCONSTERROR  (['][ \t\f\r\v]*['])
UNFINISHEDSTRING	 (\"([^\n\"]|(\\\n))*(\\\")?)
UNFINISHEDCOMMENT	 (\/\*([^*]|\*[^\/])*[^(\*\/)])
UNRECOGNIZEDCHAR	 (.)



%%



{WHITESPACE}    {}

{NEWLINE} 		{line_count++;}

"println"		{ return PRINTLN; }

"if"			{ return IF; }

"else"			{ return ELSE; }

"for"			{ return FOR; }

"WHILE"			{ return WHILE; }

"do"			{ return DO; }

"break"			{ return BREAK; }

"int"			{ yylval = (YYSTYPE)new SymbolInfo(string(yytext), "INT"); /*cout<<*yylval;*/ return INT; }

"char"			{ return CHAR; }

"float"			{ yylval = (YYSTYPE)new SymbolInfo(string(yytext), "FLOAT"); /*cout<<*yylval;*/ return FLOAT; }

"double"		{ return DOUBLE; }

"void"			{ yylval = (YYSTYPE)new SymbolInfo(string(yytext), "VOID"); /*cout<<*yylval;*/ return VOID; }

"return"		{ return RETURN; }

"switch"		{ return SWITCH; }

"case"			{ return CASE; }

"default"		{ return DEFAULT; }

"continue"		{ return CONTINUE; }

{INTEGERLITERALS}	 	{ yylval = (YYSTYPE)new SymbolInfo(string(yytext), "CONST_INT"); /*cout<<*yylval;*/ return CONST_INT; }

{FLOATINGPOINTLITERALS}	{ yylval = (YYSTYPE)new SymbolInfo(string(yytext), "CONST_FLOAT"); /*cout<<*yylval;*/ return CONST_FLOAT; }

{CHARACTERLITERALS}		|
{EXCEPTIONALCHARACTERS}	{   name = updateString((string)yytext);
							yylval = (YYSTYPE)new SymbolInfo(string(yytext), "CONST_CHAR"); /*cout<<*yylval;*/ 
							return CONST_CHAR;
						}

"+"				|
"-"				{ yylval = (YYSTYPE)(new SymbolInfo(yytext, "ADDOP")); /*cout<<*yylval;*/ return ADDOP; }

"*"				|
"/"				|
"%"				{ yylval = (YYSTYPE)new SymbolInfo(string(yytext), "MULOP"); /*cout<<*yylval;*/ return MULOP; }

"++"			{ return INCOP; }
"--"			{ return DECOP; }

"<"				|
"<="			|
">"				|
">="			|
"=="			|
"!="			{ yylval = (YYSTYPE)new SymbolInfo(string(yytext), "RELOP"); /*cout<<*yylval;*/ return RELOP; }

"="				{ return ASSIGNOP; }

"&&"			|
"||"			{ yylval = (YYSTYPE)new SymbolInfo(string(yytext), "LOGICOP"); /*cout<<*yylval;*/ return LOGICOP; }

"&"				|
"|"				|
"^"				|
"<<"			|
">>"			{ yylval = (YYSTYPE)new SymbolInfo(string(yytext), "BITOP"); /*cout<<*yylval;*/ return BITOP; }

"!"				{ return NOT; }

"("				{ return LPAREN; }

")"				{ return RPAREN; }

"{"				{ return LCURL; }

"}"				{ return RCURL; }

"["				{ return LTHIRD; }

"]"				{ return RTHIRD; }

","				{ return COMMA; }

";"				{ return SEMICOLON; }

{IDENTIFIRES}	{
					yylval = (YYSTYPE)new SymbolInfo(string(yytext), "ID"); /*cout<<*yylval;*/ return ID;
				/**	if(symbolTable->lookUp(yytext) == NULL)
					yylval = (YYSTYPE)new SymbolInfo(yytext, "ID");
					return ID;	*/
				}

{STRINGS}		{ yylval = (YYSTYPE)new SymbolInfo(updateString((string)yytext), "STRING"); /*cout<<*yylval;*/ return STRING; }


{SINGLELINECOMMENT}		{ name = updateString(yytext); }

{MULTILINECOMMENT}		{ name = updateString(yytext); }


{DECIMALPOINTERROR}		{
							error_count++;
							fprintf(errorFile, "Error at line %d: Too many decimal point: %s\n", line_count, yytext);
						}

{ILLFORMATEDNUMBER}		{
							error_count++;
							fprintf(errorFile, "Error at line %d: Ill formed number: %s\n", line_count, yytext);
						}

{INVALIDSUFFIX}			{
							error_count++;
							fprintf(errorFile, "Error at line %d: Invalid prefix on ID or invalid suffix on Number: %s\n", line_count, yytext);
						}

{MULTICHARCONSTERROR}	{
							error_count++;
							fprintf(errorFile, "Error at line %d: Multi character constant error: %s\n", line_count, yytext);
							name = updateString(yytext);
						}

{UNFINISHEDCHARACTER}	{
							error_count++;
							fprintf(errorFile, "Error at line %d: Unterminated character: %s\n", line_count, yytext);
							name = updateString(yytext);
						}

{EMPTYCHARCONSTERROR}	{
							error_count++;
							fprintf(errorFile, "Error at line %d: Empty character constant error: %s\n", line_count, yytext);
						}

{UNFINISHEDSTRING}		{
							error_count++;
							fprintf(errorFile, "Error at line %d: Unterminated string: %s\n", line_count, yytext);
							name = updateString(yytext);
						}

{UNFINISHEDCOMMENT}		{
							error_count++;
							fprintf(errorFile, "Error at line %d: Unterminated comment: %s\n", line_count, yytext);
							name = updateString(yytext);
						}

{UNRECOGNIZEDCHAR}		{
							error_count++;
							fprintf(errorFile, "Error at line %d: Unrecognized character: %s\n", line_count, yytext);
						}



%%



int yywrap(void) {
	return 1;//disable yywrap
}



