

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "semant.h"
#include "utilities.h"


extern int semant_debug;
extern char *curr_filename;

//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
static Symbol 
    arg,
    arg2,
    Bool,
    concat,
    cool_abort,
    copy,
    Int,
    in_int,
    in_string,
    IO,
    length,
    Main,
    main_meth,
    No_class,
    No_type,
    Object,
    out_int,
    out_string,
    prim_slot,
    self,
    SELF_TYPE,
    Str,
    str_field,
    substr,
    type_name,
    val;
//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
    arg         = idtable.add_string("arg");
    arg2        = idtable.add_string("arg2");
    Bool        = idtable.add_string("Bool");
    concat      = idtable.add_string("concat");
    cool_abort  = idtable.add_string("abort");
    copy        = idtable.add_string("copy");
    Int         = idtable.add_string("Int");
    in_int      = idtable.add_string("in_int");
    in_string   = idtable.add_string("in_string");
    IO          = idtable.add_string("IO");
    length      = idtable.add_string("length");
    Main        = idtable.add_string("Main");
    main_meth   = idtable.add_string("main");
    //   _no_class is a symbol that can't be the name of any 
    //   user-defined class.
    No_class    = idtable.add_string("_no_class");
    No_type     = idtable.add_string("_no_type");
    Object      = idtable.add_string("Object");
    out_int     = idtable.add_string("out_int");
    out_string  = idtable.add_string("out_string");
    prim_slot   = idtable.add_string("_prim_slot");
    self        = idtable.add_string("self");
    SELF_TYPE   = idtable.add_string("SELF_TYPE");
    Str         = idtable.add_string("String");
    str_field   = idtable.add_string("_str_field");
    substr      = idtable.add_string("substr");
    type_name   = idtable.add_string("type_name");
    val         = idtable.add_string("_val");
}

const char * const SELFTYPE_STR = "SELF_TYPE";
const char * const NO_CLASS_STR = "_no_class";

ClassTable::ClassTable(Classes classes) : semant_errors(0) , error_stream(cerr) {
  classes_ = classes;
}

// The objects built here are pointers.
void ClassTable::install_basic_classes() {

    // The tree package uses these globals to annotate the classes built below.
   // curr_lineno  = 0;
    Symbol filename = stringtable.add_string("<basic class>");
    
    // The following demonstrates how to create dummy parse trees to
    // refer to basic Cool classes.  There's no need for method
    // bodies -- these are already built into the runtime system.
    
    // IMPORTANT: The results of the following expressions are
    // stored in local variables.  You will want to do something
    // with those variables at the end of this method to make this
    // code meaningful.

    // 
    // The Object class has no parent class. Its methods are
    //        abort() : Object    aborts the program
    //        type_name() : Str   returns a string representation of class name
    //        copy() : SELF_TYPE  returns a copy of the object
    //
    // There is no need for method bodies in the basic classes---these
    // are already built in to the runtime system.

    Class_ Object_class =
	class_(Object, 
	       No_class,
	       append_Features(
			       append_Features(
					       single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
					       single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
			       single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	       filename);
    class_map["Object"] = Object_class;
    basic_classes.insert("Object");

    // 
    // The IO class inherits from Object. Its methods are
    //        out_string(Str) : SELF_TYPE       writes a string to the output
    //        out_int(Int) : SELF_TYPE            "    an int    "  "     "
    //        in_string() : Str                 reads a string from the input
    //        in_int() : Int                      "   an int     "  "     "
    //
    Class_ IO_class = 
	class_(IO, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       single_Features(method(out_string, single_Formals(formal(arg, Str)),
										      SELF_TYPE, no_expr())),
							       single_Features(method(out_int, single_Formals(formal(arg, Int)),
										      SELF_TYPE, no_expr()))),
					       single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
			       single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
	       filename);  
    class_map["IO"] = IO_class;
    basic_classes.insert("IO");

    //
    // The Int class has no methods and only a single attribute, the
    // "val" for the integer. 
    //
    Class_ Int_class =
	class_(Int, 
	       Object,
	       single_Features(attr(val, prim_slot, no_expr())),
	       filename);
    class_map["Int"] = Int_class;
    basic_classes.insert("Int");

    //
    // Bool also has only the "val" slot.
    //
    Class_ Bool_class =
	class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename);
    class_map["Bool"] = Bool_class;
    basic_classes.insert("Bool");

    //
    // The class Str has a number of slots and operations:
    //       val                                  the length of the string
    //       str_field                            the string itself
    //       length() : Int                       returns length of the string
    //       concat(arg: Str) : Str               performs string concatenation
    //       substr(arg: Int, arg2: Int): Str     substring selection
    //       
    Class_ Str_class =
	class_(Str, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       append_Features(
									       single_Features(attr(val, Int, no_expr())),
									       single_Features(attr(str_field, prim_slot, no_expr()))),
							       single_Features(method(length, nil_Formals(), Int, no_expr()))),
					       single_Features(method(concat, 
								      single_Formals(formal(arg, Str)),
								      Str, 
								      no_expr()))),
			       single_Features(method(substr, 
						      append_Formals(single_Formals(formal(arg, Int)), 
								     single_Formals(formal(arg2, Int))),
						      Str, 
						      no_expr()))),
	       filename);
    class_map["String"] = Str_class;
    basic_classes.insert("String");
}

