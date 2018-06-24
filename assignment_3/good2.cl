(* verify the inheritance behavior and the use of self type *)
class Counter {
  a : Int <- 0;
  inc() : SELF_TYPE {{
    a <- a + 1;
    self;
  }};
  get_magic() : Int { 101 };
};

class Derived inherits Counter {
  b : Int <- get_magic();
  get_value(): Int { a };
  set_value(tmp : Int): SELF_TYPE { { a <- tmp; self; } }; 
  get_magic() : Int { 102 };
  get_b(): Int { b };
};

class Derived_ inherits Counter {
  b : SELF_TYPE <- get_self();
  c : Derived_ <- inc();
  d : SELF_TYPE <- inc();
  get_self(): SELF_TYPE { self };
  get_value(): Int { a };
};

class Main inherits IO {
  d : Derived <- new Derived;
  d_ : Derived_ <- new Derived_;
  main(): SELF_TYPE {{
    out_int(d.get_value());
    out_string("\n");
    out_int(d.set_value(8).get_value());
    out_string("\n");
    out_int(d.inc().get_value());
    out_string("\n");
    out_int(d.get_magic());
    out_string("\n");
    out_int(d@Counter.get_magic());
    out_string("\n");
    out_int(d.get_b());
    out_string("\n");
    out_string("Hello, World.\n");
    out_int(d_.get_self().get_magic());
    out_string("\n");
    out_int(d_.get_value());
    out_string("\n");
  }};
};
