//////////////////////////////////////////////////////////
//
// file: cool-tree.cc
//
// This file defines the functions of each class
//
//////////////////////////////////////////////////////////


#include "tree.h"
#include "cool-tree.handcode.h"
#include "cool-tree.h"

/* *********************************** */
#include "semant.h"
#include "symtab.h"

#include <set>
using std::set;

typedef SymbolTable<string, string>* SymbolTableP;


// constructors' functions
Program program_class::copy_Program()
{
   return new program_class(classes->copy_list());
}


void program_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "program\n";
   classes->dump(stream, n+2);
}


Class_ class__class::copy_Class_()
{
   return new class__class(copy_Symbol(name), copy_Symbol(parent), features->copy_list(), copy_Symbol(filename));
}

void class__class::dump(ostream& stream, int n)
{
   stream << pad(n) << "class_\n";
   dump_Symbol(stream, n+2, name);
   dump_Symbol(stream, n+2, parent);
   features->dump(stream, n+2);
   dump_Symbol(stream, n+2, filename);
}

Symbol class__class::get_classname()
{
  return name;
}

Symbol class__class::get_parent()
{
  return parent;
}

// TODO: after the redefinition check, this class can be modified.
// some of the logic here is not needed.
void add_symbols(ClassTableP ct, SymbolTableP st, string class_name) {
  if (class_name == "_no_class") {
    return;
  }
  map<string, string>& attrs = ct->attrs_map[class_name];
  for (map<string, string>::iterator a_it = attrs.begin();
       a_it != attrs.end(); a_it++) {
    if (st->probe(a_it->first) != NULL) {
      ct->semant_error(ct->class_map[class_name]) << "Re-definition of " << a_it->first << "\n";
    } else {
      st->addid(a_it->first, &a_it->second);
    }
  }
  add_symbols(ct, st, ct->class_map[class_name]->get_parent()->get_string());
}

void class__class::semant(ClassTableP ct) {
  // build the symbol table and initialize.
  SymbolTableP st = new SymbolTable<string, string>();
  st->enterscope();
  
  add_symbols(ct, st, ct->current_class_);

  // Semantic check on all the feature.
  for (int i = features->first(); features->more(i); i = features->next(i)) {
    features->nth(i)->semant(ct, st);
  }
  
  st->exitscope();

  // TODO: does delete st clear the ids stored there?
  // In the symbol table the value is dynamically allocated, may need to delete.
  delete st;
}

void class__class::check_features(ClassTableP ct)
{
  for (int i = features->first(); features->more(i); i = features->next(i)) {
    features->nth(i)->check_features(ct);
  }
}

void class__class::cross_check_features(ClassTableP ct)
{
  for (int i = features->first(); features->more(i); i = features->next(i)) {
    features->nth(i)->cross_check_features(ct);
  }
}

Feature method_class::copy_Feature()
{
   return new method_class(copy_Symbol(name), formals->copy_list(), copy_Symbol(return_type), expr->copy_Expression());
}


void method_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "method\n";
   dump_Symbol(stream, n+2, name);
   formals->dump(stream, n+2);
   dump_Symbol(stream, n+2, return_type);
   expr->dump(stream, n+2);
}

void method_class::check_features(ClassTableP ct) {
  map<string, vector<string> >& tmp = ct->methods_map[ct->current_class_];
  if (tmp.find(name->get_string()) != tmp.end()) {
    ct->semant_error(this) << "Redefinition of a method within the class.\n";
    return;
  }

  vector<string> method_signiture;
  for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
    Formal f = formals->nth(i);
    string formal_name = f->get_name()->get_string();
    string formal_type = f->get_type()->get_string();
    if (formal_name == "self") {
      ct->semant_error(this) << "Invalid parameter name: self.\n";
    }
    if (formal_type == SELFTYPE_STR) {
      ct->semant_error(this) << "Invalid parameter type: SELF_TYPE.\n";
    }

    method_signiture.push_back(f->get_type()->get_string());
  }
  method_signiture.push_back(return_type->get_string());
  tmp[name->get_string()] = method_signiture;
}

