(* Test argument passing and assign: the cool program creates
   a copy for each argument. *)
class Main inherits IO {
  a : Int <- 3;
  t : A <- new A;
  main():Int {{ 
    t.set(10);
    print_and_inc(t);
    print(t);
    0;
  }};

  print_and_inc(arg0 : A): Int {{
    out_string("in print and inc function\n");
    out_int(arg0.get());
    arg0.set(arg0.get() + 5);
    out_string("\n");
    out_int(arg0.get());
    arg0 <- new  A;
    arg0.set(100);
    out_string("\nend of print_and_inc function\n");
    0;
  }};

  print(arg0 : A): Int {{
    out_string("in print_single function\n");
    out_int(arg0.get());
    out_string("\nend of print_single function\n");
    0;
  }};
};

class A {
  v : Int;

  set(arg0 : Int) : Int {
    v <- arg0
  };

  get() : Int {
    v
  };

};