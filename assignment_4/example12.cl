(* Test case operator. *)
class Main inherits IO {
  a : A <- new B;
  b : Int <- 8;
  main() : Int {{ 

(*
    case b of
      b1 : String => 0;
      b2 : Object => 1;
      b3 : Int => 2;
    esac;
*)



    case b of
      b1 : String => {out_string(b1); out_string("\n");};
      b2 : Object => {out_string("matched object\n");};
      b3 : Int => {out_int(b3); out_string("\nmatched int\n");};
    esac;
(*
    case a of
      a0 : E => a0;

      a0 : E => out_string("a0\n");

      a1 : A => out_string("a1\n");
      a2 : B => out_string("a2\n");
      a3 : C => out_string("a3\n");
      a4 : D => out_string("a4\n");
      a5 : Object => out_string("a5\n");

    esac;
*)
    0;
  }};


};

class A {

};

class B inherits A{

};

class C inherits B{

};

class D inherits A{

};

class E inherits A{

};