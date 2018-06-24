(* verity is subtype behavior
1. a : Test <- new Test 
this is allowed, but when the code run this line, there will be a infinite loop.
2. a : SELF_TYPE <- self
this is ok, all other types returned by the right side will result in failure.
3. b : Test3 <- new Test4
this is ok.
4. c : Test4 <- new Test3
this is not ok
 *)
class Main inherits IO {
  main(): SELF_TYPE { self };
};


class Test3 inherits Object {
  a : SELF_TYPE <- self;
  b : Test3 <- new Test4;
};

class Test4 inherits Test3 {
  c : Test4 <- new Test3;
  
};

class Test5 inherits Test3 {
  d : Int <- { "str"; };
  e : SELF_TYPE <- new Test5;
};
