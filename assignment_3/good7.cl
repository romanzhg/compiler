(*
Test self type with dispatch.
 *)

class Main inherits IO {
  t : Test2 <- new Test2;
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
};

class Test2 inherits Test1 {
  b() : Int { 2 };
  d() : Int { a.b() };
  e() : Int { c().b() };
};
