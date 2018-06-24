(*
Test semantic check on let.
*)

class Main inherits IO {
  main() : SELF_TYPE {{
    self;
  }};
};

class Test1 inherits Object {
  test1_method() : Int {{
    let x : Int <- 3 in x + 6;
  }};
};