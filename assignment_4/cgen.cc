
//**************************************************************
//
// Code generator SKELETON
//
// Read the comments carefully. Make sure to
//    initialize the base class tags in
//       `CgenClassTable::CgenClassTable'
//
//    Add the label for the dispatch tables to
//       `IntEntry::code_def'
//       `StringEntry::code_def'
//       `BoolConst::code_def'
//
//    Add code to emit everyting else that is needed
//       in `CgenClassTable::code'
//
//
// The files as provided will produce code to begin the code
// segments, declare globals, and emit constants.  You must
// fill in the rest.
//
//**************************************************************

#include <algorithm>
#include <vector>

#include "cgen.h"
#include "cgen_gc.h"

extern void emit_string_constant(ostream& str, char *s);
extern int cgen_debug;

//
// Three symbols from the semantic analyzer (semant.cc) are used.
// If e : No_type, then no code is generated for e.
// Special code is generated for new SELF_TYPE.
// The name "self" also generates code different from other references.
//
//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
Symbol 
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

static char *gc_init_names[] =
  { "_NoGC_Init", "_GenGC_Init", "_ScnGC_Init" };
static char *gc_collect_names[] =
  { "_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect" };


//  BoolConst is a class that implements code generation for operations
//  on the two booleans, which are given global names here.
BoolConst falsebool(FALSE);
BoolConst truebool(TRUE);

//*********************************************************
//
// Define method for code generation
//
// This is the method called by the compiler driver
// `cgtest.cc'. cgen takes an `ostream' to which the assembly will be
// emmitted, and it passes this and the class list of the
// code generator tree to the constructor for `CgenClassTable'.
// That constructor performs all of the work of the code
// generator.
//
//*********************************************************

void program_class::cgen(ostream &os) 
{
  // spim wants comments to start with '#'
  os << "# start of generated code\n";

  initialize_constants();
  CgenClassTable *codegen_classtable = new CgenClassTable(classes,os);

  os << "\n# end of generated code\n";
}


//////////////////////////////////////////////////////////////////////////////
//
//  emit_* procedures
//
//  emit_X  writes code for operation "X" to the output stream.
//  There is an emit_X for each opcode X, as well as emit_ functions
//  for generating names according to the naming conventions (see emit.h)
//  and calls to support functions defined in the trap handler.
//
//  Register names and addresses are passed as strings.  See `emit.h'
//  for symbolic names you can use to refer to the strings.
//
//////////////////////////////////////////////////////////////////////////////

static void emit_load(char *dest_reg, int offset, char *source_reg, ostream& s)
{
  s << LW << dest_reg << " " << offset * WORD_SIZE << "(" << source_reg << ")" 
    << endl;
}

////////////////////////////////////////////////////
/*
static void emit_load_byte(char *dest_reg, int offset, char *source_reg, ostream& s)
{
  s << LBU << dest_reg << " " << offset << "(" << source_reg << ")" 
    << endl;
}
*/

static void emit_store(char *source_reg, int offset, char *dest_reg, ostream& s)
{
  s << SW << source_reg << " " << offset * WORD_SIZE << "(" << dest_reg << ")"
      << endl;
}

static void emit_load_imm(char *dest_reg, int val, ostream& s)
{ s << LI << dest_reg << " " << val << endl; }

static void emit_load_address(char *dest_reg, char *address, ostream& s)
{ s << LA << dest_reg << " " << address << endl; }

static void emit_partial_load_address(char *dest_reg, ostream& s)
{ s << LA << dest_reg << " "; }

static void emit_load_bool(char *dest, const BoolConst& b, ostream& s)
{
  emit_partial_load_address(dest,s);
  b.code_ref(s);
  s << endl;
}

static void emit_load_string(char *dest, StringEntry *str, ostream& s)
{
  emit_partial_load_address(dest,s);
  str->code_ref(s);
  s << endl;
}

static void emit_load_int(char *dest, IntEntry *i, ostream& s)
{
  emit_partial_load_address(dest,s);
  i->code_ref(s);
  s << endl;
}

static void emit_move(char *dest_reg, char *source_reg, ostream& s)
{ s << MOVE << dest_reg << " " << source_reg << endl; }

static void emit_neg(char *dest, char *src1, ostream& s)
{ s << NEG << dest << " " << src1 << endl; }

static void emit_add(char *dest, char *src1, char *src2, ostream& s)
{ s << ADD << dest << " " << src1 << " " << src2 << endl; }

static void emit_addu(char *dest, char *src1, char *src2, ostream& s)
{ s << ADDU << dest << " " << src1 << " " << src2 << endl; }

static void emit_addiu(char *dest, char *src1, int imm, ostream& s)
{ s << ADDIU << dest << " " << src1 << " " << imm << endl; }

static void emit_div(char *dest, char *src1, char *src2, ostream& s)
{ s << DIV << dest << " " << src1 << " " << src2 << endl; }

static void emit_mul(char *dest, char *src1, char *src2, ostream& s)
{ s << MUL << dest << " " << src1 << " " << src2 << endl; }

static void emit_sub(char *dest, char *src1, char *src2, ostream& s)
{ s << SUB << dest << " " << src1 << " " << src2 << endl; }

static void emit_sll(char *dest, char *src1, int num, ostream& s)
{ s << SLL << dest << " " << src1 << " " << num << endl; }

static void emit_jalr(char *dest, ostream& s)
{ s << JALR << "\t" << dest << endl; }

static void emit_jal(char *address,ostream &s)
{ s << JAL << address << endl; }

static void emit_return(ostream& s)
{ s << RET << endl; }

static void emit_gc_assign(ostream& s)
{ s << JAL << "_GenGC_Assign" << endl; }

static void emit_disptable_ref(Symbol sym, ostream& s)
{  s << sym << DISPTAB_SUFFIX; }

static void emit_init_ref(Symbol sym, ostream& s)
{ s << sym << CLASSINIT_SUFFIX; }

static void emit_label_ref(int l, ostream &s)
{ s << "label" << l; }

static void emit_protobj_ref(Symbol sym, ostream& s)
{ s << sym << PROTOBJ_SUFFIX; }

static void emit_method_ref(Symbol classname, Symbol methodname, ostream& s)
{ s << classname << METHOD_SEP << methodname; }

static void emit_label_def(int l, ostream &s)
{
  emit_label_ref(l,s);
  s << ":" << endl;
}

