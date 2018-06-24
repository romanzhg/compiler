#include <assert.h>
#include <stdio.h>
#include "emit.h"
#include "cool-tree.h"
#include "symtab.h"

// custom include
#include <map>
#include <vector>
#include <string>
#include <utility>

using std::map;
using std::vector;
using std::string;
using std::pair;

enum Basicness     {Basic, NotBasic};
#define TRUE 1
#define FALSE 0

class CgenClassTable;
typedef CgenClassTable *CgenClassTableP;

class CgenNode;
typedef CgenNode *CgenNodeP;

class Environment;
typedef Environment* EnvironmentP;

class CgenClassTable : public SymbolTable<Symbol,CgenNode> {
private:
   List<CgenNode> *nds;
   ostream& str;
   int stringclasstag;
   int intclasstag;
   int boolclasstag;

// The following methods emit code for
// constants and global declarations.

   void code_global_data();
   void code_global_text();
   void code_bools(int);
   void code_select_gc();
   void code_constants();

   // A table of class names and class objects.
   void set_class_tag();
   void code_class_table();
   void code_dispatch_table();
   void code_prototype_objects();

   void code_object_initializer();
   void code_method_def();


   // Helper functions.
   

// The following creates an inheritance graph from
// a list of classes.  The graph is implemented as
// a tree of `CgenNode', and class names are placed
// in the base class symbol table.

   void install_basic_classes();
   void install_class(CgenNodeP nd);
   void install_classes(Classes cs);
   void build_inheritance_tree();
   void set_relations(CgenNodeP nd);
public:
   CgenClassTable(Classes, ostream& str);
   void code();
   CgenNodeP root();

   CgenNodeP current_node_;
   int label_count;
   int get_label() { return label_count++; };

   // Sort the cases according to their order in a dfs of the type tree.
   void sort_cases(const vector<Case>& input, vector<Case>& output);
};


class CgenNode : public class__class {
private: 
   CgenNodeP parentnd;                        // Parent of class
   List<CgenNode> *children;                  // Children of class
   Basicness basic_status;                    // `Basic' if class is basic
                                              // `NotBasic' otherwise

public:
   CgenNode(Class_ c,
            Basicness bstatus,
            CgenClassTableP class_table);

   void add_child(CgenNodeP child);
   List<CgenNode> *get_children() { return children; }
   void set_parentnd(CgenNodeP p);
   CgenNodeP get_parentnd() { return parentnd; }
   int basic() { return (basic_status == Basic); }

   // Public methods and fields.
   int classtag_;
   // Class tag of the last child.
   int classtag_lb_;

   int get_proto_obj_size();

   vector<Symbol> attributes_;
   vector<pair<Symbol, Symbol> > internal_disp_;

   void gen_dispatch_table_df(vector<pair<Symbol, Symbol> > disp, ostream& os);
   void code_initialization(CgenClassTableP ct, ostream& os);

   void code_default_values_rec(vector<Symbol>& attribute_vector, ostream& os) {
     if (strcmp(name->get_string(), NO_CLASS) == 0) {
       return;
     }
     parentnd->code_default_values_rec(attribute_vector, os);
     code_default_values(attribute_vector, os);
   };

   void code_method(CgenClassTableP, ostream&);

   int get_method_offset(Symbol method_name);

   // Set class tag in a depth first way.
   int set_class_tag_df(int& tmp_tag) {
     if (!basic()) {
       classtag_ = tmp_tag;
       tmp_tag++;
     }
     int lb = classtag_;
     for (List<CgenNode>* l = children; l; l = l->tl()) {
       int tmp = l->hd()->set_class_tag_df(tmp_tag);
       if (lb < tmp) {
         lb = tmp;
       }
     }
     classtag_lb_ = lb;
     return lb;
   }

   void visit_nodes_df(const vector<Case>& input, vector<Case>& output);
};

// Environment is created for initialization code generation and method code
// generation. They are specific to the method.
class Environment {
 public:
  // Variables in heap don't need to stay in a symbol table, since there
  // is only one heap.
  SymbolTable<Symbol, int> heap_;
  // Variables in stack may override variables in heap.
  SymbolTable<Symbol, int> stack_;
  int let_offset;

  bool is_attribute(Symbol);
  int get_offset(Symbol);

  // The result should be used with SELF.

  void addid_attribute(Symbol, int*);

  // The result should be used with FP.
  // TODO: add functions to enter a new scope.
  void addid_argument(Symbol, int*);

  void enter_let(Symbol);
  void exit_let();

  Environment() {
    let_offset = 0;
    heap_.enterscope();
    stack_.enterscope();
  };

  ~Environment() {heap_.exitscope(); stack_.enterscope();};
};

class BoolConst 
{
 private: 
  int val;
 public:
  BoolConst(int);
  void code_def(ostream&, int boolclasstag);
  void code_ref(ostream&) const;
};

