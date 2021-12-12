# Essential C and C++ #

## Enumerations

Enumerations are indexed by integers by default but can be indexed with characters instead.

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

## Structures ##
These are collections of data types under one name

    struct rectangle{
    	int length;
    	int breadth;
    };

	void main(){
		struct rectangle r; //places r in the stack
		r = {10, 5};		//initialises r
		
		r.length = 10;
		r.breadth = 20;
		
		printf('Area of rectangle is %d/n', r.length*r.breadth);
		
		//declaring an array of structs
		struct rectangle[5];

		rectangle[0].length = 30; //etc...
	}
    
## Pointers ##
Grant access to stack and heap resources, by address. Functions called are stored in the stack, along with their local variables

    //general form of decalring pointers is: type * identifier
	main(){
		int a = 10;
		int *p;	//NULL pointer, assign ASAP
		p = &a; //pointer p references int a (both in the stack)
		
		int t = *p; //dereferences p then assigns the value (not the address)
	}

Note that C++ pointers to the left of the assignment operator are declarations (and initialisations) of pointers. Pointers to the right of the assignment operator are dereferencing right-hand variables.

In C, data is stored in the heap using `malloc()`. In C++, use the keyword `new`. Below is a comparison. In C:

    #include<stdlib.c>
	int main(){
	int *p;
	malloc(5*sizeof(int));	//allocates space in the heap
	p = (int*)(malloc(5*sizeof(int));
	}

In C++:

    p = new int[5];

This next example shows a little about pointer arithmetic and how to free arrays in heap.

	#include <iostream>

	using std::cin;
	using std::cout;
	using std::endl;

	int main(){

		int arraySize = 5;

		// assign the int pointer to a new array of int, which resides in the heap;
		// note that both int declarations must match
		int *arrayOne = new int[arraySize];
		int *tempArray;

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
			// then int someInt = *(arrayOne + 2) is the same as int someInt = arrayOne[2]
			// and hence *(arrayOne + 2) = *(arrayOne + 3) assigns the third element 
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

## References (C++ only) ##
References are aliases to variables, and not part of C. They do not create copies of variables they reference to in any function call (other than `main()`). Unlike pointers, __references are immutable__ and so must be assigned as an alias to one variable for the program's entire lifecycle.

Functions which handle the references do not reside in separate stack frames and instead are part of the `main()` stack frame.

    //general form i: type & identifier
	int main(){
		int a = 10;
		int &r = a;
	}

References do not need dereferencing and their identifier (i.e. `r`) automatically provides the value it points to. The address the reference points to is given by `&r`.

The address of `a` and `r` are the same, so any operations on `a` and `r `are the same. So `r++` is equivalent to `a++`. The tokens `&r` to the left of the assignment operator assign a reference `r` to some variable. Pointers can be assigned to the address held by references, e.g. structures:

    struct rectangle *p = &r;
	(*p).length = 20;	//* has higher precedence than .

Alternatively, one can use the indirect member operator, instead of (*p).

    p->length = 20;

Tokens `&r` to the right of the assignment operator return the address the reference points to. All references MUST be initialised.

## Functions and parameter passing ##
Passing by value assigns a variable, local to the function,  with the parameter. The actual-parameter cannot be changed. To change a parameter variable, pass by reference or by pointer.

### Passing and calling by addresses ###
From the given block (quite often `main()`), the address of parameter(s) can be sent to a function so as to allow the parameter values to change. The following function call passes the address of the variables `a` and `b`.

    swap(&a, &b);

Then, by the following function signature, one then needs to have formal parameters as pointers:

    swap(int *x, int *y);

The above definition expects references, which are then referred to as `x` and `y` in the `swap()`. The function body would then need to dereference `x` and `y` (using `*x` and `*y`) in order to access the values of `a` and `b`.

### Passing and calling by reference (C++ only) ###
Instead of passing by value, one can use references to the values and pass references.

    swap(int &x, int &y);

The above call assigns x and y as references to the actual-parameters `a` and `b`. Thus, the function call `swap(a, b)` can change the values of the actual-parameters. This provides an alternative to the pointer approach above.

### Passing arrays ###
Arrays can be thought of as pointers to the first element of an array. The type of the array and number of elements present indicates how much storage space is required.

Passing arrays is equivalent to passing pointers.

    fun(int A[], int n);

The above call is equivalent to the following but not specific for arrays:

    fun(int *A, int n);

### Passing structures ###
One can pass structures as values, references and pointers. Here is an example of a function definition involving references and pointers to structures. Both approaches allow one to change the actual-parameter passed.

    int area(struct Rectangle &z){
		z.length++;
		return z.length * z.breadth;
	}

    int area2(struct Rectangle *p){
		(p*).length++;
		return p->length * p->breadth;
	}

## Static variables ##

The keyword `static` declares variables (as well as objects and functions) which are initialised once (all subsequent initialisations are ignored) and retain their value for the duration of the function call, including `main()`.