static void emit_beqz(char *source, int label, ostream &s)
{
  s << BEQZ << source << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_beq(char *src1, char *src2, int label, ostream &s)
{
  s << BEQ << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bne(char *src1, char *src2, int label, ostream &s)
{
  s << BNE << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bleq(char *src1, char *src2, int label, ostream &s)
{
  s << BLEQ << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_blt(char *src1, char *src2, int label, ostream &s)
{
  s << BLT << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_blti(char *src1, int imm, int label, ostream &s)
{
  s << BLT << src1 << " " << imm << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bgti(char *src1, int imm, int label, ostream &s)
{
  s << BGT << src1 << " " << imm << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_branch(int l, ostream& s)
{
  s << BRANCH;
  emit_label_ref(l,s);
  s << endl;
}

//
// Push a register on the stack. The stack grows towards smaller addresses.
//
static void emit_push(char *reg, ostream& str)
{
  emit_addiu(SP,SP,-4,str);
  emit_store(reg,1,SP,str);
}

static void emit_pop(char *reg, ostream& str)
{
  emit_load(reg,1,SP,str);
  emit_addiu(SP,SP,4,str);
}

//
// Fetch the integer value in an Int object.
// Emits code to fetch the integer value of the Integer object pointed
// to by register source into the register dest
//
static void emit_fetch_int(char *dest, char *source, ostream& s)
{ emit_load(dest, DEFAULT_OBJFIELDS, source, s); }

//
// Emits code to store the integer value contained in register source
// into the Integer object pointed to by dest.
//
static void emit_store_int(char *source, char *dest, ostream& s)
{ emit_store(source, DEFAULT_OBJFIELDS, dest, s); }


static void emit_test_collector(ostream &s)
{
  emit_push(ACC, s);
  emit_move(ACC, SP, s); // stack end
  emit_move(A1, ZERO, s); // allocate nothing
  s << JAL << gc_collect_names[cgen_Memmgr] << endl;
  emit_addiu(SP,SP,4,s);
  emit_load(ACC,0,SP,s);
}

static void emit_gc_check(char *source, ostream &s)
{
  if (source != (char*)A1) emit_move(A1, source, s);
  s << JAL << "_gc_check" << endl;
}

static void emit_method_start(ostream& str)
{
  emit_addiu(SP, SP, -12, str);
  emit_store(FP, 3, SP, str);
  emit_store(SELF, 2, SP, str);
  emit_store(RA, 1, SP, str);
  emit_addiu(FP, SP, 4, str);
  emit_move(SELF, ACC, str);
}

static void emit_method_end(int additional_pop, ostream& str)
{
  emit_load(FP, 3, SP, str);
  emit_load(SELF, 2, SP, str);
  emit_load(RA, 1, SP, str);
  emit_addiu(SP, SP, 12, str);
  if (additional_pop != 0) {
    emit_addiu(SP, SP, 4 * additional_pop, str);
  }
  emit_return(str);
}

///////////////////////////////////////////////////////////////////////////////
//
// coding strings, ints, and booleans
//
// Cool has three kinds of constants: strings, ints, and booleans.
// This section defines code generation for each type.
//
// All string constants are listed in the global "stringtable" and have
// type StringEntry.  StringEntry methods are defined both for String
// constant definitions and references.
//
// All integer constants are listed in the global "inttable" and have
// type IntEntry.  IntEntry methods are defined for Int
// constant definitions and references.
//
// Since there are only two Bool values, there is no need for a table.
// The two booleans are represented by instances of the class BoolConst,
// which defines the definition and reference methods for Bools.
//
///////////////////////////////////////////////////////////////////////////////

//
// Strings
//
void StringEntry::code_ref(ostream& s)
{
  s << STRCONST_PREFIX << index;
}

//
// Emit code for a constant String.
// You should fill in the code naming the dispatch table.
//

void StringEntry::code_def(ostream& s, int stringclasstag)
{
  IntEntryP lensym = inttable.add_int(len);

  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s  << LABEL                                             // label
      << WORD << stringclasstag << endl                                 // tag
      << WORD << (DEFAULT_OBJFIELDS + STRING_SLOTS + (len+4)/4) << endl // size
      << WORD << "String_dispTab" << endl;                    // dispatch table
      s << WORD;  lensym->code_ref(s);  s << endl;            // string length
  emit_string_constant(s,str);                                // ascii string
  s << ALIGN;                                                 // align to word
}

//
// StrTable::code_string
// Generate a string object definition for every string constant in the 
// stringtable.
//
void StrTable::code_string_table(ostream& s, int stringclasstag)
{  
  for (List<StringEntry> *l = tbl; l; l = l->tl())
    l->hd()->code_def(s,stringclasstag);
}

//
// Ints
//
void IntEntry::code_ref(ostream &s)
{
  s << INTCONST_PREFIX << index;
}

//
// Emit code for a constant Integer.
// You should fill in the code naming the dispatch table.
//

void IntEntry::code_def(ostream &s, int intclasstag)
{
  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s << LABEL                                // label
      << WORD << intclasstag << endl                      // class tag
      << WORD << (DEFAULT_OBJFIELDS + INT_SLOTS) << endl  // object size
      << WORD << "Int_dispTab" << endl;                    // dispatch table
      s << WORD << str << endl;                           // integer value
}


//
// IntTable::code_string_table
// Generate an Int object definition for every Int constant in the
// inttable.
//
void IntTable::code_string_table(ostream &s, int intclasstag)
{
  for (List<IntEntry> *l = tbl; l; l = l->tl())
    l->hd()->code_def(s,intclasstag);
}


//
// Bools
//
BoolConst::BoolConst(int i) : val(i) { assert(i == 0 || i == 1); }

void BoolConst::code_ref(ostream& s) const
{
  s << BOOLCONST_PREFIX << val;
}
  
//
// Emit code for a constant Bool.
// You should fill in the code naming the dispatch table.
//

void BoolConst::code_def(ostream& s, int boolclasstag)
{
  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s << LABEL                                  // label
      << WORD << boolclasstag << endl                       // class tag
      << WORD << (DEFAULT_OBJFIELDS + BOOL_SLOTS) << endl   // object size
      << WORD << "Bool_dispTab" << endl;                    // dispatch table
      s << WORD << val << endl;                             // value (0 or 1)
}

//////////////////////////////////////////////////////////////////////////////
//
//  CgenClassTable methods
//
//////////////////////////////////////////////////////////////////////////////

//***************************************************
//
//  Emit code to start the .data segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_data()
{
  Symbol main    = idtable.lookup_string(MAINNAME);
  Symbol string  = idtable.lookup_string(STRINGNAME);
  Symbol integer = idtable.lookup_string(INTNAME);
  Symbol boolc   = idtable.lookup_string(BOOLNAME);

  str << "\t.data\n" << ALIGN;
  //
  // The following global names must be defined first.
  //
  str << GLOBAL << CLASSNAMETAB << endl;
  str << GLOBAL; emit_protobj_ref(main,str);    str << endl;
  str << GLOBAL; emit_protobj_ref(integer,str); str << endl;
  str << GLOBAL; emit_protobj_ref(string,str);  str << endl;
  str << GLOBAL; falsebool.code_ref(str);  str << endl;
  str << GLOBAL; truebool.code_ref(str);   str << endl;
  str << GLOBAL << INTTAG << endl;
  str << GLOBAL << BOOLTAG << endl;
  str << GLOBAL << STRINGTAG << endl;

  //
  // We also need to know the tag of the Int, String, and Bool classes
  // during code generation.
  //
  str << INTTAG << LABEL
      << WORD << intclasstag << endl;
  str << BOOLTAG << LABEL 
      << WORD << boolclasstag << endl;
  str << STRINGTAG << LABEL 
      << WORD << stringclasstag << endl;    
}


//***************************************************
//
//  Emit code to start the .text segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_text()
{
  str << GLOBAL << HEAP_START << endl
      << HEAP_START << LABEL 
      << WORD << 0 << endl
      << "\t.text" << endl
      << GLOBAL;
  emit_init_ref(idtable.add_string("Main"), str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("Int"),str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("String"),str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("Bool"),str);
  str << endl << GLOBAL;
  emit_method_ref(idtable.add_string("Main"), idtable.add_string("main"), str);
  str << endl;
}

void CgenClassTable::code_bools(int boolclasstag)
{
  falsebool.code_def(str,boolclasstag);
  truebool.code_def(str,boolclasstag);
}

void CgenClassTable::code_select_gc()
{
  //
  // Generate GC choice constants (pointers to GC functions)
  //
  str << GLOBAL << "_MemMgr_INITIALIZER" << endl;
  str << "_MemMgr_INITIALIZER:" << endl;
  str << WORD << gc_init_names[cgen_Memmgr] << endl;
  str << GLOBAL << "_MemMgr_COLLECTOR" << endl;
  str << "_MemMgr_COLLECTOR:" << endl;
  str << WORD << gc_collect_names[cgen_Memmgr] << endl;
  str << GLOBAL << "_MemMgr_TEST" << endl;
  str << "_MemMgr_TEST:" << endl;
  str << WORD << (cgen_Memmgr_Test == GC_TEST) << endl;
}


//********************************************************
//
// Emit code to reserve space for and initialize all of
// the constants.  Class names should have been added to
// the string table (in the supplied code, is is done
// during the construction of the inheritance graph), and
// code for emitting string constants as a side effect adds
// the string's length to the integer table.  The constants
// are emmitted by running through the stringtable and inttable
// and producing code for each entry.
//
//********************************************************

void CgenClassTable::code_constants()
{
  //
  // Add constants that are required by the code generator.
  //
  stringtable.add_string("");
  inttable.add_string("0");

  stringtable.code_string_table(str,stringclasstag);
  inttable.code_string_table(str,intclasstag);
  code_bools(boolclasstag);
}


CgenClassTable::CgenClassTable(Classes classes, ostream& s) : nds(NULL) , str(s)
{
   // For labels.
   label_count = 0;

   stringclasstag = 4 /* Change to your String class tag here */;
   intclasstag =    2 /* Change to your Int class tag here */;
   boolclasstag =   3 /* Change to your Bool class tag here */;

   enterscope();
   if (cgen_debug) cout << "Building CgenClassTable" << endl;
   install_basic_classes();
   install_classes(classes);
   build_inheritance_tree();

   code();
   exitscope();
}

void CgenClassTable::install_basic_classes()
{

// The tree package uses these globals to annotate the classes built below.
  //curr_lineno  = 0;
  Symbol filename = stringtable.add_string("<basic class>");

//
// A few special class names are installed in the lookup table but not
// the class list.  Thus, these classes exist, but are not part of the
// inheritance hierarchy.
// No_class serves as the parent of Object and the other special classes.
// SELF_TYPE is the self class; it cannot be redefined or inherited.
// prim_slot is a class known to the code generator.
//
  addid(No_class,
	new CgenNode(class_(No_class,No_class,nil_Features(),filename),
			    Basic,this));
  addid(SELF_TYPE,
	new CgenNode(class_(SELF_TYPE,No_class,nil_Features(),filename),
			    Basic,this));
  addid(prim_slot,
	new CgenNode(class_(prim_slot,No_class,nil_Features(),filename),
			    Basic,this));

// 
// The Object class has no parent class. Its methods are
//        cool_abort() : Object    aborts the program
//        type_name() : Str        returns a string representation of class name
//        copy() : SELF_TYPE       returns a copy of the object
//
// There is no need for method bodies in the basic classes---these
// are already built in to the runtime system.
//
  install_class(
   new CgenNode(
    class_(Object, 
	   No_class,
	   append_Features(
           append_Features(
           single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
           single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
           single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	   filename),
    Basic,this));

// 
// The IO class inherits from Object. Its methods are
//        out_string(Str) : SELF_TYPE          writes a string to the output
//        out_int(Int) : SELF_TYPE               "    an int    "  "     "
//        in_string() : Str                    reads a string from the input
//        in_int() : Int                         "   an int     "  "     "
//
   install_class(
    new CgenNode(
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
	   filename),	    
    Basic,this));

//
// The Int class has no methods and only a single attribute, the
// "val" for the integer. 
//
   install_class(
    new CgenNode(
     class_(Int, 
	    Object,
            single_Features(attr(val, prim_slot, no_expr())),
	    filename),
     Basic,this));

//
// Bool also has only the "val" slot.
//
    install_class(
     new CgenNode(
      class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename),
      Basic,this));

//
// The class Str has a number of slots and operations:
//       val                                  ???
//       str_field                            the string itself
//       length() : Int                       length of the string
//       concat(arg: Str) : Str               string concatenation
//       substr(arg: Int, arg2: Int): Str     substring
//       
   install_class(
    new CgenNode(
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
	     filename),
        Basic,this));

}

// CgenClassTable::install_class
// CgenClassTable::install_classes
//
// install_classes enters a list of classes in the symbol table.
//
void CgenClassTable::install_class(CgenNodeP nd)
{
  Symbol name = nd->get_name();

  if (probe(name))
    {
      return;
    }

  // The class name is legal, so add it to the list of classes
  // and the symbol table.
  nds = new List<CgenNode>(nd,nds);
  addid(name,nd);
}

void CgenClassTable::install_classes(Classes cs)
{
  for(int i = cs->first(); cs->more(i); i = cs->next(i))
    install_class(new CgenNode(cs->nth(i),NotBasic,this));
}

//
// CgenClassTable::build_inheritance_tree
//
void CgenClassTable::build_inheritance_tree()
{
  for(List<CgenNode> *l = nds; l; l = l->tl())
      set_relations(l->hd());
}

//
// CgenClassTable::set_relations
//
// Takes a CgenNode and locates its, and its parent's, inheritance nodes
// via the class table.  Parent and child pointers are added as appropriate.
//
void CgenClassTable::set_relations(CgenNodeP nd)
{
  CgenNode *parent_node = probe(nd->get_parent());
  nd->set_parentnd(parent_node);
  parent_node->add_child(nd);
}

void CgenNode::add_child(CgenNodeP n)
{
  children = new List<CgenNode>(n,children);
}

void CgenNode::set_parentnd(CgenNodeP p)
{
  assert(parentnd == NULL);
  assert(p != NULL);
  parentnd = p;
}

void CgenClassTable::code_prototype_objects() {
  for(List<CgenNode> *l = nds; l; l = l->tl()) {
    CgenNodeP node = l->hd();
    str << WORD << "-1" << endl;
    str << node->get_name()->get_string() << PROTOBJ_SUFFIX << LABEL;
    str << WORD << node->classtag_ << endl;
    str << WORD << node->get_proto_obj_size() << endl;
    str << WORD << node->get_name()->get_string() << DISPTAB_SUFFIX << endl;
    node->code_default_values_rec(node->attributes_, str);
  }

  if (cgen_debug) {
    for(List<CgenNode> *l = nds; l; l = l->tl()) {
      CgenNodeP node = l->hd();
      printf("Class name: %s\n", node->name->get_string());
      vector<Symbol>& tmp = node->attributes_;
      for (int i = 0; i < (int)tmp.size(); i++) {
        printf("  Symbol %d name: %s\n", i, tmp[i]->get_string());
      }
      printf("\n");
    }
  }
}

bool compare_cgen_nodes (const CgenNodeP& first, const CgenNodeP& second) {
  return (first->classtag_ < second->classtag_);
}

// Generate code for class name table and obj table.
void CgenClassTable::code_class_table() {
  std::vector<CgenNodeP> sorted_nodes;
  for(List<CgenNode> *l = nds; l; l = l->tl()) {
    sorted_nodes.push_back(l->hd());
  }
  std::sort(sorted_nodes.begin(), sorted_nodes.end(), compare_cgen_nodes);
  
  str << CLASSNAMETAB  << LABEL;
  for(int i = 0; i < (int) sorted_nodes.size(); i++) {
    CgenNodeP node = sorted_nodes[i];
    str << WORD; 
    stringtable.lookup_string(node->get_name()->get_string())->code_ref(str);
    str << endl;
  }
  str << CLASSOBJTAB << LABEL;
  for(int i = 0; i < (int) sorted_nodes.size(); i++) {
    CgenNodeP node = sorted_nodes[i];
    str << WORD << node->get_name()->get_string() << PROTOBJ_SUFFIX << endl;
    str << WORD << node->get_name()->get_string() << CLASSINIT_SUFFIX << endl;
  }
}

void CgenClassTable::code_dispatch_table() {
  CgenNodeP node;
  node = lookup(idtable.lookup_string("Object"));
  vector<pair<Symbol, Symbol> > tmp_table;
  node->gen_dispatch_table_df(tmp_table, str);

  if (cgen_debug) {
    for(List<CgenNode> *l = nds; l; l = l->tl()) {
      CgenNodeP node = l->hd();
      printf("Class name: %s\n", node->name->get_string());
      vector<pair<Symbol, Symbol> >& tmp = node->internal_disp_;
      for (int i = 0; i < (int)tmp.size(); i++) {
        printf("  Method %d name: %s.%s\n", i,
               tmp[i].first->get_string(), tmp[i].second->get_string());
      }
      printf("\n");
    }
  }
}

void CgenClassTable::set_class_tag() {
  CgenNodeP node;
  node = lookup(idtable.lookup_string("Object"));
  node->classtag_ = 0;
  node = lookup(idtable.lookup_string("IO"));
  node->classtag_ = 1;
  node = lookup(idtable.lookup_string("String"));
  node->classtag_ = stringclasstag;
  node = lookup(idtable.lookup_string("Bool"));
  node->classtag_ = boolclasstag;
  node = lookup(idtable.lookup_string("Int"));
  node->classtag_ = intclasstag;

  // DFS from the root, do not set on basic classes.
  node = lookup(idtable.lookup_string("Object"));
  int tmp = 5;
  node->set_class_tag_df(tmp);

  if (cgen_debug) {
    for(List<CgenNode> *l = nds; l; l = l->tl()) {
      CgenNodeP node = l->hd();
      printf("Class name: %s, tag: %d, lb: %d\n", node->name->get_string(),
        node->classtag_,
        node->classtag_lb_);
    }
  }
}

void CgenClassTable::code_object_initializer() {
  for(List<CgenNode> *l = nds; l; l = l->tl()) {
    CgenNodeP node = l->hd();
    str << node->get_name()->get_string() << CLASSINIT_SUFFIX << LABEL;
    node->code_initialization(this, str);
  }
}

void CgenClassTable::code_method_def() {
  for(List<CgenNode> *l = nds; l; l = l->tl()) {
    CgenNodeP node = l->hd();
    if (!node->basic()) {
      node->code_method(this, str);
    }
  }
}

void CgenClassTable::sort_cases(const vector<Case>& input, vector<Case>& output) {
  CgenNodeP node = lookup(idtable.lookup_string("Object"));
  node->visit_nodes_df(input, output);
  // reverse output
  std::reverse(output.begin(), output.end());
  if (cgen_debug) {
    for (int i = 0; i < (int)output.size(); i++) {
      Case tmp_case = output[i];
      Symbol type = tmp_case->get_type_decl();
      CgenNodeP tmp_node = lookup(type);
      if (tmp_node == NULL) { printf("error!\n"); exit(1); }
      printf("type ub: %d, lb: %d\n", tmp_node->classtag_, tmp_node->classtag_lb_);
    }
  }
}

void CgenClassTable::code()
{
  if (cgen_debug) cout << "coding global data" << endl;
  code_global_data();

  if (cgen_debug) cout << "choosing gc" << endl;
  code_select_gc();

  if (cgen_debug) cout << "coding constants" << endl;
  code_constants();

//                 Add your code to emit
//                   - prototype objects
//                   - class_nameTab
//                   - dispatch tables
//
  
  set_class_tag();
  code_class_table();
  code_dispatch_table();
  code_prototype_objects();

  if (cgen_debug) cout << "coding global text" << endl;
  code_global_text();

//                 Add your code to emit
//                   - object initializer
//                   - the class methods
  code_object_initializer();
  code_method_def();
}


CgenNodeP CgenClassTable::root()
{
   return probe(Object);
}

bool Environment::is_attribute(Symbol s) {
/*
  if (stack_.lookup(s) == NULL) {
    if (heap_.lookup(s) != NULL) {
      return true;
    } else {
      printf("This should not happen!\n");
      exit(-1);
    }
  } else {
    return false;
  }
*/

  if (heap_.lookup(s) != NULL) {
    // The variable is in heap, so it is a attribute by default.
    // If it also in stack, mark this as not attribute.
    // If it is not in stack, mark it as attribute.
    if (stack_.lookup(s) != NULL) {
      return false;
    } else {
      return true;
    }
  } else {
    // The variable is not in heap, so it must in stack, if it is not in stack, exit.
    if (stack_.lookup(s) != NULL) {
      return false;
    } else {
      printf("This should not happen!\n");
      exit(-1);
    }
  }
}

int Environment::get_offset(Symbol s) {
  if (is_attribute(s)) {
    return *(heap_.lookup(s));
  } else {
    return *(stack_.lookup(s));
  }
}

void Environment::addid_attribute(Symbol s, int* v) {
  heap_.addid(s, v);
}

void Environment::addid_argument(Symbol s, int* v) {
  stack_.addid(s, v);
}

void Environment::enter_let(Symbol s) {
  let_offset = let_offset - 1;
  stack_.enterscope();
  stack_.addid(s, new int(let_offset));
}

void Environment::exit_let() {
  stack_.exitscope();
  let_offset = let_offset + 1;
}

///////////////////////////////////////////////////////////////////////
//
// CgenNode methods
//
///////////////////////////////////////////////////////////////////////

CgenNode::CgenNode(Class_ nd, Basicness bstatus, CgenClassTableP ct) :
   class__class((const class__class &) *nd),
   parentnd(NULL),
   children(NULL),
   basic_status(bstatus)
{ 
   stringtable.add_string(name->get_string());          // Add class name to string table
}

int CgenNode::get_proto_obj_size() {
  if (strcmp(get_name()->get_string(), "Object") == 0) {
    return DEFAULT_OBJFIELDS;
  }
  return get_attributes_count() + parentnd->get_proto_obj_size();
}

void CgenNode::gen_dispatch_table_df(vector<pair<Symbol, Symbol> > disp, ostream& os) {
  internal_disp_ = disp;
  gen_dispatch_table(internal_disp_);
  os << name << DISPTAB_SUFFIX << LABEL;
  for (int i = 0; i < (int) internal_disp_.size(); i++) {
    pair<Symbol, Symbol>& tmp_entry = internal_disp_[i];
    os << WORD << tmp_entry.first << "." << tmp_entry.second << endl;
  }
  for (List<CgenNode>* l = children; l; l = l->tl()) {
    l->hd()->gen_dispatch_table_df(internal_disp_, os);
  }
}

void CgenNode::code_initialization(CgenClassTableP ct, ostream& os) {
  // For object, just return.
  if (strcmp(name->get_string(), "Object") == 0) {
    emit_return(os);
    return;
  }

  // Set the current node.
  ct->current_node_ = this;

  emit_method_start(os);

  // call parent initializer.
  os << JAL;
  emit_init_ref(parent, os);
  os << endl;

  // Build the environment for the current initializer.
  EnvironmentP e = new Environment();
  for (int i = 0; i < (int)attributes_.size(); i++) {
    e->addid_attribute(attributes_[i], new int(i+3));
  }

  for (int i = features->first(); features->more(i); i = features->next(i)) {
    features->nth(i)->code_initialization(ct, e, os);
  }

  emit_move(ACC, SELF, os);
  emit_method_end(0, os);
}

void CgenNode::code_method(CgenClassTableP ct, ostream& os) {
  ct->current_node_ = this;

  // Initialize class attributes.
  EnvironmentP e;  
  // Generate code for the method.
  for (int i = features->first(); features->more(i); i = features->next(i)) {
    e = new Environment();
    for (int j = 0; j < (int)attributes_.size(); j++) {
      e->addid_attribute(attributes_[j], new int(j+3));
    }

    features->nth(i)->code_method(ct, e, os);
  }
}

int CgenNode::get_method_offset(Symbol method_name) {
  for (int i = 0; i < (int)internal_disp_.size(); i++) {
    pair<Symbol, Symbol>& entry = internal_disp_[i];
    if (entry.second == method_name) {
      return i;
    }
  }
  printf("Error: cannot find method.\n");
  exit(-1);
}

void CgenNode::visit_nodes_df(const vector<Case>& input, vector<Case>& output) {
  Symbol name = get_name();
  for (int i = 0; i < (int)input.size(); i++) {
    Case tmp_case = input[i];
    if (strcmp(tmp_case->get_type_decl()->get_string(), name->get_string()) == 0) {
      output.push_back(tmp_case);
    }
  }

  for (List<CgenNode>* l = children; l; l = l->tl()) {
    l->hd()->visit_nodes_df(input, output);
  }
}

/////////////////////////////////////////////////////////////////////
//
// Methods on AST nodes that are not code generation.
//
////////////////////////////////////////////////////////////////////

// Get attribute count.
int class__class::get_attributes_count() {
  int rtn = 0;
  for (int i = features->first(); features->more(i); i = features->next(i)) {
    if (features->nth(i)->is_attribute()) {
      rtn++;
    }
  }
  return rtn;
}

bool method_class::is_attribute() {
  return false;
}

bool attr_class::is_attribute() {
  return true;
}

// Generate dispatch table.
void class__class::gen_dispatch_table(vector<pair<Symbol, Symbol> >& mv) {
  for (int i = features->first(); features->more(i); i = features->next(i)) {
    features->nth(i)->gen_dispatch_table(name, mv);
  }
}

void method_class::gen_dispatch_table(Symbol class_name, vector<pair<Symbol, Symbol> >& mv) {
  for (int i = 0; i < (int) mv.size(); i++) {
    pair<Symbol, Symbol>& tmp_pair = mv[i];
    if (tmp_pair.second == name) {
      tmp_pair.first = class_name;
      return;
    }
  }
  mv.push_back(std::make_pair(class_name, name));
}

void attr_class::gen_dispatch_table(Symbol class_name, vector<pair<Symbol, Symbol> >& mv) {
}

// Code default values.
void class__class::code_default_values(vector<Symbol>& symbol_vector, ostream& os) {
  for (int i = features->first(); features->more(i); i = features->next(i)) {
    features->nth(i)->code_default_values(symbol_vector, os);
  }
}

void method_class::code_default_values(vector<Symbol>& symbol_vector, ostream& os) {
}

void attr_class::code_default_values(vector<Symbol>& symbol_vector, ostream& os) {
  symbol_vector.push_back(name);
  if (strcmp(type_decl->get_string(), "String") == 0) {
    os << WORD;
    stringtable.lookup_string("")->code_ref(os);
    os << endl;
  } else if (strcmp(type_decl->get_string(), "Int") == 0) {
    os << WORD;
    inttable.lookup_string("0")->code_ref(os);
    os << endl;
  } else if (strcmp(type_decl->get_string(), "Bool") == 0) {
    os << WORD;
    falsebool.code_ref(os);
    os << endl;
  } else {
    os << WORD << EMPTYSLOT << endl;
  }
}


void method_class::code_initialization(CgenClassTableP ct, EnvironmentP e, ostream& os) {
}

void attr_class::code_initialization(CgenClassTableP ct, EnvironmentP e, ostream& os) {
  if (init->is_no_expr()) {
    return;
  }
  init->code(ct, e, os);

  // The variables here to assign are always attributes.
  int attribute_offset = e->get_offset(name);
  emit_store(ACC, attribute_offset, SELF, os);
}

// Code method.
void method_class::code_method(CgenClassTableP ct, EnvironmentP e, ostream& os) {
  os << ct->current_node_->name->get_string() << METHOD_SEP << name->get_string() << LABEL;
  
  int arg_size = formals->len();
  for (int i = 0; i < arg_size; i++) {
    Formal f = formals->nth(i);
    e->addid_argument(f->get_name(), new int(arg_size - 1 - i + 3));
  }
  emit_method_start(os);
  expr->code(ct, e, os);
  emit_method_end(arg_size, os);
}

void attr_class::code_method(CgenClassTableP ct, EnvironmentP e, ostream& os) {
}

//******************************************************************
//
//   Fill in the following methods to produce code for the
//   appropriate expression.  You may add or remove parameters
//   as you wish, but if you do, remember to change the parameters
//   of the declarations in `cool-tree.h'  Sample code for
//   constant integers, strings, and booleans are provided.
//
//*****************************************************************

void assign_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  // Generate code for the expression, the result should be in $a0.
  expr->code(ct, e, s);

  // Assign value in $a0 to the address of id.
  if (e->is_attribute(name)) {
    int offset = e->get_offset(name);
    emit_store(ACC, offset, SELF, s);
  } else {
    int offset = e->get_offset(name);
    emit_store(ACC, offset, FP, s);
  }
}

void static_dispatch_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  // Evaluate the arguments with current environment.
  int number_of_args = actual->len();
  emit_addiu(SP, SP, - number_of_args * 4, s);
  for (int i = 0; i < number_of_args; i++) {
    actual->nth(i)->code(ct, e, s);
    emit_store(ACC, number_of_args - i, SP, s);
  }

  // Evaluate the expression.
  // The result is the calling object in $a0
  expr->code(ct, e, s);

  int label_continue = ct->get_label();
  emit_bne(ACC, ZERO, label_continue, s);

  // ACC equals to zero, abort
  // First, load a0 with file name
  emit_load_string(ACC,
    stringtable.lookup_string(ct->current_node_->get_filename()->get_string()),
    s);
  emit_load_imm(T1, 1 /* line number */, s);
  emit_jal("_dispatch_abort", s);

  emit_label_def(label_continue, s);

  Symbol disp_type = type_name;
  
  // load dispatch table to t1
  s << LA << T1 << " " << disp_type->get_string() << PROTOBJ_SUFFIX << endl;
  emit_load(T1, DISPTABLE_OFFSET, T1, s);

  if (cgen_debug) {
    printf("Dispatch expression has type %s\n", disp_type->get_string());
    printf("Dispatch method name: %s\n", name->get_string());
  }
  // load the function to call to t1
  CgenNodeP disp_node = ct->lookup(disp_type);
  if (disp_node == NULL) {
    printf("Wrong type in dispatch.\n");
    exit(-1);
  }

  int method_offset = disp_node->get_method_offset(name);
  emit_load(T1, method_offset, T1, s);

  // Jump to method.
  emit_jalr(T1, s);
}

void dispatch_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  // Evaluate the arguments with current environment.
  int number_of_args = actual->len();
  emit_addiu(SP, SP, - number_of_args * 4, s);
  for (int i = 0; i < number_of_args; i++) {
    actual->nth(i)->code(ct, e, s);
    emit_store(ACC, number_of_args - i, SP, s);
  }

  // Evaluate the expression.
  // The result is the calling object in $a0
  Symbol disp_type = expr->get_type();
  if (strcmp(disp_type->get_string(), "SELF_TYPE") == 0 ) {
    disp_type = ct->current_node_->get_name();
  }
  expr->code(ct, e, s);

  int label_continue = ct->get_label();
  emit_bne(ACC, ZERO, label_continue, s);

  // ACC equals to zero, abort
  // First, load a0 with file name
  emit_load_string(ACC,
    stringtable.lookup_string(ct->current_node_->get_filename()->get_string()),
    s);
  emit_load_imm(T1, 1 /* line number */, s);
  emit_jal("_dispatch_abort", s);

  emit_label_def(label_continue, s);

  // load dispatch table to t1
  emit_load(T1, DISPTABLE_OFFSET, ACC, s);

  if (cgen_debug) {
    printf("Dispatch expression has type %s\n", disp_type->get_string());
    printf("Dispatch method name: %s\n", name->get_string());
  }
  // load the function to call to t1
  CgenNodeP disp_node = ct->lookup(disp_type);
  if (disp_node == NULL) {
    printf("Wrong type in dispatch.\n");
    exit(-1);
  }

  int method_offset = disp_node->get_method_offset(name);
  emit_load(T1, method_offset, T1, s);

  // Jump to method.
  emit_jalr(T1, s);
}

void cond_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  pred->code(ct, e, s);
  emit_fetch_int(T1, ACC, s);

  int label_false = ct->get_label();
  int label_end = ct->get_label();

  emit_beqz(T1, label_false, s);
  // True branch.
  then_exp->code(ct, e, s);
  emit_branch(label_end, s);
  
  // False branch.
  emit_label_def(label_false, s);
  else_exp->code(ct, e, s);

  // End.
  emit_label_def(label_end, s);
}

void loop_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  int loop_start = ct->get_label();
  int loop_end = ct->get_label();

  emit_label_def(loop_start, s);
  pred->code(ct, e, s);
  emit_fetch_int(T1, ACC, s);
  emit_beqz(T1, loop_end, s);
  body->code(ct, e, s);
  emit_branch(loop_start, s);

  emit_label_def(loop_end, s);

  // Loop always return void.
  emit_move(ACC, ZERO, s);
}

void typcase_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  vector<Case> input;
  vector<Case> output;
  for (int i = cases->first(); cases->more(i); i = cases->next(i)) {
    Case c = cases->nth(i);
    input.push_back(c);
  }
  ct->sort_cases(input, output);
  
  int case_start = ct->get_label();
  int case_end = ct->get_label();
  vector<int> case_labels;
  for (int i = 0; i < (int)output.size(); i++) {
    case_labels.push_back(ct->get_label());
  }

  expr->code(ct, e, s);
  emit_bne(ACC, ZERO, case_start, s);
  // The expression evaluates to void.
  emit_load_string(ACC,
    stringtable.lookup_string(ct->current_node_->get_filename()->get_string()),
    s);
  emit_load_imm(T1, 1 /* line number */, s);
  emit_jal("_case_abort2", s);

  emit_label_def(case_start, s);
  emit_load(T1, 0, ACC, s);

  int branches = cases->len();
  for (int i = 0; i < branches; i++) {
    Case tmp_case = output[i];
    Symbol tmp_type = tmp_case->get_type_decl();
    CgenNodeP node = ct->lookup(tmp_type);
    int ub = node->classtag_;
    int lb = node->classtag_lb_;
    emit_bgti(T1, lb, case_labels[i], s);
    emit_blti(T1, ub, case_labels[i], s);
    tmp_case->code(ct, e, s);
    emit_branch(case_end, s);
    emit_label_def(case_labels[i], s);
  }
  // Handle the case that no case match.
  // ACC is not changed, it contains the expr value.
  emit_jal("_case_abort", s);
  emit_label_def(case_end, s);
}

