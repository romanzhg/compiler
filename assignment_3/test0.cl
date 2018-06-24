(* verity is subtype behavior *)
class Main inherits IO {
  main(): SELF_TYPE { self };
};

class Test1 inherits Object {
  a : Test1 <- new Test2;
};

class Test2 inherits Test1 {
  b : Test2 <- new SELF_TYPE;
  c : Int <- 3;
  d : Test2 <- self;
  e : Bool <- not false;
  f : Bool <- not 3;
};

(*
class Test3 inherits Test2 {
  
};

class Test4 inherits Test3 {

};

class Test5 inherits Test4 {

};
*)
