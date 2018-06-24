(* define attribute/method multiple times *)
class Main inherits IO {
   main(): SELF_TYPE {
	out_string("Hello, World.\n")
   };
};

class Test1 inherits Object {
  a : Int <- 123;
  a : Int <- 456;
};

class Test2 inherits Object {
  f(): Int {1};
  f(): Int {2};
};

class Test3 inherits Object {
  g(a : Int): Int {1};
  g(a : Int, b : Int): Int {2};
};
