#ifndef SEMANT_H_
#define SEMANT_H_

#include <assert.h>
#include <iostream>  
#include "cool-tree.h"
#include "stringtab.h"
#include "symtab.h"
#include "list.h"

#include <map>
#include <string>
#include <vector>
#include <set>

using std::map;
using std::string;
using std::vector;
using std::set;

#define TRUE 1
#define FALSE 0

class ClassTable;
typedef ClassTable *ClassTableP;

extern const char * const SELFTYPE_STR;
extern const char * const NO_CLASS_STR;

// This is a structure that may be used to contain the semantic
// information such as the inheritance graph.  You may use it or not as
// you like: it is only here to provide a container for the supplied
// methods.

class ClassTable {
private:
  int semant_errors;
  void install_basic_classes();
  ostream& error_stream;
  Classes classes_;

  // Semantic checks at class level:
  // 1. a class is defined only once.
  // 2. Int, String, Bool cannot be inherit from.
  // 3. There is no cycle in the class hierarchy.
  void check_inheritance(string cn, Class_ c);

public:
  ClassTable(Classes);
  int errors() { return semant_errors; }
  ostream& semant_error();
  ostream& semant_error(Class_ c);
  ostream& semant_error(Symbol filename, tree_node *t);
  // A newly defined method.
  ostream& semant_error(tree_node *t);

  // Build related data structure and run the semantic check on classes.
  // Will call semant_error() to report errors if any.
  void check_classes();

  void check_features();

  void cross_check_features();

  // Recursively call the semantic check functions on the AST.
  void semant();

  // Set of basic classes.
  set<string> basic_classes;

  // Class map.
  map<string, Class_> class_map;

  // Inner map: method name to argument type map.
  // Outer map: class name to all methods map.
  // Cool does not support function overload, so multiply definition
  // of a method in the same class with the same name is an error.
  map<string, map<string, vector<string> > > methods_map;

  // Inner map: attribute name to attribute type.
  // Outer map: class name to all attributes.
  map<string, map<string, string> > attrs_map;

  // Finds the least upper bound of two types.
  string lub(string a, string b);

  // Decides if type a is a subtype of type b.
  bool isSubType(string a, string b);

  bool isValidAttribute(tree_node* node, string name);
  bool isAttributeRedefined(string parent_class, string name);

  bool isValidMethod(tree_node* node, string name);
  bool isValidRedefinition(tree_node* node, string parent_class,
                           string name, const vector<string>& sig);

  // Return if the input is a valid attribute name.
  // TODO: should extend this to check against a list of reserved keywords.
  bool isValidVariableName(string name);

  // A helper function to return the parent class name of the input class.
  string getParentClassName(string class_name);

  // Get the signiture of a method start at the class given by class name.
  // Return false if no such method exist.
  bool getMethodSig(string class_name, string method_name, vector<string>* sig);

  string current_class_;
  Symbol current_filename_;
};


#endif