////////////////////////////////////////////////////////////////////
//
// semant_error is an overloaded function for reporting errors
// during semantic analysis.  There are three versions:
//
//    ostream& ClassTable::semant_error()                
//
//    ostream& ClassTable::semant_error(Class_ c)
//       print line number and filename for `c'
//
//    ostream& ClassTable::semant_error(Symbol filename, tree_node *t)  
//       print a line number and filename
//
///////////////////////////////////////////////////////////////////

ostream& ClassTable::semant_error(Class_ c)
{                                                             
    return semant_error(c->get_filename(),c);
}    

ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
{
    error_stream << filename << ":" << t->get_line_number() << ": ";
    return semant_error();
}

ostream& ClassTable::semant_error()                  
{                                                 
    semant_errors++;                            
    return error_stream;
} 

ostream& ClassTable::semant_error(tree_node *t)
{
    error_stream << current_filename_ << ":" << t->get_line_number() << ": ";
    return semant_error();
}

void ClassTable::check_classes() {
  install_basic_classes();
  
  for (int i = classes_->first(); classes_->more(i); i = classes_->next(i)) {
    Class_ class_elem = classes_->nth(i);
    string class_name = class_elem->get_classname()->get_string();
    if (class_name == SELFTYPE_STR) {
      semant_error(class_elem) << "Redefinition of SELF_TYPE.\n";
      continue;
    }
    if (class_map.find(class_name) != class_map.end()) {
      semant_error(class_elem) << "Redefinition of a class.\n";
      continue;
    }
    class_map[class_elem->get_classname()->get_string()] = class_elem;
  }
  if (errors()) {
    cerr << "Compilation halted due to static semantic errors." << endl;
    exit(1);
  }

  for (map<string, Class_>::iterator it = class_map.begin();
       it != class_map.end(); it++) {
    check_inheritance(it->first, it->second);
  }
  if (errors()) {
    cerr << "Compilation halted due to static semantic errors." << endl;
    exit(1);
  }
}

void ClassTable::check_inheritance(string original_class, Class_ c) {
  string parent_class_name = c->get_parent()->get_string();
  if (original_class == parent_class_name) {
    semant_error(c) << "Cycle in the inheritance graph\n";
    return;
  }

  // TODO: ideally the following three checks only need to run once
  // for each class.
  if (string("Bool").compare(parent_class_name) == 0) {
    semant_error(c) << "Bool cannot be inherit from.\n";
    return;
  }
  if (string("Int").compare(parent_class_name) == 0) {
    semant_error(c) << "Int cannot be inherit from.\n";
    return;
  }
  if (string("String").compare(parent_class_name) == 0) {
    semant_error(c) << "String cannot be inherit from.\n";
    return;
  }

  // Reached the end of the class hierarchy.
  if (string("_no_class").compare(parent_class_name) == 0) {
    return;
  }

  if (class_map.find(parent_class_name) == class_map.end()) {
    semant_error(c) << "Inherit from an undefined class.\n";
    return;
  } else {
    check_inheritance(original_class, class_map[parent_class_name]);
  }
}

