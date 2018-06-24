(*
Test argument type check.
*)

class Main inherits IO {

  main() : SELF_TYPE {{
(*  
    out_int(t.d());
    out_string("\n");
    out_int(t.e());
    out_string("\n");
*)
    self;
  }};
};

class Test1 inherits Object {
  a : SELF_TYPE <- self;
  b() : Int { 1 };
  c() : SELF_TYPE { self };
  to_override(a : Int, b: String) : Int {3};
};

class Test2 inherits Test1 {
  b() : Int { 2 };
  d() : Int { a.b() };
  e() : Int { c().b() };
  f(p : Int, q : String, r : Object) : SELF_TYPE { self };
  run() : Int {{
    f(1, "good", new Test1);
    invalid_method();
    0;
  }};
  run_error() : Int {{
    f("good", 1, new Test1);
    0;
  }};
  to_override(a : Int, b: String) : String { "" };
  to_override(a : Int) : Int {3};
  to_override(a : String, b : String) : Int {3};

  check_rtn() : String { 3 };
};
