(* Test calling functions with arguments. *)
class Main inherits IO {
  main():Int {{ 
    print(3, 5);
    0;
  }};

  print(arg0 : Int, arg1 : Int): Int {{
    out_string("in print function\n");
    out_int(arg0 + arg1);
    out_string("\nend of print function\n");
    0;
  }};
};