void method_class::cross_check_features(ClassTableP ct) {
  map<string, vector<string> >& tmp = ct->methods_map[ct->current_class_];
  if (!ct->isValidMethod(this, name->get_string())) {
    tmp.erase(name->get_string());
  }
}

// The semantic check on a method just need to check the method itself.
// No class hiararchy need to reference.
void method_class::semant(ClassTableP ct, SymbolTableP st) {
  // Add formals to the symbol table.
  st->enterscope();
  for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
    Formal f = formals->nth(i);
    string f_name = f->get_name()->get_string();
    if (st->probe(f_name) != NULL) {
      ct->semant_error(this) << "Redefinition of a parameter: " << f_name << "\n";
    } else {
      // TODO: should put this pointer in ct for garbage collection.
      string* f_type = new string(f->get_type()->get_string());
      st->addid(f_name, f_type);
    }
  }

  // Run semantic check on expressions.
  expr->semant(ct, st);
  st->exitscope();

  if (expr->is_no_expr()) {
    return;
  }

  // Check the actual return type with the declared one.
  string expr_type = expr->get_type()->get_string();
  string declared_type = return_type->get_string();
  if (!ct->isSubType(expr_type, declared_type)) {
    ct->semant_error(this) << "Inferred type " << expr_type
      << " of method " << name->get_string()
      << " does not conform to declared type " << declared_type
      << ".\n";
  }
}

Feature attr_class::copy_Feature()
{
   return new attr_class(copy_Symbol(name), copy_Symbol(type_decl), init->copy_Expression());
}


void attr_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "attr\n";
   dump_Symbol(stream, n+2, name);
   dump_Symbol(stream, n+2, type_decl);
   init->dump(stream, n+2);
}

void attr_class::check_features(ClassTableP ct) {
  map<string, string>& tmp = ct->attrs_map[ct->current_class_];
  string attr_name = name->get_string();
  if (!ct->isValidVariableName(attr_name)) {
    ct->semant_error(this) << "Invalid attribute name.\n"; 
    return;
  }
  if (tmp.find(attr_name) != tmp.end()) {
    ct->semant_error(this) << "Redefinition of attribute "
      << attr_name << " within the class.\n";
  } else {
    tmp[attr_name] = type_decl->get_string();
  }
}

void attr_class::cross_check_features(ClassTableP ct) {
  map<string, string>& tmp = ct->attrs_map[ct->current_class_];
  if (!ct->isValidAttribute(this, name->get_string())) {
    tmp.erase(name->get_string());
  }
}

void attr_class::semant(ClassTableP ct, SymbolTableP st) {
  if (init->is_no_expr()) {
    return;
  }
  init->semant(ct, st);
  string init_type = init->get_type()->get_string();
  string declared_type = type_decl->get_string();
  if (!ct->isSubType(init_type, declared_type)) {
    ct->semant_error(this) << "Inferred type " << init_type
      << " of initialization of attribute " << name->get_string()
      << " does not conform to declared type " << declared_type
      << ".\n";
  }
}

Formal formal_class::copy_Formal()
{
   return new formal_class(copy_Symbol(name), copy_Symbol(type_decl));
}


void formal_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "formal\n";
   dump_Symbol(stream, n+2, name);
   dump_Symbol(stream, n+2, type_decl);
}

Symbol formal_class::get_type()
{
  return type_decl;
}

Symbol formal_class::get_name()
{
  return name;
}


Case branch_class::copy_Case()
{
   return new branch_class(copy_Symbol(name), copy_Symbol(type_decl), expr->copy_Expression());
}


void branch_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "branch\n";
   dump_Symbol(stream, n+2, name);
   dump_Symbol(stream, n+2, type_decl);
   expr->dump(stream, n+2);
}

Symbol branch_class::get_type() {
  return expr->get_type();
}

void branch_class::semant(ClassTableP ct, SymbolTableP st) {
  st->enterscope();

  string name_str = name->get_string();
  string decl_type_str = type_decl->get_string();
  // TODO: gc
  string* decl_type_str_p = new string(decl_type_str);
  st->addid(name_str, decl_type_str_p);
  
  expr->semant(ct, st);

  st->exitscope();
}


