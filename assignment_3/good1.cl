(* verify the initializer behavior *)
class Main inherits IO {
  main(): SELF_TYPE {{
    func();
    out_string("Hello, World.\n");
  }};
  a : Int <- b + 3;
  b : Int <- a + 3;
  c : Int <- c + 3;
  func(): Int {{
    out_string("a: ");
    out_int(a);
    out_string("\n");
    out_string("b: ");
    out_int(b);
    out_string("\n");
    out_string("c: ");
    out_int(c);
    out_string("\n");
    0;
  }};
};