void ClassTable::check_features() {
  // 1. Builds method_map and attr_map.
  for (map<string, Class_>::iterator it = class_map.begin();
       it != class_map.end(); it++) {
    current_class_ = it->first;
    current_filename_ = it->second->get_filename();
    it->second->check_features(this);
  }

  if (class_map.find("Main") == class_map.end()) {
    semant_error() << "Class Main is not defined.\n";
    return;
  }

  if (methods_map["Main"].find("main") == methods_map["Main"].end()) {
    semant_error() << "No 'main' method in class Main.\n";
  }
}

void ClassTable::cross_check_features() {
// 1. check if a variable is not redifined accross classes.
// 2. check if a method is redefined properly accross classes.
// 3. check method argument types(cannot be self type) and return type are properly defined.
// 4. remove invalid attribute and method.
// TODO: build a type hierarchy tree here and check from top to bottom.
// This is needed because the expected behavior in case of a redefinition is the upper class will override.
  for (map<string, Class_>::iterator it = class_map.begin();
       it != class_map.end(); it++) {
    current_class_ = it->first;
    current_filename_ = it->second->get_filename();

    // Do not check basic classes.
    if (basic_classes.find(it->first) != basic_classes.end()) {
      continue;
    }

    it->second->cross_check_features(this);
  }
}

bool ClassTable::isValidAttribute(tree_node* node, string name) {
  string type = attrs_map[current_class_][name];
  if (type != SELFTYPE_STR && class_map.find(type) == class_map.end()) {
    semant_error(node) << "Attribute type is not defined.\n";
    return false;
  }
  string parent_class_name = getParentClassName(current_class_);
  if (isAttributeRedefined(parent_class_name, name)) {
    semant_error(node) << "Attribute is already defined in a parent type.\n";
    return false;
  }
  return true;
}

bool ClassTable::isAttributeRedefined(string parent_class, string name) {
  if (parent_class == NO_CLASS_STR) {
    return false;
  }
  if (attrs_map[parent_class].find(name) != attrs_map[parent_class].end()) {
    return true;
  } else {
    return isAttributeRedefined(getParentClassName(parent_class), name);
  }
}

bool ClassTable::isValidMethod(tree_node* node, string name) {
  const vector<string>& sig = methods_map[current_class_][name];
  // Parser ensures sig has size >= 1.
  string rtn_type = sig.back();
  if (rtn_type != SELFTYPE_STR && class_map.find(rtn_type) == class_map.end()) {
    semant_error(node) << "Method return type is not defined.\n";
    return false;
  }
  return isValidRedefinition(node, getParentClassName(current_class_), name, sig);
}

bool ClassTable::isValidRedefinition(tree_node* node, string parent_class,
                                     string name, const vector<string>& sig) {
  if (parent_class == NO_CLASS_STR) {
    return true;
  }
  if (methods_map[parent_class].find(name)
      != methods_map[parent_class].end()) {
    const vector<string>& existing_sig = methods_map[parent_class][name];
    if (existing_sig.size() != sig.size()) {
      semant_error(node) << "Redefinition: parameter list size doesn't match.\n";
      return false;
    }
    if (existing_sig.back() != sig.back()) {
      semant_error(node) << "Redefinition: return type doesn't match.\n";
      return false;
    }
    for (int i = 0; i < ((int)existing_sig.size() - 1); i++) {
      if (existing_sig[i] != sig[i]) {
        semant_error(node) << "Redefinition: parameter type doesn't match.\n";
        return false;
      }
    }
  }
  return isValidRedefinition(node, getParentClassName(parent_class),
                             name, sig);
}

