//
// The following include files must come first.

#ifndef COOL_TREE_HANDCODE_H
#define COOL_TREE_HANDCODE_H

#include <iostream>
#include "tree.h"
#include "cool.h"
#include "stringtab.h"
#define yylineno curr_lineno;
extern int yylineno;

////////////////////////////////////////////////////////
#include <vector>
#include <utility>
using std::vector;
using std::pair;

class CgenClassTable;
typedef CgenClassTable *CgenClassTableP;

class CgenNode;
typedef CgenNode *CgenNodeP;

class Environment;
typedef Environment* EnvironmentP;

////////////////////////////////////////////////////////

inline Boolean copy_Boolean(Boolean b) {return b; }
inline void assert_Boolean(Boolean) {}
inline void dump_Boolean(ostream& stream, int padding, Boolean b)
	{ stream << pad(padding) << (int) b << "\n"; }

void dump_Symbol(ostream& stream, int padding, Symbol b);
void assert_Symbol(Symbol b);
Symbol copy_Symbol(Symbol b);

class Program_class;
typedef Program_class *Program;
class Class__class;
typedef Class__class *Class_;
class Feature_class;
typedef Feature_class *Feature;
class Formal_class;
typedef Formal_class *Formal;
class Expression_class;
typedef Expression_class *Expression;
class Case_class;
typedef Case_class *Case;

typedef list_node<Class_> Classes_class;
typedef Classes_class *Classes;
typedef list_node<Feature> Features_class;
typedef Features_class *Features;
typedef list_node<Formal> Formals_class;
typedef Formals_class *Formals;
typedef list_node<Expression> Expressions_class;
typedef Expressions_class *Expressions;
typedef list_node<Case> Cases_class;
typedef Cases_class *Cases;

#define Program_EXTRAS                          \
virtual void cgen(ostream&) = 0;		\
virtual void dump_with_types(ostream&, int) = 0; 



#define program_EXTRAS                          \
void cgen(ostream&);     			\
void dump_with_types(ostream&, int);            

#define Class__EXTRAS                   \
virtual Symbol get_name() = 0;  	\
virtual Symbol get_parent() = 0;    	\
virtual Symbol get_filename() = 0;      \
virtual void dump_with_types(ostream&,int) = 0; \
virtual int get_attributes_count() = 0; \
virtual void gen_dispatch_table(vector<pair<Symbol, Symbol> >&) = 0; \
virtual void code_default_values(vector<Symbol>&, ostream&) = 0; 

#define class__EXTRAS                                  \
Symbol get_name()   { return name; }		       \
Symbol get_parent() { return parent; }     	       \
Symbol get_filename() { return filename; }             \
void dump_with_types(ostream&,int); \
int get_attributes_count(); \
void gen_dispatch_table(vector<pair<Symbol, Symbol> >&); \
void code_default_values(vector<Symbol>&, ostream&); 


#define Feature_EXTRAS                                        \
virtual void dump_with_types(ostream&,int) = 0; \
virtual bool is_attribute() = 0; \
virtual void gen_dispatch_table(Symbol, vector<pair<Symbol, Symbol> >&) = 0; \
virtual void code_default_values(vector<Symbol>&, ostream&) = 0; \
virtual void code_initialization(CgenClassTableP, EnvironmentP, ostream&) = 0; \
virtual void code_method(CgenClassTableP, EnvironmentP, ostream&) = 0;


#define Feature_SHARED_EXTRAS                                       \
void dump_with_types(ostream&,int); \
bool is_attribute(); \
void gen_dispatch_table(Symbol, vector<pair<Symbol, Symbol> >&); \
void code_default_values(vector<Symbol>&, ostream&); \
void code_initialization(CgenClassTableP, EnvironmentP, ostream&); \
void code_method(CgenClassTableP, EnvironmentP, ostream&);

#define Formal_EXTRAS                              \
virtual void dump_with_types(ostream&,int) = 0; \
virtual Symbol get_name() = 0;


#define formal_EXTRAS                           \
void dump_with_types(ostream&,int); \
Symbol get_name() { return name; };


#define Case_EXTRAS                             \
virtual void dump_with_types(ostream& ,int) = 0; \
virtual Symbol get_type_decl() = 0; \
virtual void code(CgenClassTableP, EnvironmentP, ostream&) = 0;


#define branch_EXTRAS                                   \
void dump_with_types(ostream& ,int); \
Symbol get_type_decl() { return type_decl; }; \
void code(CgenClassTableP, EnvironmentP, ostream&);


#define Expression_EXTRAS                    \
Symbol type;                                 \
Symbol get_type() { return type; }           \
Expression set_type(Symbol s) { type = s; return this; } \
virtual void code(CgenClassTableP, EnvironmentP, ostream&) = 0; \
virtual void dump_with_types(ostream&,int) = 0;  \
void dump_type(ostream&, int);               \
Expression_class() { type = (Symbol) NULL; } \
virtual bool is_no_expr() { return false; };

#define Expression_SHARED_EXTRAS           \
void code(CgenClassTableP, EnvironmentP, ostream&); \
void dump_with_types(ostream&,int); 

#define no_expr_EXTRAS \
bool is_no_expr() { return true; }

#endif
