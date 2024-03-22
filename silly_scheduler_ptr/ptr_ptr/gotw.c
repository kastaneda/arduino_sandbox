// http://www.gotw.ca/gotw/057.htm

//  Example 3(d): The correct solution
//
struct FuncPtr_;
typedef FuncPtr_ (*FuncPtr)();

struct FuncPtr_
{
  FuncPtr_( FuncPtr pp ) : p( pp ) { }
  operator FuncPtr() { return p; }
  FuncPtr p;
};

FuncPtr_ f() { return f; } // natural return syntax

int main()
{
  FuncPtr p = f();  // natural usage syntax
  p();
}

/*

gotw.c:4:19: error: expected declaration specifiers or ‘...’ before ‘*’ token
    4 | typedef FuncPtr_ (*FuncPtr)();
      |                   ^
gotw.c:8:3: error: expected specifier-qualifier-list before ‘FuncPtr_’
    8 |   FuncPtr_( FuncPtr pp ) : p( pp ) { }
      |   ^~~~~~~~
gotw.c:13:1: error: unknown type name ‘FuncPtr_’; use ‘struct’ keyword to refer to the type
   13 | FuncPtr_ f() { return f; } // natural return syntax
      | ^~~~~~~~
      | struct 
gotw.c: In function ‘f’:
gotw.c:13:23: warning: returning ‘int (*)()’ from a function with return type ‘int’ makes integer from pointer without a cast [-Wint-conversion]
   13 | FuncPtr_ f() { return f; } // natural return syntax
      |                       ^
gotw.c: In function ‘main’:
gotw.c:17:3: error: unknown type name ‘FuncPtr’
   17 |   FuncPtr p = f();  // natural usage syntax
      |   ^~~~~~~
gotw.c:18:3: error: called object ‘p’ is not a function or function pointer
   18 |   p();
      |   ^
gotw.c:17:11: note: declared here
   17 |   FuncPtr p = f();  // natural usage syntax

*/
