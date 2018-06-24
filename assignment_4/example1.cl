(* Test basic method dispatches and class attribute reference. *)
class Main inherits IO {
  a : Int <- 101;
  b : Int <- 102;
  c : Int <- 103;
  d : Int <- a;
  s : String <- "abc\n";

  main():Int {{ 
    out_int((c + b + c + b + a - 503)*8/32);
    out_string("\nhello world\n");
    out_string(s);
    0;
  }};

};