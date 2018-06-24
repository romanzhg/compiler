(*
Test argument type check.
*)

class Main inherits IO {
  main() : SELF_TYPE {{
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
  f(p : Int, q : String, r : Object) : SELF_TYPE { self };
  run() : Int {{
    f(1, "good", new Test1);
    0;
  }};
};