void block_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  for (int i = body->first(); body->more(i); i = body->next(i)) {
    Expression expr = body->nth(i);
    expr->code(ct, e, s);
  }
}

void let_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  if (init->is_no_expr()) {
    // The variable should be initialized to its default value.
    //s << LA << ACC << " " << type_decl->get_string() << PROTOBJ_SUFFIX << endl;
    //emit_jal("Object.copy", s);

    // Or we should make un-initialized id to null?
    // Note this is not a varialbe-> it can points to different objects, and the
    // underlying object may change, but we should make it clear that the symbol
    // here is an id.
    if (strcmp(type_decl->get_string(), "String") == 0
        || strcmp(type_decl->get_string(), "Int") == 0
        || strcmp(type_decl->get_string(), "Bool") == 0) {
      s << LA << ACC << " " << type_decl->get_string() << PROTOBJ_SUFFIX << endl;
      emit_jal("Object.copy", s);
    } else {
      emit_move(ACC, ZERO, s);
    }
  } else {
    init->code(ct, e, s);
  }
  emit_push(ACC, s);

  // Get the offset
  e->enter_let(identifier);
  body->code(ct, e, s);
  e->exit_let();

  // Pop the previous pushed value.
  // The value is no longer used, store in a dummy register.
  emit_pop(T1, s);
}

