(*
Verify if child can access parent attributes.

notes: if we do
let v : Test2 in { out_int(v.get());};
we will get dispatch to void, since v is not initialized(v is an object not a primitive type).

 *)
class Main inherits IO {
  main(): SELF_TYPE {{ 
  let v : Test2 <- new Test2 in {
    out_int(v.get());
    out_string("\n");
    out_int(v@Test1.get());
    out_string("\n");
  };
  self;}};
};


class Test1 inherits Object {
  a : Int <- 2;
  get() : Int { a };
};

class Test2 inherits Test1 {
  b : Int <- 10;
  get() : Int { a + b };
};
