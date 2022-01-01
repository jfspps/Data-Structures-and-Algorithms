# Classes in C++ #

Structures do not feature concepts such as:

+ Encapsulation: combination (packaging) of members (fields) with methods that operate on members
+ Inheritance: how one class forms the basis of another, by inheriting the base classes members and methods
+ Polymorphism: how an object can exhibit different properties through the different method definitions (e.g. Java's `toString()`)

Classes address these limitations and extend the basic idea of C structures.

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

## Instantiation and data members ##

Syntactically similar to Java, data members (or just members) are accessed with the direct member selection operator (.).

```cpp
Rectangle aRectangle;

// initialise public members directly 
aRectangle.length = 10;
aRectangle.lengthTwo = 2;
aRectangle.CalculateArea();
```

## Scope resolution and inline methods ##

Methods can be:

+ declared in the class as a prototype and defined outside the class
+ defined in the class (resulting in an __inline__ method)

Methods declared in a class __and__ defined _outside_ the class body are qualified through scope resolution using `::`. In Java, the resolution operator `::` is used to call (reference) methods on an object which is not an instance of the class.

```cpp
Rectangle::Rectangle(int a, int b){
  length = a;
  breadth = b;
 }

 // emphasises that area() is a member function of the class Rectangle
 int Rectangle::area(){
 //some code for area()
 }
 
 Rectangle::~Rectangle(){};

 class Rectangle{
 //class instance variables and other methods
 }
```

The method `Init()` in C++ is equivalent to the `static{}` block in Java, allowing one to hide initialisation details from an external class or external method.

Methods defined within the class are treated as inline methods. Such methods instruct the compiler to literally replace all method call literals (outside the class body) with the body of the inline method.

```cpp
// mimic a Java getter
class DoStuff{
  private:
    char value;

  public:
    // implicitly inline
    char getValue()
    {
      return value;
    }
}

// somewhere in main()
DoStuff anObject;
anObject.value = 'f';
anObject.getValue();
```

The call to getValue() is replaced with the body of getValue(), along with appropriate adjustments so that the function is not called.

This replacement occurs whenever getValue() is called. This has the advantage of reducing the the overhead of calling a function but only works for very simple definitions because the
compiler can make the replacement. For more complicated methods (e.g. recursive methods) which are unlikely to be mapped by the compiler, it is best define such methods outside the class and apply scope resolution.

It is also possible to treat class methods (defined in a class) as inline methods by preceding the function header with the keyword __inline__:

```cpp
// note that all members are public
class DoStuff{
  public:
    char value;
    // defined outside the class...
    char getValue(void);
    int getNumber(void);
}

// somewhere outside of main(); treated as inline
inline char DoStuff::getValue(){
  return value;
}

// somewhere outside of main(); not treated as inline
int DoStuff::getNumber(){
  int Result = value;

  // perform more complex stuff...

  return intResult;
}

// somewhere in main() ------------------------------
DoStuff anObject;
anObject.value = 'f';
anObject.getValue();
anObject.getNumber;
```

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