void plus_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  // The result is of type int, create the result object, push it to stack.
  emit_load_address(ACC, "Int_protObj", s);
  emit_jal("Object.copy", s);
  emit_push(ACC, s);
  
  // Create an object to hold the int value, store in register s2.
  
  e1->code(ct, e, s);
  emit_push(ACC, s);
  e2->code(ct, e, s);
  emit_pop(T1, s);

  // Now $a0 and $t1 contains the object address, we need to get the 
  // int value.
  emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
  emit_load(ACC, DEFAULT_OBJFIELDS, ACC, s);
  
  emit_add(T1, T1, ACC, s);

  // Pop the result object to $t1.
  emit_pop(ACC, s);
  emit_store(T1, DEFAULT_OBJFIELDS, ACC, s);
}

void sub_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  // The result is of type int, create the result object, push it to stack.
  emit_load_address(ACC, "Int_protObj", s);
  emit_jal("Object.copy", s);
  emit_push(ACC, s);
  
  // Create an object to hold the int value, store in register s2.
  
  e1->code(ct, e, s);
  emit_push(ACC, s);
  e2->code(ct, e, s);
  emit_pop(T1, s);

  // Now $a0 and $t1 contains the object address, we need to get the 
  // int value.
  emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
  emit_load(ACC, DEFAULT_OBJFIELDS, ACC, s);
  
  emit_sub(T1, T1, ACC, s);

  // Pop the result object to $t1.
  emit_pop(ACC, s);
  emit_store(T1, DEFAULT_OBJFIELDS, ACC, s);
}

