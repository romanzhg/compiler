(* Test if and isvoid and dispatch on void. *)
class Main inherits IO {
  a : A;
  main():Int {{ 
    if isvoid a then
      { out_string("a is void\n"); }
    else
      { out_string("a is not void\n");}
    fi;
    a.some_method();
    0;
  }};


};

class A {
  some_method() : Int {0};
};
