(* Demonstrate argument passing. Cool argument is passed by value: a new
   copy of the argument is made for every function call. *)
class Main inherits IO {
  main():Int {{
    let a :Int <- 3 in {inc(a); print_single(a); }; 
    0;
  }};

  inc(arg0:Int) : Int {{
    arg0 <- arg0 + 3;
    out_string("in inc: ");
    out_int(arg0);
    out_string("\n");
    0;
  }};

  print_single(arg0: Int) : Int {{
    out_int(arg0);
    out_string("\n");
    0;
  }};
};