void mul_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  // The result is of type int, create the result object, push it to stack.
  emit_load_address(ACC, "Int_protObj", s);
  emit_jal("Object.copy", s);
  emit_push(ACC, s);
  
  // Create an object to hold the int value, store in register s2.
  
  e1->code(ct, e, s);
  emit_push(ACC, s);
  e2->code(ct, e, s);
  emit_pop(T1, s);

  // Now $a0 and $t1 contains the object address, we need to get the 
  // int value.
  emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
  emit_load(ACC, DEFAULT_OBJFIELDS, ACC, s);
  
  emit_mul(T1, T1, ACC, s);

  // Pop the result object to $t1.
  emit_pop(ACC, s);
  emit_store(T1, DEFAULT_OBJFIELDS, ACC, s);
}

void divide_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  // The result is of type int, create the result object, push it to stack.
  emit_load_address(ACC, "Int_protObj", s);
  emit_jal("Object.copy", s);
  emit_push(ACC, s);
  
  // Create an object to hold the int value, store in register s2.
  
  e1->code(ct, e, s);
  emit_push(ACC, s);
  e2->code(ct, e, s);
  emit_pop(T1, s);

  // Now $a0 and $t1 contains the object address, we need to get the 
  // int value.
  emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
  emit_load(ACC, DEFAULT_OBJFIELDS, ACC, s);
  
  emit_div(T1, T1, ACC, s);

  // Pop the result object to $t1.
  emit_pop(ACC, s);
  emit_store(T1, DEFAULT_OBJFIELDS, ACC, s);
}

