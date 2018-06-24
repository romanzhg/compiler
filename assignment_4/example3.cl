(* Test assign. *)
class Main inherits IO {
  a : Int <- 3;
  main():Int {{ 
    print(a);
    a <- 5;
    print(a);
    0;
  }};

  print(arg0 : Int): Int {{
    out_string("in print_single function\n");
    out_int(arg0);
    out_string("\nend of print_single function\n");
    0;
  }};
};
