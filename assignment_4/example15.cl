(* Test the new operator. *)
class Main inherits IO {
  a : A;
  main():Int {{ 
    a <- new A;
    0;
  }};
};

class A {
  x : SELF_TYPE;
  function_init() : Object {{
    x <- new SELF_TYPE;
  }};
};
