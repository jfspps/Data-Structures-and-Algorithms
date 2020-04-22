# Static and global variables #

Static variables are stored in the code section of memory. They are initialised once and once only. All subsequent initialisation which can be foundin recursive calls, are ignored. The static variable retains its value since the first initialisation or last expression.

```cpp
int fun(int n)
{
	static int x = 0;
	if (n > 0)
	{
		x++;
		return fun(n - 1) + x;
	}
}
```

Here, `fun()` changes x and does not re-assign it to zero. Removing the `static` keyword then leads the compiler to reset x to zero.

Global variables, declared outside of functions behave in the same way as static variables.