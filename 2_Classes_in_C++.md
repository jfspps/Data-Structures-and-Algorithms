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

   // default constructor (without arguments)
   Rectangle(){
     // no-args constructor need not be empty, for example, the following is valid
     std::cout << "Default constructor called" << std::endl;
   };

   //other public methods, including setters and getters for private member access

   //destructors are needed in C++ if objects reside in the heap
   ~Rectangle(); 
 };
```

Note that garbage collection of the stack is automated in C++. To avoid memory leaks pertaining to the heap, one must call a destructor.
Default constructors, through overloading, are available.

## Instantiation, members and constructors ##

Syntactically similar to Java, _data members_ (or just _members_) are accessed with the direct member selection operator (.). They constitute the
variables and methods, which can be private or public. Only the class' methods and friend functions (see later) can access private members.

Like Java, _constructors_ provide a more concise way of initialising members in addition to granting access to private members.
The syntax for constructor calls in C++ is more concise than it is in Java (recall that the `new` keyword initialises pointers to
data on the heap).

```cpp
Rectangle aRectangle;

// initialise public members directly (assumes length and lengthTwo are public) 
aRectangle.length = 10;
aRectangle.lengthTwo = 2;
aRectangle.CalculateArea();

// instantiate via the constructor (members are private or public)
Rectangle anotherRectangle(10,2);
```

Constructors are not strictly required and the compiler will provide a default no-args constructor if none is provided.
Note that by adding a constructor with or without arguments indicates to the compiler that it will __not__ provide a default no-args
constructor. This means that if a no-args constructor is needed (when at least one constructor is already defined), then one must be declared in the class.

Default constructors can initialise defaults for members and are used when building arrays of objects, for example. The method call to such a method is the same as the no-args constructor. As a result,
the compiler will not know which to call, the constructor with no-args or that with defaults. In this case, one could
replace the no-args constructor with the defaults constructor:

```cpp
   // default constructor (no arguments but with defaults)
   Rectangle(int length = 1, int lengthTwo = 1){
     std::cout << "Default constructor with defaults called" 
        << std::endl;
   };
```

Finally, one can use __initialisation lists__ in a defaults constructor to initialise members with identifiers that differ from member identifiers:

```cpp
   // default constructor (no arguments but with defaults set by 
   // initialisation lists)
   Rectangle(int l1 = 1, int l2 = 1):length(l1), lengthTwo(l2)
   {
     std::cout << "Default constructor with defaults called via an initialisation list" 
        << std::endl;
   };
```

Initialisation lists are needed in some cases when initialisating members of certain data types.

## Scope resolution and inline methods ##

Methods (class functions) can be:

+ declared in the class as a prototype and defined outside the class
+ defined in the class (resulting in an __inline__ method)

Methods declared in a class __and__ defined _outside_ the class body are qualified through scope resolution using `::`.
In Java, the resolution operator `::` is used to call (reference) methods on an object which is not an instance of the class.

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

The method `Init()` in C++ is equivalent to the `static{}` block in Java, allowing one to hide initialisation details from
an external class or external method.

Methods defined within the class are treated as inline methods. Such methods instruct the compiler to literally replace all
method call literals (outside the class body) with the body of the inline method.

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
};

// somewhere in main()
DoStuff anObject;
anObject.value = 'f';
anObject.getValue();
```

The call to getValue() is replaced with the body of getValue(), along with appropriate adjustments so that the function does
not need to be called.

This replacement occurs whenever getValue() is called. This has the advantage of reducing the the overhead of calling a function
but only works for very simple definitions because the
compiler can make the replacement. For more complicated methods (e.g. recursive methods) which are unlikely to be mapped by the
compiler, it is best define such methods outside the class and apply scope resolution.

It is also possible to treat class methods (defined in a class) as inline methods by preceding the function header with the
keyword __inline__:

```cpp
// note that all members are public
class DoStuff{
  public:
    char value;
    // defined outside the class...
    char getValue(void);
    int getNumber(void);
};

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

### Friend functions ###

Friend functions are functions which are not part of a class (that is, they are neither private nor public members) that are granted access to a class' private members.
Friend functions defined within a class are by default, inline. Friend function prototypes inside a class would need to be defined outside the class and would not be
treated as inline methods unless they are preceded with the _inline_ keyword.

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
  
  // check the indentation, this friend function is not a member;
  // for clarity, this prototype are placed outside of both 
  // private and public lists
  friend int RepeatCharacter(DoStuff object);
};

// compiler assumes this is not an inline method
int DoStuff::RepeatCharacter(DoStuff object)
{
  // CharToInt is hypothetical here but is sent the value to a private member
  return CharToIntobject(value);
}
```

Placing the method definition outside the class generally makes it clearer to see that the method exists (instead of hiding it in the class).

## The this pointer ##

Methods can be defined to operate on the instance directly without passing it as a parameter. To achieve this, one uses the `this` pointer
in the method definition. Since `this` is a pointer, then one can access its members with the indirect member operator (->) instead of using (*this).

```cpp
class DoStuff{
  public:
    int value;

    // implicitly inline
    int incrementValue()
    {
      return ++this->value;
    }

    int compareTo(DoStuff object){
      // this is a pointer but object is not
      return this->value >= object.value;
    }
};

// somewhere in main()
DoStuff example;
example.value = 8;
example.incrementValue();

// example.value is now 9
```

Indeed, all member functions come with `this` and is provided by the compiler. The above definition is not the only way to implement `compareTo()` but is arguably the simplest.

### Constant class instances ###

Objects or instances of a class can be treated as constants provided that the `this` pointer provided in all member functions that use `this` (note that not all member functions need to use `this` so to them this passage does not apply) are also marked constant. To make the `this` pointer
of a member function constant requires making the method constant! So overall, a constant object is assumed as long as the relevant member functions are also constant.

Since member functions can be (a) declared as prototypes in the class and defined outside the class or (b) defined in the class, wherever the method is declared or defined, it must apply the `const` keyword. The following
demonstrates both cases:

```cpp
class DemoClass 
{
  private:
    double someDouble;

  public:
    DemoClass(double sD = 1.1);

    // uses the this pointer
    double getDouble() const;

    // uses the this pointer
    double doubleDouble() const
    {
      return 2*(this->someDouble);
    }
}

double DemoClass::getDouble() const
{
  return this->someDouble();
}

DemoClass::DemoClass(double sD): someDouble(sD)
{
  std::cout << "DemoClass initialised" << std::endl;
}

int main(){
  DemoClass demo;

  double demoDouble = demo.getDouble();
}
```

## Pointers and references to objects ##

Passing by address is particularly useful with member access since some classes can get quite large.

```cpp
SomeClass example;

SomeClass* objectPtr = 0;
objectPtr = &example;

// dereference the object first before accessing the data member...
std::cout << objectPtr->someField << std::endl;
```

References can be assigned to objects using:

```cpp
SomeClass example;

SomeClass& objectRef = example;

// no need to dereference the object first; accessing the data member directly...
std::cout << objectRef.someField << std::endl;
```

## The copy constructor ##

Copy constructors build objects by initialising data members from an existing object, hence a copy. Passing an object (to be copied) by value would result in an endless loop.
A copy constructor would need to build a copy of the object to pass as an argument and so the copy constructor would need a copy constructor in order to proceed.

Copy constructors therefore must use a pass-by-reference argument of the object that it is copying. The reference to an existing object does not require a copy constructor call.

Generally, one passes a `const` reference to the object to ensure that the copy constructor cannot change the reference to the object (to be copied). Other new objects may also
want to apply the data members.

```cpp
// copy constructor prototype
SomeClass(const SomeClass& copyFromThis);

// the definition provided outside SomeClass
SomeClass::SomeClass(const SomeClass& initObj){
  // initialise the members of the newly created object 
  // according to those provided by initObj
}
```

## Templates in C++ ##

### Function templates ###

Function templates are particularly useful when function overloading becomes excessive, i.e. a function prototype is declared
one too many times.

There are two keywords one can use to define a function template: `class` and `typename`. The latter is considered more generic
while the former is used specifically for class templates (see next section). These keywords are interchangeable in this section.

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

Templates in C++ are equivalent to generic classes in Java. The instantiation of a template with chosen types through the
constructor causes other methods to follow the same type used.

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
