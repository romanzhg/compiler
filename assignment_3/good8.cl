(*
Test argument type check.
*)

class Main inherits IO {
  t : Test3 <- new Test3;
  main() : SELF_TYPE {{
(*
    (* Expect output 3. *)
    out_int(t.test1_method());
    out_string("\n");
    (* Expect output 3. *)
    out_int(t@Test2.test1_method());
    out_string("\n");
*)
    self;
  }};
};

class Test1 inherits Object {
  test1_method() : Int {3};
};

class Test2 inherits Test1 {
  test2_method() : Int {5};
};

class Test3 inherits Test2 {
  a : Test3 <- self;
  test3_method() : Int {7};
  method_call() : Int {{
    a.test1_method();
    a@Test2.test1_method();
  }};
};
