(* Test equal operator. *)
class Main inherits IO {
  a : Int <- 101;
  b_false : Bool <- false;
  b_true : Bool <- true;
  c : Int <- 102;
  d : String <- "hello";
  d_len_diff : String <- "hello ";
  e : String <- "world";
  f : String <- "hello";

  a_void : A;
  b_void : B;
  b_non_void : B <- new B;
  

  main() : Int {{ 
    print_bool(1 = 1);
    print_bool(a = a);
    print_bool(b_false = b_true);
    print_bool(a = c);
    print_bool(d = d);
    print_bool(d = d_len_diff);
    print_bool(d = e);
    print_bool(a = c);
    print_bool(a_void = b_void);
    --print_bool(a_void = b_non_void);
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

class A {

};

class B {

};