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

/***********************************/
#include "symtab.h"
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;
/***********************************/

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


/* ************************************** */
class ClassTable;
typedef ClassTable *ClassTableP;
typedef SymbolTable<string, string> *SymbolTableP;
/* ************************************** */


#define Program_EXTRAS                          \
virtual void semant() = 0;			\
virtual void dump_with_types(ostream&, int) = 0; 



#define program_EXTRAS                          \
void semant();     				\
void dump_with_types(ostream&, int);            

#define Class__EXTRAS                   \
virtual Symbol get_filename() = 0;      \
virtual void dump_with_types(ostream&,int) = 0; \
virtual Symbol get_classname() = 0; \
virtual Symbol get_parent() = 0; \
virtual void check_features(ClassTableP class_table) = 0; \
virtual void cross_check_features(ClassTableP class_table) = 0; \
virtual void semant(ClassTableP class_table) = 0;


#define class__EXTRAS                                 \
Symbol get_filename() { return filename; }             \
void dump_with_types(ostream&,int); \
Symbol get_classname(); \
Symbol get_parent(); \
void check_features(ClassTableP class_table); \
void cross_check_features(ClassTableP class_table); \
void semant(ClassTableP class_table);


#define Feature_EXTRAS                                        \
virtual void dump_with_types(ostream&,int) = 0; \
virtual void check_features(ClassTableP class_table) = 0; \
virtual void cross_check_features(ClassTableP class_table) = 0; \
virtual void semant(ClassTableP ct, SymbolTableP st) = 0;


#define Feature_SHARED_EXTRAS                                       \
void dump_with_types(ostream&,int); \
void check_features(ClassTableP class_table); \
void cross_check_features(ClassTableP class_table); \
void semant(ClassTableP ct, SymbolTableP st);





#define Formal_EXTRAS                              \
virtual void dump_with_types(ostream&,int) = 0; \
virtual Symbol get_type() = 0; \
virtual Symbol get_name() = 0;


#define formal_EXTRAS                           \
void dump_with_types(ostream&,int); \
Symbol get_type(); \
Symbol get_name();


#define Case_EXTRAS                             \
virtual void dump_with_types(ostream& ,int) = 0; \
virtual void semant(ClassTableP ct, SymbolTableP st) = 0; \
virtual Symbol get_type() = 0; \
virtual Symbol get_decl_type() = 0;



#define branch_EXTRAS                                   \
void dump_with_types(ostream& ,int); \
void semant(ClassTableP ct, SymbolTableP st); \
Symbol get_type(); \
Symbol get_decl_type() { return type_decl; };


#define Expression_EXTRAS                    \
Symbol type;                                 \
Symbol get_type() { return type; }           \
Expression set_type(Symbol s) { type = s; return this; } \
virtual void dump_with_types(ostream&,int) = 0;  \
void dump_type(ostream&, int);               \
Expression_class() { type = (Symbol) NULL; } \
virtual void semant(ClassTableP ct, SymbolTableP st) = 0; \
virtual bool is_no_expr() { return false; };

#define Expression_SHARED_EXTRAS           \
void dump_with_types(ostream&,int); \
void semant(ClassTableP ct, SymbolTableP st);

#define no_expr_EXTRAS \
bool is_no_expr() { return true; }

#endif