Expression assign_class::copy_Expression()
{
   return new assign_class(copy_Symbol(name), expr->copy_Expression());
}


void assign_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "assign\n";
   dump_Symbol(stream, n+2, name);
   expr->dump(stream, n+2);
}

void assign_class::semant(ClassTableP ct, SymbolTableP st) {
  expr->semant(ct, st);
  string expr_type = expr->get_type()->get_string();

  // TODO: can we combine these two lines?
  string obj_name = name->get_string();
  string* obj_type_p = st->lookup(obj_name);
  string obj_type;
  if (obj_type_p == NULL) {
    obj_type = "Object";
    ct->semant_error(this) << "Object " << obj_name << " not defined.\n";
  } else {
    obj_type = *obj_type_p;
  }
  if (!ct->isSubType(expr_type, obj_type)) {
    ct->semant_error(this) << "Inferred type " << expr_type
      << " of expression does not conform to the declared type " << obj_type
      << " of the variable " << obj_name
      << ".\n";
  }
  char* tmp_char = strdup(expr_type.c_str());
  type = idtable.add_string(tmp_char);
  free(tmp_char);
}

Expression static_dispatch_class::copy_Expression()
{
   return new static_dispatch_class(expr->copy_Expression(), copy_Symbol(type_name), copy_Symbol(name), actual->copy_list());
}


void static_dispatch_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "static_dispatch\n";
   expr->dump(stream, n+2);
   dump_Symbol(stream, n+2, type_name);
   dump_Symbol(stream, n+2, name);
   actual->dump(stream, n+2);
}

void static_dispatch_class::semant(ClassTableP ct, SymbolTableP st) {
  // Resolve the type of calling expression.
  expr->semant(ct, st);
  string expr_type = expr->get_type()->get_string();
  
  if (!ct->isSubType(expr_type, type_name->get_string())) {
    ct->semant_error(this) << "Expression type does not conform to declared static dispatch type.\n";
    type = idtable.add_string("Object");
    return;
  }

  // Get the method signiture of the function call.
  string method_name = name->get_string();
  vector<string> method_signiture;
  if (!ct->getMethodSig(type_name->get_string(), method_name, &method_signiture)) {
    ct->semant_error(this) << "Method doesn't exist in methods map.\n";
    type = idtable.add_string("Object");
    return;
  }
  
  // Type check all the arguments.
  int arg_size = method_signiture.size();
  if ((arg_size - 1) != actual->len()) {
    ct->semant_error(this) << "Argument size mismatch.\n";
  }

  for (int i = 0; i < actual->len(); i++) {
    Expression tmp_expr = actual->nth(i);
    tmp_expr->semant(ct, st);
    string tmp_expr_type = tmp_expr->get_type()->get_string();
    if (!ct->isSubType(tmp_expr_type, method_signiture[i])) {
      ct->semant_error(this) << "The " << i << " th argument is declared to have type " << method_signiture[i]
        << ", the actual type is " << tmp_expr_type << ".\n";
    }
  }

  // Type check the return type.
  string decl_return_type = method_signiture.back();
  char * tmp_char;
  if (decl_return_type == SELFTYPE_STR) {
    type = expr->get_type();
  } else {
    tmp_char = strdup(decl_return_type.c_str());
    type = idtable.add_string(tmp_char);
    free(tmp_char);
  }
}


Expression dispatch_class::copy_Expression()
{
   return new dispatch_class(expr->copy_Expression(), copy_Symbol(name), actual->copy_list());
}


void dispatch_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "dispatch\n";
   expr->dump(stream, n+2);
   dump_Symbol(stream, n+2, name);
   actual->dump(stream, n+2);
}

