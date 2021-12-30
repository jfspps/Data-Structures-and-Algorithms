# Classes in C++ #

C++ and Java overlap a fair bit. Private and public instance variables and methods are bunched together in C++.

```cpp
class Rectangle{
  private:
   int length;
   int breadth;

  public:
   Rectangle(int l, int b){
    length = l;
    breadth = b;
   }

   //other public methods, including setters and getters

   //destructors are needed in C++ if objects reside in the heap
   ~Rectangle(); 
 }
```

Note that garbage collection of the stack is automated in C++. To avoid memory leaks pertaining to the heap, one must call a destructor. Default constructors, through overloading, are available.

## Scope resolution ##

Methods of a `class` body can be declared and defined outside the class body if they are qualified using `::`. In Java, the resolution operator `::` is used to call (reference) methods on an object which is not an instance of the class.

```cpp
Rectangle::Rectangle(int a, int b){
  length = a;
  breadth = b;
 }

 int Rectangle::area(){
 //some code for area()
 }
 
 Rectangle::~Rectangle(){};

 class Rectangle{
 //class instance variables and other methods
 }
```

The method `Init()` in C++ is equivalent to the `static{}` block in Java, allowing one to hide initialisation details from an external class or external method.

## Templates in C++ ##

### Function templates ###

Function templates are particularly useful when function overloading becomes excessive, i.e. a function prototype is declared one too many times.

There are two keywords one can use to define a function template: `class` and `typename`. The latter is considered more generic while the former is used specifically for class templates (see next section). These keywords are interchangeable in this section.

```cpp
// assume here that an array of int's, double's or long's is involved...
template<typename T> 
T somePopularFunction(T generalArray[], int index, T generalQuantity)
{
  T localVar = generalArray[index];

  if (localVar > generalQuantity){

    // great, do other stuff...
    return localVar;

  } else {

    // not good, try something else...
    return generalQuantity;

  }
}

int main(){

  long valueLong = 12;
  long arrayLong[] = { 2,4,5 };

  double valueDouble = 4.5;
  double arrayDouble[] = { 3.3,4.4,5.5 };

  // the compiler will use the prototypes to decide function to call;
  // both long and double forms are instantiated at run-time, 
  // regardless if they are used or not
  long resultLong = somePopularFunction(arrayLong, 1, valueLong);

  double resultDouble = somePopularFunction(arrayDouble, 0, valueDouble);

  return 0;
}
```

### Class templates ###

Templates in C++ are equivalent to generic classes in Java. The instantiation of a template with chosen types through the constructor causes other methods to follow the same type used.

```cpp
template<class T>   // this token is similar in function to @someProperty annotation in Java
 class Arithmetic
 {
  private:
   T a;
   T b;
  
  public:
   Arithmetic(T a, T b);
   T add();
   T sub();
 }

 template<class T>   // needed again since } closed previous class block
 Arithmetic::Arithmetic(T a, T b)
 {
  this.a = a;        // right-hand a is parameter value passed
  this->b = b;       // alternative notation
 }

 // define a function template
 template<class T>
 T Arithmetic<T>::add()
 {
  T c;
  c = a + b;
  return c;
 }
```
