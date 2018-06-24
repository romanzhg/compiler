/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1024
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */
#include <string.h>

/* For string. */
int string_len;

bool encountered_null_char;
// Set string_buf_ptr at most MAX_STR_CONST times.
// If there are already MAX_STR_CONST chars added, only increase string_len.
void fill_string_buf(char c) {
  if (string_len < MAX_STR_CONST) {
    *string_buf_ptr = c;
    string_buf_ptr++;
  }
  string_len++;
}

/* handles comment */
int comment_levels  = 0;
%}

/*
 * Define names for regular expressions here.
 */

INTEGERS    [0-9]+
WHITESPACE  [ \f\r\t\v]+
NEWLINE	    \n
OBJECT_ID   [a-z][a-zA-Z0-9_]*
TYPE_ID     [A-Z][a-zA-Z0-9_]*

%x NCOMMENT ICOMMENT STRC

%%

 /*
  *  Nested comments
  */
<INITIAL,NCOMMENT>"(*" {
  if (comment_levels == 0) {
    BEGIN(NCOMMENT);
  }
  comment_levels++;
}

<INITIAL,NCOMMENT>"*"+")" {
  if (comment_levels == 0) {
    cool_yylval.error_msg = "Unmatched *)";
    return ERROR;
  } else {
    comment_levels--;
    if (comment_levels == 0) {
      BEGIN(INITIAL);
    }
  }
}

 /* any number of * not followed by ) and \n, in the branket we need to exclude 
  * '*', if we don't the last * will be consumed. *) won't be matched, ) won't
  * be matched. ) is only related to *. so need to handle it in any rule involves
  * '*'. */
<NCOMMENT>"*"+[^*()\n]* {
  ;
}

 /* anything else not a \n and *, (, ). */
<NCOMMENT>[^*\n()]+ {
  ;
}

 /* Flex match the rule with the longest sequence. ( or ) will not be matched 
  * if (* or *) exists. */
<NCOMMENT>[()] {
  ;
}

<NCOMMENT><<EOF>> {
  BEGIN(INITIAL);
  cool_yylval.error_msg = "EOF in comment";
  return ERROR;
}

<NCOMMENT>\n {
 curr_lineno++;
}

"--" {
  BEGIN(ICOMMENT);
}

 /* Eat everyting after a icomment, until the end of line or EOF(which we don't
  * need to explicitly handle). */
<ICOMMENT>.* {
  BEGIN(INITIAL);
}

<ICOMMENT>\n {
  BEGIN(INITIAL);
  curr_lineno++;
}

 /* New line applied before any other rule. */
\n {
  curr_lineno++;
}

 /* Key words and operators. */ 
[cC][lL][aA][sS][sS] {
  return CLASS;
}
[eE][lL][sS][eE] {
  return ELSE;
}
[fF][iI] {
  return FI;
}
[iI][fF] {
  return IF;
}
[iI][nN] {
  return IN;
}
[iI][nN][hH][eE][rR][iI][tT][sS] {
  return INHERITS;
}
[lL][eE][tT] {
  return LET;
}
[lL][oO][oO][pP] {
  return LOOP;
}
[pP][oO][oO][lL] {
  return POOL;
}
[tT][hH][eE][nN] {
  return THEN;
}
[wW][hH][iI][lL][eE] {
  return WHILE;
}
[cC][aA][sS][eE] {
  return CASE;
}
[eE][sS][aA][cC] {
  return ESAC;
}
[oO][fF] {
  return OF;
}
[nN][eE][wW] {
  return NEW;
}
[iI][sS][vV][oO][iI][dD] {
  return ISVOID;
}
[nN][oO][tT] {
  return NOT;
}

t[rR][uU][eE] {
  cool_yylval.boolean = 1;
  return BOOL_CONST;
}

f[aA][lL][sS][eE] {
  cool_yylval.boolean = 0;
  return BOOL_CONST;
}

 /*
  *  The multiple-character operators.
  */
 /* Rules appear first got applied first. */
"=>" {
  return DARROW;
}

"<-" {
  return ASSIGN;
}

"<=" {
  return LE;
}

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */
{WHITESPACE} {
  ;
}

 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */

\" {
  BEGIN(STRC);
  string_len = 0;
  string_buf_ptr = string_buf;
  encountered_null_char = false;
}

<STRC>\" {
  BEGIN(INITIAL);
  if (string_len > MAX_STR_CONST) {
    cool_yylval.error_msg = "String constant too long";
    return ERROR;
  } else if (encountered_null_char) {
    cool_yylval.error_msg = "String contains null character";
    return ERROR;
  } else {
    cool_yylval.symbol = stringtable.add_string(string_buf, string_len);
    return STR_CONST;
  }
}

 /* Non escaped \n. */
<STRC>\n {
  curr_lineno++;
  BEGIN(INITIAL);
  /* if invalid char or string too long error exist, do not report this error */
  if (string_len > MAX_STR_CONST) {
    cool_yylval.error_msg = "String constant too long";
    return ERROR;
  } else if (encountered_null_char) {
    cool_yylval.error_msg = "String contains null character";
    return ERROR;
  } else {
    cool_yylval.error_msg = "Unterminated string constant";
    return ERROR;
  }
}

<STRC>\0 {
  encountered_null_char = true;
}

<STRC><<EOF>> {
  BEGIN(INITIAL);
  cool_yylval.error_msg = "EOF in string constant";
  return ERROR;
}

 /* 2 char, \b \t \n \f \0 sequence. */
<STRC>\\b {
  fill_string_buf('\b');
}

<STRC>\\t {
  fill_string_buf('\t');
}

<STRC>\\n {
  fill_string_buf('\n');
}

<STRC>\\f {
  fill_string_buf('\f');
}

<STRC>\\0 {
  fill_string_buf('0');
}

 /* escaped sequences, should not escape \0 */
<STRC>\\(\0) {
  encountered_null_char = true;
}

<STRC>\\(.|\n) {
  if (yytext[1] == '\n') {
    curr_lineno++;
  }
  fill_string_buf(yytext[1]);
}

 /* basically there are three cases to handle. |\n|, \n, \|\n|. */
 /* the all matching rule, if a previous rule matched some char, it needs to be
  * excluded from here. */
<STRC>[^\\"\n\0]* {
  /* copy every thing to string buf. */
  for (int i = 0; i < yyleng; i++) {
    fill_string_buf(yytext[i]);
  }
}

 /* Put something in the int table and return. */
{INTEGERS} {
  cool_yylval.symbol = inttable.add_string(yytext);
  return INT_CONST;
}

 /* id table  */
{OBJECT_ID} {
  cool_yylval.symbol = idtable.add_string(yytext);
  return OBJECTID;
}

{TYPE_ID} {
  cool_yylval.symbol = idtable.add_string(yytext);
  return TYPEID;
}

 /* Single char operators*/
[.@~*/+\-<=(){}:;,] {
  return yytext[0];
}

. {
  cool_yylval.error_msg = strdup(yytext);
  return ERROR;
}

%%