void dispatch_class::semant(ClassTableP ct, SymbolTableP st) {
  // Resolve the type of calling expression.
  expr->semant(ct, st);
  string expr_type = expr->get_type()->get_string();
  if (expr_type == "SELF_TYPE") {
    expr_type = ct->current_class_;
  }
  
  // Get the method signiture of the function call.
  string method_name = name->get_string();
  vector<string> method_signiture;
  if (!ct->getMethodSig(expr_type, method_name, &method_signiture)) {
    ct->semant_error(this) << "Method doesn't exist in methods map.\n";
    type = idtable.add_string("Object");
    return;
  }
  
  // Type check all the arguments.
  int arg_size = method_signiture.size();
  if ((arg_size - 1) != actual->len()) {
    ct->semant_error(this) << "Argument size mismatch.\n";
  }

  for (int i = 0; i < actual->len(); i++) {
    Expression tmp_expr = actual->nth(i);
    tmp_expr->semant(ct, st);
    string tmp_expr_type = tmp_expr->get_type()->get_string();
    if (!ct->isSubType(tmp_expr_type, method_signiture[i])) {
      ct->semant_error(this) << "The " << i << " th argument is declared to have type " << method_signiture[i]
        << ", the actual type is " << tmp_expr_type << ".\n";
    }
  }

  // Type check the return type.
  string decl_return_type = method_signiture.back();
  char * tmp_char;
  if (decl_return_type == SELFTYPE_STR) {
    type = expr->get_type();
  } else {
    tmp_char = strdup(decl_return_type.c_str());
    type = idtable.add_string(tmp_char);
    free(tmp_char);
  }
}

Expression cond_class::copy_Expression()
{
   return new cond_class(pred->copy_Expression(), then_exp->copy_Expression(), else_exp->copy_Expression());
}


void cond_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "cond\n";
   pred->dump(stream, n+2);
   then_exp->dump(stream, n+2);
   else_exp->dump(stream, n+2);
}

void cond_class::semant(ClassTableP ct, SymbolTableP st) {
  pred->semant(ct, st);
  then_exp->semant(ct, st);
  else_exp->semant(ct, st);

  string pred_type = pred->get_type()->get_string();
  string then_type = then_exp->get_type()->get_string();
  string else_type = else_exp->get_type()->get_string();

  if (pred_type != "Bool") {
    ct->semant_error(this) << "Predicator needs to have type Bool, the actual type is " << pred_type
      << ".\n";
  }
  string lub_type = ct->lub(then_type, else_type);
  char* tmp_type = strdup(lub_type.c_str());
  type = idtable.add_string(tmp_type);
  free(tmp_type);
}


Expression loop_class::copy_Expression()
{
   return new loop_class(pred->copy_Expression(), body->copy_Expression());
}


void loop_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "loop\n";
   pred->dump(stream, n+2);
   body->dump(stream, n+2);
}

void loop_class::semant(ClassTableP ct, SymbolTableP st) {
  pred->semant(ct, st);
  body->semant(ct, st);

  string pred_type = pred->get_type()->get_string();
  string body_type = body->get_type()->get_string();

  if (pred_type != "Bool") {
    ct->semant_error(this) << "Predicator needs to have type Bool, the actual type is " << pred_type
      << ".\n";
  }

  type = idtable.add_string("Object");
}


Expression typcase_class::copy_Expression()
{
   return new typcase_class(expr->copy_Expression(), cases->copy_list());
}


void typcase_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "typcase\n";
   expr->dump(stream, n+2);
   cases->dump(stream, n+2);
}

void typcase_class::semant(ClassTableP ct, SymbolTableP st) {
  // The type of the expression is not used in semantic analysis phase.
  expr->semant(ct, st);

  vector<string> branch_types;
  vector<string> dc;

  for (int i = cases->first(); cases->more(i); i = cases->next(i)) {
    Case c = cases->nth(i);
    c->semant(ct, st);
    branch_types.push_back(c->get_type()->get_string());
    string decl_type = c->get_decl_type()->get_string();
    for (int i = 0; i < (int)dc.size(); i++) {
      if (decl_type == dc[i]) {
        ct->semant_error(c) << "Duplicate branch is case statement.\n";
        break;
      }
    }
    dc.push_back(decl_type);
/*
    if (dc.find(decl_type) == dc.end()) {
      dc.insert(decl_type);
    } else {
      ct->semant_error(c) << "Duplicate branch is case statement.\n";
    }
*/
  }

  string first_type = branch_types[0];
  for (int i = 1; i < (int) branch_types.size(); i++) {
    string second_type = branch_types[i];
    first_type = ct->lub(first_type, second_type);
  }
  // TODO: can the type here be self type?
  char* tmp_char = strdup(first_type.c_str());
  type = idtable.add_string(tmp_char);
  free(tmp_char);
}

