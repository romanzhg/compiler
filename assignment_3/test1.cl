(* verity is subtype behavior *)
class Main inherits IO {
  main(): SELF_TYPE { self };
};

class Test0 inherits Object {
  a : Int <- { 1;};
};

class Test1 inherits Object {
  a : String <- { "str";};
};

class Test2 inherits Object {
  a : Int <- { 1; 2; 3; 4; "str";};
};

class Test3 inherits Object {
  a : SELF_TYPE <- new Test4;
};

class Test4 inherits Test3 {
  a : Test4 <- new Test4;

};

