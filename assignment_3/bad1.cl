(* defined a class twice *)
class Main inherits IO {
   main(): SELF_TYPE {
	out_string("Hello, World.\n")
   };
};

class Main inherits Main {
   main(): SELF_TYPE {
	out_string("Hello, World.\n")
   };
};

class Test inherits Bool {

};

class Test1 inherits Test2 {

};

class Test2 inherits Test1 {

};
