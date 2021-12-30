# Essential C and C++ #

## Enumerations ##

Enumerations are indexed by integers by default but can be indexed with characters instead.

```cpp
 int main(){

  // of type int by default, MondayN = 0 etc.
  enum WeekDayNum {
   MondayN,
   TuesdayN,
   WednesdayN,
   ThursdayN,
   FridayN
  };

  // of type char, Monday = M
  enum WeekDay : char {
   Monday = 'M',
   Tuesday = 'T',
   Wednesday = 'W',
   Thursday = 'T',
   Friday = 'F'
  };


  WeekDay someWeekDay = Monday;
  WeekDayNum someWeekDayNum = MondayN;

  // use a more modern form of type-casting
  cout << "The current weekday set is: " << static_cast<char>(someWeekDay) << endl;
  cout << "The current weekday (num) set is: " << someWeekDayNum << endl;

  cout << "Pick a number between 0 and 4: " << endl;

  int customDay;
  cin >> customDay;

  while (customDay < 0 || customDay > 4){
   cout << "Please enter a value between 0 and 4, inclusive: " << endl;
   cin >> customDay;
  }

  if (someWeekDayNum == customDay){
   cout << "You picked the same day" << endl;
  } else
   cout << "You picked a different day" << endl;

  return 0;
 }
```

## Structures ##

These are collections of data types under one name

```cpp
  struct rectangle{
    int length;
    int breadth;
  };

 void main(){
  struct rectangle r; //places r in the stack
  r = {10, 5};  //initialises r
  
  r.length = 10;
  r.breadth = 20;
  
  printf('Area of rectangle is %d/n', r.length*r.breadth);
  
  //declaring an array of structs
  struct rectangle[5];

  rectangle[0].length = 30; //etc...
 }
 ```

## Pointers ##

Grant access to stack and heap resources, by address. Functions called are stored in the stack, along with their local variables

```cpp
//general form of decalring pointers is: type * identifier
 main(){
  int a = 10;
  int *p; //NULL pointer, assign ASAP
  p = &a; //pointer p references int a (both in the stack)
  
  int t = *p; //dereferences p then assigns the value (not the address)
 }
 ```

Note that C++ pointers to the left of the assignment operator are declarations (and initialisations) of pointers. Pointers to the right of the assignment operator are dereferencing right-hand variables.

### Storing data on the heap with pointers in C and C++ ###

In C, data is stored in the heap using `malloc()`. In C++, use the keyword `new`. Below is a comparison. In C:

```cpp
 #include<stdlib.c>
 int main(){
  int *p;
  malloc(5*sizeof(int)); //allocates space in the heap
  p = (int*)(malloc(5*sizeof(int));
 }
 ```

In C++:

```cpp
 p = new int[5];
```

### Pointer and Arrays ###

A pointer to an array can be expressed in the form:

```cpp
 // array of pointers to integers
 int *ptr[arraySize];

 // used for comparison:
 int someArray[arraySize];
```

In this case, `ptr` is an array of pointers to integers. In comparison, the literal `someArray` represents an array of integers.

The array name or literal is essentially a pointer to the first element. The expression `*ptr` refers to the _value_ of the first element of the array and is equivalent to `ptr[0]`. The expression `*(ptr + 1)` is equivalent to `ptr[1]` and all are examples of 'pointer arithmetic'.

This next example shows a little about pointer arithmetic and how to free arrays in heap.

```cpp
 #include <iostream>

 using std::cin;
 using std::cout;
 using std::endl;

 int main(){

  int arraySize = 5;

  // assign the int pointer to a new array of int, which resides in the heap;
  // note that both int declarations must match
  int *arrayOne = new int[arraySize];
  int*tempArray;

  // use this to mark the actual number of elements present
  int added = 0;

  int heapIndex = 0;
  int answer = 0;

  // assume that at least one value is entered
  while (true){
   cout << "Enter an non-zero integer value (enter 0 to quit): ";

   // using the int equivalent of the input would also work here
   cin >> answer;

   if (answer == 0 || answer == 0){
    cout << "Terminating input...";
    break;
   }

   added++;
   arrayOne[heapIndex++] = answer;
   // the array name is the same as a pointer pointing to the first element,
   // i.e. int someInt = *arrayOne is the same as int someInt = arrayOne[0]
   // then int someInt =*(arrayOne + 2) is the same as int someInt = arrayOne[2]
   // and hence *(arrayOne + 2) =*(arrayOne + 3) assigns the third element
   // value to the second

   // if the last element was assigned,
   if (heapIndex == arraySize){
    cout << "Increasing the array size..." << endl;

    arraySize += 5;
    cout << "New array size: " << arraySize << endl;

    tempArray = new int[arraySize];
    for (int j = 0; j < added; j++){
     tempArray[j] = arrayOne[j];
    }

    // remove the current arrayOne elements from the heap
    delete[] arrayOne;

    // pointers (unlike references) are mutable so reassign arrayOne
    arrayOne = tempArray;
    tempArray = 0;
   }
  }

  cout << "You entered a total of " << heapIndex << " value(s)" << endl;

  int sum = 0;
  bool groupDoneYet = false;
  int i = 0;

  // only process as many elements that were added
  for (; i < added; i++){
   groupDoneYet = false;
   cout << arrayOne[i] << " ";
   sum += arrayOne[i];

   if ((i + 1) % 5 == 0){
    cout << "sum: " << sum << " and average: " <<  
       static_cast<double>(sum/5) << endl;
    sum = 0;
    groupDoneYet = true;
   }
  }

  // handle the trailing elements
  if (!groupDoneYet)
   cout << "sum: " << sum << " and average: " <<
       static_cast<double>(sum/(i%5)) << endl;

  cout << "Clearing up..." << endl;

  // release all heap memory
  delete[] arrayOne;

  // remove the address
  arrayOne = 0;

  return 0;
 }
```

