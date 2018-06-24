(* Test various operators. *)
class Main inherits IO {
  a : Int <- 101;
  b : Int <- 102;
  c : Int <- 103;
  d : Int <- a;
  e : Bool <- false;

  main():Int {{ 
    out_int((c + b + c + b + a - 503) * 8 / 32);
    out_string("\nhello world\n");
    out_int(~a);
    out_string("\nhello world\n");
    print_bool(e);
    print_bool(not e);
    print_bool(3 < 4);
    print_bool(100 < 100);
    print_bool(1000 < 100);
    print_bool(100 <= 100);
    print_bool(100 <= 1000);
    while 95 < a loop { a <- a - 1; out_string("in loop\n"); } pool;
    0;
  }};

  print_bool(a : Bool) : Int {{
    if a then
      out_string("input is true\n")
    else
      out_string("input is false\n")
    fi;
    0;
  }};

};