void neg_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  // Evaluate current expression, the result is in ACC.
  e1->code(ct, e, s);

  // Copy the value to a temp place.
  emit_jal("Object.copy", s);
  
  emit_load(T1, DEFAULT_OBJFIELDS, ACC, s);
  
  emit_neg(T1, T1, s);

  emit_store(T1, DEFAULT_OBJFIELDS, ACC, s);
}

void lt_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  emit_load_address(ACC, "Bool_protObj", s);
  emit_jal("Object.copy", s);
  emit_push(ACC, s);

  e1->code(ct, e, s);
  emit_push(ACC, s);
  e2->code(ct, e, s);
  emit_pop(T1, s);

  emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
  emit_load(ACC, DEFAULT_OBJFIELDS, ACC, s);

  s << SLT << T1 << " " << T1 << " " << ACC << endl;

  emit_pop(ACC, s);
  emit_store_int(T1, ACC, s);
}

void eq_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  int end_label = ct->get_label();
  e1->code(ct, e, s);
  emit_push(ACC, s);
  e2->code(ct, e, s);
  // T2 and T1 contains the two object
  emit_move(T2, ACC, s);
  emit_pop(T1, s);
  
  // Load $a0 with true and $a1 with false.
  emit_load_bool(ACC, truebool, s);

  // TODO: reformat these lines.
  emit_beq(T1, T2, end_label,s);

  emit_load_bool(A1, falsebool, s);
  
  emit_jal("equality_test", s);
  emit_label_def(end_label, s);
}

