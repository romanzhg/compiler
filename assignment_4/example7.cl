(* Test new. *)
class Main inherits IO {
  a : A;
  main():Int {{ 
    a <- new A;
    a.set(101);
    print(a.get());
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
  v0 : Int;
  v1 : B;
  get() : Int {v0};
  set(arg0:Int) : Int {{ v0 <- arg0; 0; }};
};

class B {

};