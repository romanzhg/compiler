(* Test let. *)
class Main inherits IO {
  main():Int {{ 
    let a : Int <- 3 in print(a);
    let a : Int <- 5, b : Int <-8, c : Int <- 11 in print(a+b+c);
    let a : Int <- 5 in 
      { print(a);
        let a : Int <-8, b : Int <- 11 in {print(a); print(b);};
        print(a);};
    0;
  }};

  print(arg0 : Int): Int {{
    out_string("in print_single function\n");
    out_int(arg0);
    out_string("\nend of print_single function\n");
    0;
  }};
};