Expression block_class::copy_Expression()
{
   return new block_class(body->copy_list());
}


void block_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "block\n";
   body->dump(stream, n+2);
}

void block_class::semant(ClassTableP ct, SymbolTableP st) {
  string last_expr_type;
  for (int i = body->first(); body->more(i); i = body->next(i)) {
    Expression expr = body->nth(i);
    expr->semant(ct, st);
    last_expr_type = expr->get_type()->get_string();
  }
  char* tmp = strdup(last_expr_type.c_str());
  type = idtable.add_string(tmp);
  free(tmp);
}

Expression let_class::copy_Expression()
{
   return new let_class(copy_Symbol(identifier), copy_Symbol(type_decl), init->copy_Expression(), body->copy_Expression());
}


void let_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "let\n";
   dump_Symbol(stream, n+2, identifier);
   dump_Symbol(stream, n+2, type_decl);
   init->dump(stream, n+2);
   body->dump(stream, n+2);
}

void let_class::semant(ClassTableP ct, SymbolTableP st) {
  string decl_type_str = type_decl->get_string();
  if (!init->is_no_expr()) {
    init->semant(ct, st);
    string init_type = init->get_type()->get_string();
    if (!ct->isSubType(init_type, decl_type_str)) {
      ct->semant_error(this) << "Let expression initializer does not comfort the declared type.\n";
    }
  }
  st->enterscope();
  string identifier_str = identifier->get_string();
  if (ct->isValidVariableName(identifier_str)) {
    // TODO: need to gc.
    string* decl_type_str_p = new string(decl_type_str);
    st->addid(identifier_str, decl_type_str_p);
  } else {
    ct->semant_error(this) << "Invalid variable name.\n";
  }
  
  body->semant(ct, st);
  type = idtable.add_string(body->get_type()->get_string());
  st->exitscope();
}

Expression plus_class::copy_Expression()
{
   return new plus_class(e1->copy_Expression(), e2->copy_Expression());
}


void plus_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "plus\n";
   e1->dump(stream, n+2);
   e2->dump(stream, n+2);
}

void plus_class::semant(ClassTableP ct, SymbolTableP st) {
  e1->semant(ct, st);
  e2->semant(ct, st);
  string e1_type = e1->get_type()->get_string();
  string e2_type = e2->get_type()->get_string();
  if (e1_type != "Int") {
    ct->semant_error(this) << "Plus operation accepts only int, e1 has type "<< e1_type  << "\n";
  }
  if (e2_type != "Int") {
    ct->semant_error(this) << "Plus operation accepts only int, e2 has type "<< e2_type  << "\n";
  }
  type = idtable.add_string("Int");
}

Expression sub_class::copy_Expression()
{
   return new sub_class(e1->copy_Expression(), e2->copy_Expression());
}


void sub_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "sub\n";
   e1->dump(stream, n+2);
   e2->dump(stream, n+2);
}

void sub_class::semant(ClassTableP ct, SymbolTableP st) {
  e1->semant(ct, st);
  e2->semant(ct, st);
  string e1_type = e1->get_type()->get_string();
  string e2_type = e2->get_type()->get_string();
  if (e1_type != "Int") {
    ct->semant_error(this) << "Subtraction operation accepts only int, e1 has type "<< e1_type  << "\n";
  }
  if (e2_type != "Int") {
    ct->semant_error(this) << "Subtraction operation accepts only int, e2 has type "<< e2_type  << "\n";
  }
  type = idtable.add_string("Int");
}

Expression mul_class::copy_Expression()
{
   return new mul_class(e1->copy_Expression(), e2->copy_Expression());
}


