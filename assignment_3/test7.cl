class Main inherits IO {
  main(): SELF_TYPE {{ self; }};
};


class Test1 inherits Object {
  a : Int <- 2;
};

class Test2 inherits Test1 {
  a : Int <- 10;
};
