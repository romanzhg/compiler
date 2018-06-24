(* Test static dispatch and dynamic dispatch. *)
class Main inherits IO {
  a : A <- new A;
  b : A <- new B;
  c : B <- new B;
  main():Int {{ 
    print(a.get0()); -- expect to get 101
    print(b.get0()); -- expect to get 102
    print(c.get0()); -- expect to get 102
    print(b@A.get0()); -- expect to get 101
    print(c@A.get0()); -- expect to get 101
    0;
  }};

  print(arg0 : Int): Int {{
    out_string("in print_single function\n");
    out_int(arg0);
    out_string("\nend of print_single function\n");
    0;
  }};
};

class A {
  get0() : Int { 101 };
};

class B inherits A {
  get0() : Int { 102 };
  get1() : Int { 103 };
};