void mul_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "mul\n";
   e1->dump(stream, n+2);
   e2->dump(stream, n+2);
}

void mul_class::semant(ClassTableP ct, SymbolTableP st) {
  e1->semant(ct, st);
  e2->semant(ct, st);
  string e1_type = e1->get_type()->get_string();
  string e2_type = e2->get_type()->get_string();
  if (e1_type != "Int") {
    ct->semant_error(this) << "Multiply operation accepts only int, e1 has type "<< e1_type  << "\n";
  }
  if (e2_type != "Int") {
    ct->semant_error(this) << "Multiply operation accepts only int, e2 has type "<< e2_type  << "\n";
  }
  type = idtable.add_string("Int");
}

Expression divide_class::copy_Expression()
{
   return new divide_class(e1->copy_Expression(), e2->copy_Expression());
}


void divide_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "divide\n";
   e1->dump(stream, n+2);
   e2->dump(stream, n+2);
}

void divide_class::semant(ClassTableP ct, SymbolTableP st) {
  e1->semant(ct, st);
  e2->semant(ct, st);
  string e1_type = e1->get_type()->get_string();
  string e2_type = e2->get_type()->get_string();
  if (e1_type != "Int") {
    ct->semant_error(this) << "Divide operation accepts only int, e1 has type "<< e1_type  << "\n";
  }
  if (e2_type != "Int") {
    ct->semant_error(this) << "Divide operation accepts only int, e2 has type "<< e2_type  << "\n";
  }
  type = idtable.add_string("Int");
}

Expression neg_class::copy_Expression()
{
   return new neg_class(e1->copy_Expression());
}


void neg_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "neg\n";
   e1->dump(stream, n+2);
}

void neg_class::semant(ClassTableP ct, SymbolTableP st) {
  e1->semant(ct, st);
  string e1_type = e1->get_type()->get_string();
  if (e1_type != "Int") {
    ct->semant_error(this) << "Negate only accepts Int, but got "<< e1_type  << "\n";
    exit(1);
  }
  type = idtable.add_string("Int");
}

Expression lt_class::copy_Expression()
{
   return new lt_class(e1->copy_Expression(), e2->copy_Expression());
}


void lt_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "lt\n";
   e1->dump(stream, n+2);
   e2->dump(stream, n+2);
}

void lt_class::semant(ClassTableP ct, SymbolTableP st) {
  e1->semant(ct, st);
  e2->semant(ct, st);
  string e1_type = e1->get_type()->get_string();
  string e2_type = e2->get_type()->get_string();
  if (e1_type != "Int") {
    ct->semant_error(this) << "Compare operation accepts only int, e1 has type "<< e1_type  << "\n";
  }
  if (e2_type != "Int") {
    ct->semant_error(this) << "Compare operation accepts only int, e2 has type "<< e2_type  << "\n";
  }
  type = idtable.add_string("Bool");
}

Expression eq_class::copy_Expression()
{
   return new eq_class(e1->copy_Expression(), e2->copy_Expression());
}


void eq_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "eq\n";
   e1->dump(stream, n+2);
   e2->dump(stream, n+2);
}

void eq_class::semant(ClassTableP ct, SymbolTableP st) {
  e1->semant(ct, st);
  e2->semant(ct, st);
  string e1_type = e1->get_type()->get_string();
  string e2_type = e2->get_type()->get_string();
  if ((e1_type == "Int" || e1_type == "String" || e1_type == "Bool")
        && (e2_type == "Int" || e2_type == "String" || e2_type == "Bool")) {
    if (e1_type != e2_type) {
      ct->semant_error(this) << "Equal comparator got arguments of different type. "
        << "e1 type: " << e1_type << " e2 type: " << e2_type << ".\n";
    }
  }
  type = idtable.add_string("Bool");
}

Expression leq_class::copy_Expression()
{
   return new leq_class(e1->copy_Expression(), e2->copy_Expression());
}


void leq_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "leq\n";
   e1->dump(stream, n+2);
   e2->dump(stream, n+2);
}