void leq_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  emit_load_address(ACC, "Bool_protObj", s);
  emit_jal("Object.copy", s);
  emit_push(ACC, s);

  e1->code(ct, e, s);
  emit_push(ACC, s);
  e2->code(ct, e, s);
  emit_pop(T1, s);

  emit_load(T1, DEFAULT_OBJFIELDS, T1, s);
  emit_load(ACC, DEFAULT_OBJFIELDS, ACC, s);

  s << SLE << T1 << " " << T1 << " " << ACC << endl;

  emit_pop(ACC, s);
  emit_store_int(T1, ACC, s);
}

// complement, the not operation.
void comp_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  // Evaluate current expression, the result is in ACC.
  e1->code(ct, e, s);

  emit_jal("Object.copy", s);
  
  emit_fetch_int(T1, ACC, s);

  s << SEQ << T1 << " " << T1 << " " << ZERO << endl;

  emit_store_int(T1, ACC, s);
}

void int_const_class::code(CgenClassTableP ct, EnvironmentP e, ostream& s)  
{
  //
  // Need to be sure we have an IntEntry *, not an arbitrary Symbol
  //
  emit_load_int(ACC,inttable.lookup_string(token->get_string()),s);
}

void string_const_class::code(CgenClassTableP ct, EnvironmentP e, ostream& s)
{
  emit_load_string(ACC,stringtable.lookup_string(token->get_string()),s);
}

