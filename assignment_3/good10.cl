(*
Test semantic check on let.
*)

class Main inherits IO {
  main() : SELF_TYPE {{
    self;
  }};
};

class Test1 inherits Object {
  test1_method() : Int {{
    case 3 of 
      a : Int => 3;
      b : Object => "nice";
    esac;
    0;
  }};
};