void leq_class::semant(ClassTableP ct, SymbolTableP st) {
  e1->semant(ct, st);
  e2->semant(ct, st);
  string e1_type = e1->get_type()->get_string();
  string e2_type = e2->get_type()->get_string();
  if (e1_type != "Int") {
    ct->semant_error(this) << "Compare(<=) operation accepts only int, e1 has type "<< e1_type  << "\n";
  }
  if (e2_type != "Int") {
    ct->semant_error(this) << "Compare(<=) operation accepts only int, e2 has type "<< e2_type  << "\n";
  }
  type = idtable.add_string("Bool");
}

Expression comp_class::copy_Expression()
{
   return new comp_class(e1->copy_Expression());
}


void comp_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "comp\n";
   e1->dump(stream, n+2);
}

void comp_class::semant(ClassTableP ct, SymbolTableP st) {
  e1->semant(ct, st);
  string e1_type = e1->get_type()->get_string();
  if (e1_type != "Bool") {
    ct->semant_error(this) << "compliment only accept Bool\n";
    exit(1);
  }
  type = idtable.add_string("Bool");
}

Expression int_const_class::copy_Expression()
{
   return new int_const_class(copy_Symbol(token));
}


void int_const_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "int_const\n";
   dump_Symbol(stream, n+2, token);
}

void int_const_class::semant(ClassTableP ct, SymbolTableP st) {
  type = idtable.add_string("Int");
}


Expression bool_const_class::copy_Expression()
{
   return new bool_const_class(copy_Boolean(val));
}


void bool_const_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "bool_const\n";
   dump_Boolean(stream, n+2, val);
}

void bool_const_class::semant(ClassTableP ct, SymbolTableP st) {
  type = idtable.add_string("Bool");
}

Expression string_const_class::copy_Expression()
{
   return new string_const_class(copy_Symbol(token));
}


void string_const_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "string_const\n";
   dump_Symbol(stream, n+2, token);
}

void string_const_class::semant(ClassTableP ct, SymbolTableP st) {
  type = idtable.add_string("String");
}

Expression new__class::copy_Expression()
{
   return new new__class(copy_Symbol(type_name));
}


void new__class::dump(ostream& stream, int n)
{
   stream << pad(n) << "new_\n";
   dump_Symbol(stream, n+2, type_name);
}

void new__class::semant(ClassTableP ct, SymbolTableP st) {
  type = type_name;
}

Expression isvoid_class::copy_Expression()
{
   return new isvoid_class(e1->copy_Expression());
}


void isvoid_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "isvoid\n";
   e1->dump(stream, n+2);
}

void isvoid_class::semant(ClassTableP ct, SymbolTableP st) {
  e1->semant(ct, st);
  type = idtable.add_string("Bool");
}

Expression no_expr_class::copy_Expression()
{
   return new no_expr_class();
}


void no_expr_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "no_expr\n";
}

void no_expr_class::semant(ClassTableP ct, SymbolTableP st) {
}

Expression object_class::copy_Expression()
{
   return new object_class(copy_Symbol(name));
}


void object_class::dump(ostream& stream, int n)
{
   stream << pad(n) << "object\n";
   dump_Symbol(stream, n+2, name);
}

void object_class::semant(ClassTableP ct, SymbolTableP st) {
  string name_str = name->get_string();
  if (name_str == "self") {
    type = idtable.add_string("SELF_TYPE");
  } else {
    // Find the symbol in any scope.
    string* tmp = st->lookup(name_str);
    if (tmp == NULL) {
      ct->semant_error(this) << "ID " << name_str << " not defined.\n";
      type = idtable.add_string("Object");
    } else {
      char* tmp_char = strdup(tmp->c_str());
      type = idtable.add_string(tmp_char);
      free(tmp_char);
    }
  }
}

// interfaces used by Bison
Classes nil_Classes()
{
   return new nil_node<Class_>();
}

Classes single_Classes(Class_ e)
{
   return new single_list_node<Class_>(e);
}

Classes append_Classes(Classes p1, Classes p2)
{
   return new append_node<Class_>(p1, p2);
}