void bool_const_class::code(CgenClassTableP ct, EnvironmentP e, ostream& s)
{
  emit_load_bool(ACC, BoolConst(val), s);
}

void new__class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
/*
  Symbol new_type = type_name;
  if (strcmp(new_type->get_string(), "SELF_TYPE") == 0 ) {
    new_type = ct->current_node_->get_name();
  }

  // First, load the prototype of the class.
  s << LA << ACC << " " << new_type->get_string() << PROTOBJ_SUFFIX << endl;

  // Copy the default object, store the result in ACC.
  // The prototype object contains the default value for each field.
  emit_jal("Object.copy", s);

  // Call type initializer
  s << JAL << new_type->get_string() << CLASSINIT_SUFFIX << endl;
*/
 
  if (strcmp(type_name->get_string(), "SELF_TYPE") == 0 ) {
    emit_load(T1, 0, SELF, s);
  } else {
    int current_class_tag = ct->lookup(type_name)->classtag_;
    emit_load_imm(T1, current_class_tag, s);
  }

  emit_sll(T1, T1, 3, s);
  emit_load_address(T2, "class_objTab", s);
  // T1 contains the memory address of the address of class proto object.
  // Loads T1 to ACC, so ACC will contain the address of the class proto object.
  emit_add(T1, T1, T2, s);
  emit_push(T1, s);
  emit_load(ACC, 0, T1, s);
  // Now ACC stores the proto object.
  emit_jal("Object.copy", s);

  emit_pop(T1, s);
  emit_load(T2, 1, T1, s);
  emit_jalr(T2, s);
}

void isvoid_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  // a symbol is void if its content is all 0.
  e1->code(ct, e, s);

  // Equal to zero label.
  int label_isvoid = ct->get_label();
  // End label.
  int label_end = ct->get_label();

  emit_beqz(ACC, label_isvoid, s);
  // Should create a new bool result and put in ACC?
  // copy false bool, and branch to the end
  // Do no equal to zero branch.
  emit_load_bool(ACC, falsebool, s);
  emit_jal("Object.copy", s);
  emit_branch(label_end, s);

  // Equal to zero branch.
  emit_label_def(label_isvoid, s);
  emit_load_bool(ACC, truebool, s);
  emit_jal("Object.copy", s);

  emit_label_def(label_end, s);
}

void no_expr_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
}

void object_class::code(CgenClassTableP ct, EnvironmentP e, ostream &s) {
  if (strcmp(name->get_string(), "self") == 0) {
    emit_move(ACC, SELF, s);
    return;
  }
  if (e->is_attribute(name)) {
    int offset = e->get_offset(name);
    emit_load(ACC, offset, SELF, s);
  } else {
    // The attribute is an argument.
    int offset = e->get_offset(name);
    emit_load(ACC, offset, FP, s);
  }
}

void branch_class::code(CgenClassTableP ct, EnvironmentP e, ostream& s) {
  // Push the expr value to stack.
  emit_push(ACC, s);

  e->enter_let(name);
  expr->code(ct, e, s);
  e->exit_let();
  emit_pop(T1, s);
}