void ClassTable::semant() {
  for (map<string, Class_>::iterator it = class_map.begin();
       it != class_map.end(); it++) {
    current_class_ = it->first;
    current_filename_ = it->second->get_filename();
    it->second->semant(this);
  }
}

// Finds the least upper bound of two types.
string ClassTable::lub(string a, string b) {
  if (a == "SELF_TYPE" && b == "SELF_TYPE") {
    return current_class_;
  }
  if (a == "SELF_TYPE") {
    return lub(current_class_, b);
  }
  if (b == "SELF_TYPE") {
    return lub(a, current_class_);
  }
  // Neither a nor b is SELF_TYPE.
  vector<string> alist, blist;
  while (a != "_no_class") {
    alist.push_back(a);
    assert(class_map.find(a) != class_map.end());
    Class_ a_class = class_map[a];
    a = a_class->get_parent()->get_string();
  }

  while (b != "_no_class") {
    blist.push_back(b);
    assert(class_map.find(b) != class_map.end());
    Class_ b_class = class_map[b];
    b = b_class->get_parent()->get_string();
  }

  string rtn = "Object";
  while (!alist.empty() && !blist.empty()) {
    if (alist.back() == blist.back()) {
      rtn = alist.back();
      alist.pop_back();
      blist.pop_back();
    } else {
      break;
    }
  }
  return rtn;
}

// Decides if type a is a subtype of type b. a <= b
bool ClassTable::isSubType(string a, string b) {
  if (a == "SELF_TYPE" && b == "SELF_TYPE") {
    return true;
  }
  if (a == "SELF_TYPE") {
    return isSubType(current_class_, b);
  }
  if (b == "SELF_TYPE") {
    return false;
  }
  // Neither a nor b is SELF_TYPE.
  while (a != "_no_class") {
    // printf("a: %s, b: %s\n", a.c_str(), b.c_str());
    if (a == b) {
      return true;
    }
    // a should always be available in the class map.
    assert(class_map.find(a) != class_map.end());
    Class_ a_class = class_map[a];
    a = a_class->get_parent()->get_string();
  }
  return false;
}


string ClassTable::getParentClassName(string class_name) {
  if (class_map.find(class_name) == class_map.end()) {
    semant_error() << "Class " << class_name << " not defined.\n";
    exit(1);
  }
  Class_ class_struct = class_map[class_name];
  return class_struct->get_parent()->get_string();
}

bool ClassTable::getMethodSig(string class_name, string method_name, vector<string>* sig) {
  if (class_name == "_no_class") {
    return false;
  }
  // TODO: the class we are examining here should always be valid. Proof?
  if (methods_map[class_name].find(method_name) != methods_map[class_name].end()) {
    *sig = methods_map[class_name][method_name];
    return true;
  }
  return getMethodSig(getParentClassName(class_name), method_name, sig);
}

bool ClassTable::isValidVariableName(string name) {
  if (name == "self") {
    return false;
  } else {
    return true;
  }
}

/*   This is the entry point to the semantic checker.

     Your checker should do the following two things:

     1) Check that the program is semantically correct
     2) Decorate the abstract syntax tree with type information
        by setting the `type' field in each Expression node.
        (see `tree.h')

     You are free to first do 1), make sure you catch all semantic
     errors. Part 2) can be done in a second stage, when you want
     to build mycoolc.
 */
void program_class::semant()
{
    initialize_constants();

    /* ClassTable constructor may do some semantic analysis */
    ClassTable *class_table = new ClassTable(classes);
    
    // Check class hierarchy.
    class_table->check_classes();

    // Build attribute table and method table.
    class_table->check_features();

    // TODO: check the attribute redefinition accross classes.
    // Check if a method is valid.
    class_table->cross_check_features();

    class_table->semant();

    if (class_table->errors()) {
	cerr << "Compilation halted due to static semantic errors." << endl;
        exit(1);
    }
}