## References (C++ only) ##

References are aliases to variables, and not part of C. They do not create copies of variables they reference to in any function call (other than `main()`). Unlike pointers, __references are immutable__ and so must be assigned as an alias to one variable for the program's entire lifecycle.

Functions which handle the references do not reside in separate stack frames and instead are part of the `main()` stack frame.

```cpp
//general form i: type & identifier
 int main(){
  int a = 10;
  int &r = a;
 }
```

References do not need dereferencing and their identifier (i.e. `r`) automatically provides the value it points to. The address the reference points to is given by `&r`.

The address of `a` and `r` are the same, so any operations on `a` and `r`are the same. So `r++` is equivalent to `a++`. The tokens `&r` to the left of the assignment operator assign a reference `r` to some variable. Pointers can be assigned to the address held by references, e.g. structures:

```cpp
 struct rectangle *p = &r;
 (*p).length = 20; //* has higher precedence than .
```

Alternatively, one can use the indirect member operator, instead of (*p).

```cpp
 p->length = 20;
```

Tokens `&r` to the right of the assignment operator return the address the reference points to. All references MUST be initialised.

## Functions and parameter passing ##

Passing by value assigns a variable, local to the function, with the parameter. The variable passed as the parameter resides in a different part of memory. Only a copy of the variable is handled by the function: hence the original variable cannot be changed. To change a parameter passed as a variable, send its address in the form of a reference or a pointer.

### Passing pointers ###

From the given block (quite often `main()`), the address of parameter(s) can be sent to a function so as to allow the parameter values to change. The following function call passes the address of the variables `a` and `b`.

```cpp
 swap(&a, &b);
```

It is also possible to send pointers directly instead of addresses of variables.

```cpp
 swap(pointerA, pointerB);
```

The corresponding function prototype (or _declaration_, that is, the function signature: function return and parameter types, and, the function name), one then needs to have formal parameters as pointers, for example:

```cpp
 void swap(int *x, int *y);
```

The above definition expects pointers, which are then referred to as `x` and `y` in the `swap()`. The function body would then need to dereference `x` and `y` (using `*x` and `*y`) in order to access the values of `a` and `b`.

### The main() method ###

The `main()` method can have arguments defined which end up representing command-line parameters.

```cpp
 int main(int argc, char* argv[]){
  // do stuff...
 }
```

The first argument `argc` represents the number of arguments and the second argument `argv` is an array of pointers to characters. The latter equivalent to an array of pointers to strings, since each character pointer points to the first character of the string. The first element of `argv` is always the program name and so `argc` is always at least 1.

### Passing by reference (C++ only) ###

Instead of passing by value or pointer, one can use references to the values and pass references.

```cpp
 swap(int &x, int &y);
```

The above call assigns x and y as references to the function-local parameters `a` and `b`. Thus, the function call `swap(a, b)` can change the values of the actual-parameters. This provides an alternative to the pointer approach above. The function prototype would take the form of:

```cpp
 void swap(int &x, int &y);
```

### Passing arrays ###

Recall that arrays can be thought of as pointers to the first element of an array. The type of the array and number of elements present indicates how much storage space is required.

Passing arrays is equivalent to passing pointers.

```cpp
 fun(int A[], int n);
```

The above call is equivalent to the following but not specific for arrays:

```cpp
 fun(int *A, int n);
```

The function prototype would be something like:

```cpp
 void fun(int someArray[], int someInt);
```

### Passing read-only addresses ###

It is possible to force the compiler to prevent the function from editing the address of variable by using the `const` keyword in the function prototype:

```cpp
 void swap(const int &x, int &y);
```

In this case, the reference corresponding to x cannot be changed, however, that corresponding to y can.

### Passing structures ###

One can pass structures as values, references and pointers. Here is an example of a function definition involving references and pointers to structures. Both approaches allow one to change the actual-parameter passed.

```cpp
 int area(struct Rectangle &z){
  z.length++;
  return z.length * z.breadth;
 }


 int area2(struct Rectangle *p){
  (p*).length++;
  return p->length* p->breadth;
 }
```

## Static variables ##

The keyword `static` declares variables (as well as objects and functions) which are initialised once (all subsequent initialisations are ignored) and retain their value for the duration of the function call, including `main()`.

## A note on returning pointers and references ##

In all cases, do not return the address (by pointer or reference) of local variables to the function. This is because the local variable is freed once the function termiantes and so the pointer or reference will be pointing to an undefined region of memory. Instead, build a new pointer to the local variable in the heap with `new` and return the pointer.

The first snippet will not work but the second will:

```cpp
 double*someFunc(double data){
  double someData = 3*data;
  return &someData;
 }

 double*someFunc2(double data){
  double* something = new double(3*data);
  return something;
 }
```

Returning references is also similarly fraught with errors. Additionally, avoid the mistake of returning pointers when references are called for:

```cpp
 double& someFunc3(double someArray[]){
  // do stuff...
  return someArray[2];
 }
```

Here the function is defined such that it returns a reference to the third element of `someArray`.  Note that using `&someArray[2]` would return the address (pointer) of the result, which is not an alias to the result.

Overall, `someArray[]` was initialised before `someFunc3` was called.
