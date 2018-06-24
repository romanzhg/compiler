(* Verify and test the behavior of method parameter checking *)
class Main inherits IO {
  main(): SELF_TYPE {{ self; }};
};


class Test1 inherits Object {
  func1(a : Int, self : String) : Int { 0 };
  func2(a : Int, b : SELF_TYPE) : Int { 0 };
};

class Test2 inherits Test1 {

};