Features nil_Features()
{
   return new nil_node<Feature>();
}

Features single_Features(Feature e)
{
   return new single_list_node<Feature>(e);
}

Features append_Features(Features p1, Features p2)
{
   return new append_node<Feature>(p1, p2);
}

Formals nil_Formals()
{
   return new nil_node<Formal>();
}

Formals single_Formals(Formal e)
{
   return new single_list_node<Formal>(e);
}

Formals append_Formals(Formals p1, Formals p2)
{
   return new append_node<Formal>(p1, p2);
}

Expressions nil_Expressions()
{
   return new nil_node<Expression>();
}

Expressions single_Expressions(Expression e)
{
   return new single_list_node<Expression>(e);
}

Expressions append_Expressions(Expressions p1, Expressions p2)
{
   return new append_node<Expression>(p1, p2);
}

Cases nil_Cases()
{
   return new nil_node<Case>();
}

Cases single_Cases(Case e)
{
   return new single_list_node<Case>(e);
}

Cases append_Cases(Cases p1, Cases p2)
{
   return new append_node<Case>(p1, p2);
}

Program program(Classes classes)
{
  return new program_class(classes);
}

Class_ class_(Symbol name, Symbol parent, Features features, Symbol filename)
{
  return new class__class(name, parent, features, filename);
}

Feature method(Symbol name, Formals formals, Symbol return_type, Expression expr)
{
  return new method_class(name, formals, return_type, expr);
}

Feature attr(Symbol name, Symbol type_decl, Expression init)
{
  return new attr_class(name, type_decl, init);
}

Formal formal(Symbol name, Symbol type_decl)
{
  return new formal_class(name, type_decl);
}

Case branch(Symbol name, Symbol type_decl, Expression expr)
{
  return new branch_class(name, type_decl, expr);
}

Expression assign(Symbol name, Expression expr)
{
  return new assign_class(name, expr);
}

Expression static_dispatch(Expression expr, Symbol type_name, Symbol name, Expressions actual)
{
  return new static_dispatch_class(expr, type_name, name, actual);
}

Expression dispatch(Expression expr, Symbol name, Expressions actual)
{
  return new dispatch_class(expr, name, actual);
}

Expression cond(Expression pred, Expression then_exp, Expression else_exp)
{
  return new cond_class(pred, then_exp, else_exp);
}

Expression loop(Expression pred, Expression body)
{
  return new loop_class(pred, body);
}

Expression typcase(Expression expr, Cases cases)
{
  return new typcase_class(expr, cases);
}

Expression block(Expressions body)
{
  return new block_class(body);
}

Expression let(Symbol identifier, Symbol type_decl, Expression init, Expression body)
{
  return new let_class(identifier, type_decl, init, body);
}

Expression plus(Expression e1, Expression e2)
{
  return new plus_class(e1, e2);
}

Expression sub(Expression e1, Expression e2)
{
  return new sub_class(e1, e2);
}

Expression mul(Expression e1, Expression e2)
{
  return new mul_class(e1, e2);
}

Expression divide(Expression e1, Expression e2)
{
  return new divide_class(e1, e2);
}

Expression neg(Expression e1)
{
  return new neg_class(e1);
}

Expression lt(Expression e1, Expression e2)
{
  return new lt_class(e1, e2);
}

Expression eq(Expression e1, Expression e2)
{
  return new eq_class(e1, e2);
}

Expression leq(Expression e1, Expression e2)
{
  return new leq_class(e1, e2);
}

Expression comp(Expression e1)
{
  return new comp_class(e1);
}

Expression int_const(Symbol token)
{
  return new int_const_class(token);
}

Expression bool_const(Boolean val)
{
  return new bool_const_class(val);
}

Expression string_const(Symbol token)
{
  return new string_const_class(token);
}

Expression new_(Symbol type_name)
{
  return new new__class(type_name);
}

Expression isvoid(Expression e1)
{
  return new isvoid_class(e1);
}

Expression no_expr()
{
  return new no_expr_class();
}

Expression object(Symbol name)
{
  return new object_class(name);
}

