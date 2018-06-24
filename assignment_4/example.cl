
(*  Example cool program testing as many aspects of the code generator
    as possible.
 *)

class Main {
  main():Int { 0 };
  func(a : Int, b : Int, c : String): Int { a + b };
};

class A {

};

class B inherits A {

};

class C inherits B {

};

(*
class A {
  a : String <- "aaaaaaaaaaaaaaaaaaaaaaaa";
  b : String <- f();
  f() : String { "abc" };
};

class B inherits A {
  e : String;
};
*)