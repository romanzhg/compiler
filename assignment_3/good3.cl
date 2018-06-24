(* verify attributes can be defined in both base and derived with the same type,
   and the inherited function behavior. *)
class Counter {
  a : Int <- 0;
  inc() : SELF_TYPE {{
    a <- a + 1;
    self;
  }};
  get_value(): Int { a };
};

class Derived inherits Counter {
  a : Int <- 100;
  get_value(): Int { a };
  set_value(tmp : Int): SELF_TYPE { { a <- tmp; self; } }; 
};


class Main inherits IO {
  d : Derived <- new Derived;

  main(): SELF_TYPE {{
    
    out_int(d.get_value());
    out_string("\n");

    out_int(d@Counter.get_value());
    out_string("\n");

    d.set_value(1000);

    out_int(d.get_value());
    out_string("\n");

    out_int(d@Counter.get_value());
    out_string("\n");

  }};
};
