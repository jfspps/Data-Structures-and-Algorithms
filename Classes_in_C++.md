# Classes in C++ #
C++ and Java overlap a fair bit. Private and public instance variables and methods are bunched together in C++.

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

Note that garbage collection of the stack is automated in C++. To avoid memory leaks pertaining to the heap, one must call a destruictor. Default constructors, through overloading, are available.

## Scope resolution ##
Methods of a `class` body can be declared and defined outside the class body if they are qualified using `::`. In Java, the resolution operator `::` is used to call (reference) methods on an object which is not an instance of the class.

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

The method `Init()` in C++ is equivalent to the `static{}` block in Java, allowing one to hide initialisation details from an external class or external method.

## Templates in C++ ##
Templates in C++ are equivalent to generic classes in Java. The instantiation of a template with chosen types through the constructor causes other methods to follow the same type used.

    template<class T>	//this token is similar in function to @someProperty in Java
	class Arithmetic{
		private:
			T a;
			T b;
		
		public:
			Arithmetic(T a, T b);
			T add();
			T sub();
	}

	template<class T>	//needed again since } closed previous class block
	Arithmetic::Arithmetic(T a, T b){
		this.a = a;	//right-hand a is parameter value passed
		this->b = b;	//alternative notation
	}

	template<class T>
	T Arithmetic<T>::add(){
		T c;
		c = a + b;
		return c;
	}

