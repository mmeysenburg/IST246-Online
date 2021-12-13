## Module 1: C++ Introduction

Welcome to Module 1! In this module we will cover some introductory information about the C++ programming language, in preparation for working with data structures in the next module. 

### What we assume you know

In this course, we are operating on the assumption that you have taken our first two programming courses, *IST 145 Introduction to Programming and Problem-Solving*, using the Python programming language, and *IST 146 Programming and Problem-Solving II* using the Java programming language, or have equivalent experience. The remainder of this course assumes you have this Python and Java programming knowledge. 

In particular, you should be very comfortable with the following concepts:

- Data types (integers, floats, strings, etc.) and operations on them (mathematics, string operations, Boolean operations, logical relations, etc.)
- Selection (if and switch statements)
- Iteration (for and while loops)
- Linear data structures (arrays or lists)
- Basic Object-Oriented Programming concepts (classes, methods, fields)

In addition, you should have introductory knowledge of the following concepts:

- Intermediate Object-Oriented Programming concepts (inheritance, polymorphism, interfaces)
- Exception handling to create code that "fails gracefully"
- The divide and conquer problem-solving technique, and recursive programming 
- Characteristics and basic use of data structures such as lists, queues, stacks, sets, and maps

### What we assume you have

To build and execute the code samples and assignments in this course, you will need an ISO/IEC 14882-compliant C++ 11 compiler. In the course videos, we will use a Windows PC with an Ubuntu Windows Subsystem for Linux (WSL) environment enabled, and our IDE will be Visual Studio Code. You may use a similar environment. Another option is [replit](https://replit.com/), the online, browser-based IDE. 

You may wish to use a more fully-developed IDE such as Visual Studio on Windows, or xCode on MacOS. This will require you to create projects, configure the unit testing directories, and so on. You are on your own here!

You will also need to clone the course's git repository, which contains all of the source code we will be using. In a bash environment, you can do this by executing the following command:

```
git clone https://github.com/mmeysenburg/ist246
```

### Differences between Java and C++

**[For this section of the reading, refer to the sample code in the module01-Intro/1-AirlinePassenger directory of the course's git code repository]**

Since Java and C++ share a common ancestor (the C programming language), you will find that much of the basic syntax between the two languages is the same or at least very similar. The following programming constructs are the same or very nearly the same in C++ as they were in Java:

- Declaration and use of primitive variables
- Basic control structures: `if`, `switch`, `for`, `while`
- Block structure is indicated with `{ }` 
- Function / method syntax 

However, there are some differences between Java and C++ that we will encounter. Some of these differences are summarized below. 

#### Object-oriented programming differences

C++ supports object-oriented programming, but the use of classes and objects is not required in a C++ program. In Java, there must be at least one class, but not so in C++. In C++ programs, it is not unusual to have a mixture of object-oriented concepts and structured programming concepts. In this course, we will define each of our data structures as a class, while our main programs will not be object-oriented. 

C++ allows generic data structures, that is, data structures that can hold any type of data, through template classes. These are not classes in themselves, but instructions to the compiler on how to write a class, given a data type specified by the user of the template. Each of the data structures we examine in this course will be written as a template class. 

Java only supports inheritance from one superclass, but allows for something like multiple inheritance through interfaces. C++ supports true multiple inheritance. 

It is occasionally useful to allow certain functions or classes outside of a class we are designing to be able to directly access our class' private data and / or methods. C++ allows this via the `friend` keyword, which indicates that our class trusts the specified function or classes to responsibly access its private data. 

#### Separation of interface and implementation

When we write a class in Python or Java, all of the code related to the class is in the same syntactic unit. For example, a class representing an airline passenger in Java would likely be found in a file named `AirlinePassenger.java`, such as this:

```
public class AirlinePassenger {
    private String flightNumber;
    private String name;
    private String seat;
    private int mealPreferenceCode;
 
    public AirlinePassenger(String flightNumber, String name, String seat, 
        int mealPreferenceCode) {
        
        this.flightNumber = flightNumber;
        this.name = name;
        this.seat = seat;
        this.mealPreferenceCode = mealPreferenceCode;
    }
 
    // ... and more
}
```

C++ may have separate code files for the declaration and implementation of a class. So, for an airline passenger class, we might have the declaration of the class in a file named `AirlinePassenger.h`, like this:

```
#pragma once
 
#include <string> 
 
class AirlinePassenger {
private:
    std::string flightNumber;
    std::string name;
    std::string seat;
    int mealPreferenceCode;
 
public:
    AirlinePassenger(std::string fn, std::string n, std::string s, int mpc);
 
    // ... and more
};
```

(An aside: what's up with the `std::` prefix on the string class name? The two colons (`::`) represent the *scope resolution* operator in C++. Here, they mean that the string class belongs to the standard namespace. Namespaces in C++ are something like packages in Java. They help organize code into logical groupings, and help to reduce problems with multiply-defined names. There are ways to make use of the `std::` prefix unnecessary, but we will follow the practice of using this scope resolution operator throughout our code in the course.)

The implementation of the various methods in the class might be stored in a separate file, perhaps `AirlinePassenger.cpp`:

```
#include "AirlinePassenger.h"
 
AirlinePassenger::AirlinePassenger(std::string fn, std::string n, 
    std::string s, int mpc) : flightNumber(fn), name(n), seat(s), 
    mealPreferenceCode(mpc) {
 
}
 
// ... and more
```

In this course, we will place the declaration and implementation of each of our template data structures in its own header file, ending with a `.hpp` extension. Our main code will be placed in files ending with `.cpp` extensions. Code for non-templated, non-data-structure classes may be split into a `.h` file and a `.cpp` file. 

#### Pointers and references

In Java, every object is accessed via a reference, which is a variable that holds the address of the object's location in memory. Every object in Java is dynamically allocated, usually with the `new` keyword, and accessed through a reference variable. The fields and methods of the object are accessed via the dot operator, e.g., `list.size()` gets the number of elements in a `List` object named `list`. 

On the other hand, primitive data types in Java, such as integers, are stored in variables that contain the value of the variable itself. They are not allocated with `new`, i.e., they are statically allocated. 

In C++, things are more complicated. We may have statically-allocated, local variables that are objects, rather than the addresses of objects. For example, consider this instance of airline passenger object:

```
AirlinePassenger ap("UAL1345", "Jane Smith", "32A", 1); 
```

The fields and methods of this object could be accessed via the dot operator, as in Java. So, if the class included a `setSeat()` method, we could change Jane's seat assignment with this method call:

```
ap.setSeat("1B");
```

If the proper function overloads have been written (a topic we will explore later in the course), we could print out the details of this passenger like this: 

```
std::cout << ap << std::endl;
```
 
(In C++, we can print to the console using the `std::cout` object, and the stream insertion operator, `<<`. The `std::endl` object represents an endline character. )

For this object, for example, we might see the following output:

```
Flight: UAL1345
Passenger: Jane Smith
Seat: 1B
Meal preference code: 1
```

C++ has two ways to refer to primitives or objects via their addresses: *pointers* and *references*. Pointers are variables that hold the addresses of elements in memory, and they are used extensively in dynamic memory allocation. A dynamically-allocated instance of an airline passenger might be created like this:

```
AirlinePassenger *pAp = new AirlinePassenger("SWA5462", "James Johnson", "25C", 2);
```
 
The asterisk in this usage indicates that the variable `pAp` is a pointer. Our naming convention will put a prefix of 'p' at the front of pointer variable names, although this is not required. Via a pointer, the fields and methods of an object are accessed via the arrow operator, ->, like this:

```
pAp->setSeat("25C");
```

To output this object via the pointer, we need to *dereference* it via another use of the asterisk, like this:

```
std::cout << *pAp << std::endl;
```
 
This time, we might see output like this:

```
Flight: SWA5462
Passenger: James Johnson
Seat: 25A
Meal preference code: 2
```

C++ references are *aliases*, i.e., additional names, for existing objects, and they work more or less like references in Java do. For example, this code

```
AirlinePassenger &apr = ap;
```
 
creates the reference `apr`, which is another name for the object named `ap`. The `&` symbol in the declaration indicates that this is a reference, rather than a statically-allocated airline passenger object. Via references, object fields and methods are accessed via the dot operator, such as:

```
apr.setSeat("13D");
```
 
Note that, since `ap` and `apr` are both names for the same object, printing either `ap` or `apr` would result in the same output:

```
Flight: UAL1345
Passenger: Jane Smith
Seat: 13D
Meal preference code: 1
```

We will frequently use references in pass-by-reference parameter passing, to prevent unnecessary copying of large objects when a method is called. 

#### Memory management

A MAJOR difference between C++ and Python or Java is that In C++ we must do our own memory management. Python and Java have runtime environments that periodically run garbage collectors to clean up objects created with the `new` keyword that are no longer in use. Not so with C++.

In C++, we must put away our own toys. When we are done with an object, we need to tell the computer's operating system that the object's memory may be reused for another purpose. If we fail to do this, we eventually will have a large amount of the computer's memory erroneously marked as "in use," leading to programs that run slowly or crash entirely. This is called a *memory leak*. 

A good rule of thumb is that we must have a `delete` for every `new` called in our program. For example, when we are done with the James Johnson airline passenger we allocated above with the `new` keyword, we should free the memory used by the object, like this:

```
delete pAp;
```

#### Programming safely

**[For this section of the reading, refer to the sample code in the module01-Intro/2-BadThings directory of the course's git code repository]**

Java was designed from the outset to be able to detect runtime errors and recover from them to keep running, or "fail gracefully," by providing specific details on exactly what went wrong. C++, generally speaking, will do what you tell it to, even if what you tell it to do is a really bad idea. This will be manifest in two ways in this course.

First, C++ does not automatically check array bounds. To illustrate this, let's consider this short Java program. It creates an array of integers, then intentionally tries to write to an array element that does not exist, i.e., it tries to change some memory that is not part of the array. The problematic code is in the second for loop: `i <= 100000`.

```
import java.util.Random;
 
public class ArrayBounds {
    public static void main(String[] args) {
        // random number generator
        Random prng = new Random();
 
        // make an array with 100000 elements, fill with 1's
        int[] arr = new int[100000];
        for(int i = 0; i < 100000; i++) {
            arr[i] = 1;
        }
 
        // overwrite the array values
        for(int i = 0; i <= 100000; i++) {
            arr[i] = prng.nextInt();
 
            // every so often report how we're doing
            if(i % 10000 == 0) {
                System.out.println("Overwriting element " + i);
            }
        }
    }
}
```

The output of the program is:

```
Overwriting element 0
Overwriting element 10000
Overwriting element 20000
Overwriting element 30000
Overwriting element 40000
Overwriting element 50000
Overwriting element 60000
Overwriting element 70000
Overwriting element 80000
Overwriting element 90000
Exception in thread "main" java.lang.ArrayIndexOutOfBoundsException: 100000
        at ArrayBounds.main(ArrayBounds.java:16)
```

As soon as the program tries to write to array element 100000 -- one past the end of the array -- the Java runtime stops the program, and it reports what went wrong (`java.lang.ArrayIndexOutOfBoundsException`) and where the problem happened (line 16). A maintenance programmer could use that information to go directly to the point where the error occurred. 

Now consider a similar program in C++:

```
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
 
int main() {
    // random number generator 
    std::mt19937 prng(time(0));
    std::uniform_int_distribution<int> dist(0, RAND_MAX);
 
    // make an array with 100000 elements, fill with 1's
    int *pArr = new int[100000];
    for(int i = 0; i < 100000; i++) {
        pArr[i] = 1;
    }
 
    // overwrite the array values
    for(int i = 0; i <= 100000; i++) {
        pArr[i] = dist(prng);
 
        // every so often report how we're doing
        if(i % 10000 == 0) {
            std::cout << "Overwriting element " << i << std::endl;
        }
    }
 
    // free memory used by the array
    delete [] pArr;
 
    return EXIT_SUCCESS;
}
```

The output of this code is:

```
Overwriting element 0
Overwriting element 10000
Overwriting element 20000
Overwriting element 30000
Overwriting element 40000
Overwriting element 50000
Overwriting element 60000
Overwriting element 70000
Overwriting element 80000
Overwriting element 90000
Overwriting element 100000
```

Notice the difference here! The error does NOT cause the program to crash, and thus we have no idea that something bad has occurred. But we know for sure that the program wrote over a location it should not have! The specific behavior will vary depending on the platform and compiler used to build the executable, but the end lesson is the same: C++ will let you read/write past the end of an array, and may not tell you when this error happens. 

Second, C++ will allow parameter mismatches much more readily than other languages. Consider this sample Java program:

```
public class ParamCheck {
    private static void foo(int x) {
        System.out.println("Foo says: You sent me: " + x);
    }
 
    public static void main(String[] args) {
        foo(13);
        foo(13.13);
    }
}
```

If we try to compile this code, we get a syntax error message, similar to this:

```
ParamCheck.java:8: error: incompatible types: possible lossy conversion from double to int
        foo(13.13);
```

What about a similar C++ program?

```
#include <cstdlib>
#include <iostream>
 
void foo(int x) {
    std::cout << "Foo says: You sent me: " << x << std::endl;
}
 
int main() {
    foo(13);
    foo(13.13);
 
    return EXIT_SUCCESS;
}
```

Compiling this program works just fine - no errors, no warnings. Worse, when we execute the program, we get this output:

```
Foo says: You sent me: 13
Foo says: You sent me: 13
```

The program silently converts the double value 13.13 into an integer value, 13, and executes the function. So, when writing C++ code, we need to have extra vigilance about the types of our variables and parameters, to make sure that they match (or at least that any automatic conversions that the program makes are acceptable). 

### More C++ details 

Now that we've looked at some of the key differences between C++ and Java, let's add some more detail to our understanding of C++. First, we examine the primitive types available in the language.

#### Primitive types and constants

**\[For this section of the reading, refer to the sample code in the module01-Intro/3-Primitives directory of the course's git code repository\]**

The primitive types available in C++ are similar to those in Java, with some notable exceptions. This table summarizes C++ primitives -- as they are on our Windows 10 / WSL setup at the moment this material is being written. 

| Data type | Keyword | Comments |
| ----------- | ----------- | ----------- |
| Character | `char` | 8-bit ASCII characters |
| Integer | `short`, `int`, `long` | 16-, 32-, or 64-bit signed integers |
| Unsigned integer | `unsigned short`, `unsigned` or `unsigned int`, `unsigned long` | 16-, 32-, or 64-bit unsigned integers |
| Floating point | `float`, `double`, `long double` | 32-, 64-, or 128-bit floating point numbers |
| Boolean | `bool` | `true` or `false` |


Perhaps the most obvious difference between C++ and Java primitives is that C++ provides unsigned versions of each of the integral data types. For example, the `int` primitive can hold values in the range \[-2,147,483,648, 2,147,483,647\], while the `unsigned` primitive holds values in the range \[0, 4,294,967,295\].

Secondly, unlike for Java, the sizes / ranges of primitives are not guaranteed to be consistent across platforms. In other words, it is possible that the size of an `int` -- the number of bits used -- is different across separate computer / operating system platforms. For example, a `long` on a PC running Windows 10 is a 64-bit integer, while in legacy code for old Windows systems or for a microcontroller, a `long` might be only 32 bits long. 

#### Pointers and arrays

**\[For this section of the reading, refer to the sample code in the module01-Intro/4-Arrays directory of the course's git code repository\]**

We mentioned above that C++ supports pointers and references, both of which are in some ways similar to reference variables in Java. Pointers are crucial to programming in C++, especially when we work with data structures, which allocate their memory dynamically. 

Like a reference variable in Java, a pointer is a variable that contains the address of something else in memory. In C++, pointers can refer to individual primitive values, arrays of values or objects, or to individual objects. 

We will use three operators with pointers:

- the asterisk (`*`) is used in the declaration of a pointer variable and when we dereference a pointer, i.e., when we get the value the pointer variable refers to. In this course, we will frequently use it to declare pointers, but only occasionally to dereference a pointer
- the ampersand (`&`) is used to declare a reference variable or parameter, but can also be used to find the address of something in memory. In this course, we will frequently use it to declare reference parameters
- the arrow (`->`) is also used for a kind of dereferencing, when the item at the end of the pointer is an object rather than a primitive value. We will use it frequently to access the fields and methods of dynamically-allocated objects. 

Arrays and pointers are closely related in C++. An array name is actually a pointer to the first array element (element 0). So, we often pass arrays to functions as pointers, and we will also include the size of the array as a separate parameter, since C++ arrays are not objects, and thus have no length field or size() method. To illustrate, here is the signature for a method to sum the elements of an array in Java:

```
private static int sum(int[] arr) 
```

Here, the `int[]` indicates that we are passing a Java array of integers, named `arr`. We would typically pass an array to a similar C++ function like this: 

```
int sum(int* pArr, int n)
```

Here, `int*` indicates that the first parameter, `pArr`, is a pointer to an integer (the first integer in the array), and the second parameter is the size of the array. 

Similarly, there is different syntax when allocating dynamically-allocated arrays in Java and C++. In Java, we would do something like this:

```
int[] arr = new int[100000];
```

In C++, the result of the new operator is a pointer, so we would allocate the same array like this: 

```
int *pArr = new int[100000];
```

Then, since we have to manage memory ourselves in C++, when we are done with the array we should return the memory we have allocated:

```
delete [] pArr;
```

The square brackets indicate that the `pArr` pointer refers to an array, rather than a single dynamically allocated integer. 

#### Parameter passing

**\[For this section of the reading, refer to the sample code in the module01-Intro/5-Parameters directory of the course's git code repository\]**

To discuss parameter passing, it is helpful to use two terms: *formal parameter* and *actual parameter*. Consider this Java code:

```
public class Parameters {
 
    private static void bar(double d) {
        d = 13;
        System.out.println("in bar, d = " + d);
    }
 
    public static void main(String[] args) {
        double md = 0;
 
        System.out.println("before bar, md = " + md);
        bar(md);
        System.out.println("after bar, md = " + md);
    }
}
```

A formal parameter is the name used in a method signature to identify a parameter. In the code above, the formal parameter for the `bar()` method is `d`. An actual parameter is the value that is passed into the method. In the sample Java, the actual parameter is the value of `md`. 

In Java, all parameters are pass-by-value, which means that the formal parameter receives a copy of the actual parameter value. Consequently, any changes the method makes to the formal parameter have no effect on the actual parameter value, since the changes were made to a copy. If we run the preceding sample code, we see: 

```
before bar, md = 0.0
in bar, d = 13.0
after bar, md = 0.0
```

C++ allows both pass-by-value and pass-by-reference. In pass-by-reference, the formal parameter is an alias for the actual parameter, i.e., it is simply another name for the same object. Pass by value is the default. If we want a reference parameter, we preface the formal parameter with the ampersand, `&`. This example, a C++ program similar to the Java code above, shows how references parameters work:

```
#include <cstdlib>
#include <iostream>
 
void bar(double &d) {
    d = 13;
    std::cout << "in bar, d = " << d << std::endl;
}
 
int main() {
    double md = 0;
 
    std::cout << "before bar, md = " << md << std::endl;
    bar(md);
    std::cout << "after bar, md = " << md << std::endl;
 
    return EXIT_SUCCESS;
}
```

The `&` marks `d` as a reference parameter. When the code runs, the formal parameter `d` will be an alias for the actual parameter `md`, and so the change made in the `bar()` function will change the value of `md`:

```
before bar, md = 0
in bar, d = 13
after bar, md = 13
```

We will frequently use reference parameters to pass large objects, preventing unnecessary copying from the actual parameter to the formal parameter. We will also frequently preface reference parameters with the `const` keyword, like this:

```
void foo(const double &d)
```

With the formal reference parameter marked as `const`, we would get a syntax error if we attempted to place `d` on the left hand side of the assignment operator. 

#### Operator overloading

Like Python, but unlike Java, C++ allows us to overload operators as well as methods. This is going to be quite important as we deepen our understanding of data structures. We will frequently overload the stream insertion operator (`<<`) and the assignment operator (`=`) for our data structures. For example, in the `AirlinePassenger` C++ class we examined at the beginning of this reading, we overloaded stream insertion so that `AirlinePassenger` objects could be easily printed:

```
std::ostream& operator<<(std::ostream &out, const AirlinePassenger &ap) {
    out << "Flight: " << ap.flightNumber << std::endl;
    out << "Passenger: " << ap.name << std::endl;
    out << "Seat: " << ap.seat << std::endl;
    out << "Meal preference code: " << ap.mealPreferenceCode << std::endl;
    return out;
}
```
 
Operator overloading is very powerful, and we should avoid caution so that we do not make an operator mean something drastically different from its usual connotation. For example, we could make `+` mean multiplication, but that would be a bad idea in practice. 

#### C++ classes

**\[For this section of the reading, refer to the sample code in the module01-Intro/6-MonteCarlo directory of the course's git code repository\]**

To help introduce you to writing C++ classes, we will take a top-to-bottom tour of the `Coordinate.hpp` file, which is employed in this module's sample application. This file contains a templated class, representing a *(x, y)* coordinate on a plane. 

To prevent the classes we write from being defined more than one time, we place this *compiler directive* at the top of our class' `.hpp` file (`Coordinate.hpp`, line 1):

```
#pragma once
```

After that, we have more compiler directives to include other header files that contain definitions we will need. This is similar to the `import` statements in Python or Java. Here, we include the math library and our unit-testing definitions (`Coordinate.hpp`, line 3):

```
#include <cmath>
#include <doctest.h>
```

Line 10 of the code is the start of a Doxygen comment for the class. We will discuss Doxygen comments in the next section. 

Next, we have the beginning of our class declaration (`Coordinate.hpp`, line 17):

```
template <class T> class Coordinate
```

The `template` keyword means that this is a set of instructions on how to make a class, rather than an actual class itself. The part in angle brackets, `<class T>`, says that any particular class generated from this template will be parameterized with a datatype `T`. `T` will be the type used for each component in our *(x, y)* coordinate -- `float`, `double`, `long double`, etc. The template is used by the compiler to generate the appropriate version of a coordinate. For example, 

```
Coordinate<float> zeroF, dartF;
```

would create two coordinates using floats for *x* and *y*, while 

```
Coordinate<long double> zeroLD, dartLD;
```

would create two other coordinates using long doubles. 

Finally, the name of the class is specified with `class Coordinate`.

Rather than specifying access levels for each method and field, as in Java, in C++ we specify areas inside the class declaration to convey this information. We start a section of publicly-available methods with (`Coordinate.hpp`, line 18):

```
public:
```

Everything declared after this line will have public access, until we change with a different area access specifier. We can change back and forth between access specifiers as many times as we wish, and there is no particular order that must be followed. In this course, we will tend to have all of the public elements first in our class declaration, followed by all of the private elements. 

The next items of note are the default constructor (`Coordinate.hpp`, line 24):

```
Coordinate() : x(), y() { }
````
 
and the initializing constructor (`Coordinate.hpp`, line 34):

```
Coordinate(T inX, T inY) : x(inX), y(inY) { }
```
 
As is the case in Java, constructors have the same name as their class, and they have no return value. A difference in C++ is the *initialization list*, used to provide initial values to the fields of the class. In the default constructor, the initialization list `: x(), y()` sets the fields to the default values for whatever type the class is parameterized for -- typically 0 for numeric types. In the initializing constructor, the initialization list `: x(inX), y(inY)` gives the fields the values provided by the formal parameters. 

Next in both constructors is the empty body of the constructor - `{ }`. Since the initialization lists took care of providing field values, there is nothing else for the constructors to do, and so they have empty bodies. When we have small method bodies like this, we will place them inside the class declaration. Other, longer methods will be *declared* inside the class declaration, but *defined* after the class declaration. 

The next items in the class declaration are the mutators and accessors. These should be familiar to you from Java. The only difference is the use of `T` to indicate the type of the formal parameters and return values. If our coordinate was parameterized with `float`, `T` would be replaced by `float`. If we parameterized with `long double`, `T` would be replaced by `long double`. 

The last method declaration in the public section of the class is for a method to measure the distance between this coordinate and another (`Coordinate.hpp`, line 72):

```
T distanceTo(const Coordinate<T> &other) const;
```

Reading this declaration from left to right, we see that the method's return type is `T`, the type used for each part of a coordinate. The name of the method is `distanceTo`. The method takes one formal parameter, a constant reference `Coordinate<T>` object. The final `const` on the line means that this method will not change the values of any of the object's fields. Since this method will take more than one line to write, we end the line with a semicolon. The definition of the method will occur later in the file, after the end of the class declaration. 

Next, we switch to a private access specifier area (`Coordinate.hpp`, line 73):

```
private:
```

and then declare the two private fields for the class, `x` and `y`. 

The class declaration ends on line 83 with 

```
};
```

Note the semicolon! Unlike Java, class declarations in C++ must end with a semicolon. Forgetting the semicolon here will result in a syntax error when you try to compile your code. 

After the class declaration, we define any of the methods that were too long to include inside the declaration. Here, there is only one method to declare (`Coordinate.hpp`, line 92):

```
template <class T>
T Coordinate<T>::distanceTo(const Coordinate<T> &other) const {
    T dx = x - other.x;
    dx = dx * dx;
    T dy = y - other.y;
    dy = dy * dy;
    return sqrt(dx + dy);
}
```

Since the class is templated, and the `distanceTo()` method was not defined inside the class declaration, we begin the function with `template <class T>`. The next line from left to right: `T` is the return type of the function. `Coordinate<T>::` means that this function belongs to the templated coordinate class. The rest of the signature is the same as it was in the class declaration. The body of the method uses the Euclidean distance formula to compute the distance between this object and the `Coordinate` referenced by the formal parameter `other`. 

Some other aspects of using C++ classes as data structures, such as destructors, overloading required or beneficial operators, copy constructors, and friend functions, will be covered as we move forward in the course. 

### Doxygen comments

Python has docstrings, and Java has javadoc comments, as a way to not only add comments to code but also to automatically generate documentation that appears in our IDEs or as HTML reference pages. C++ does not have a standard facility for this, but there are several choices available to us to accomplish the same thing. In this course, we will use [Doxygen](https://www.doxygen.nl/index.html). We will write Doxygen comments in much the same way we did javadoc. For example, consider the following Doxygen comments for the `distanceTo()` method in the `Coordinate` class (`Coordinate.hpp`, line 64):

```
/**
 * @brief Euclidean distance method.
 * 
 * Calculate the Euclidean distance between this coordinate and another.
 * 
 * @param other Reference to the other coordinate to use.
 * @return Euclidean distance between this coordinate and the other.
 */
```

The `@brief` tag briefly describes the element. After a blank line in the comments, a more complete description is provided. As in javadoc, a `@param` tag is used to document each parameter, and `@return` is used to document the return type of the method. All of the data structures classes we develop through the course will be thoroughly documented with Doxygen comments. You can find the processes HTML documentation for all of the data structures in the `html` directory of the course git repository. 

### Unit tests

There are many different unit-testing frameworks for C++. For this course, we have chosen a simple, lightweight framework called [doctest](https://github.com/onqtam/doctest). The required header for using doctest is in the `doctest` directory of the course git repository, and the makefiles for each of our code samples configures the include path to find that directory. Each piece of code we want to write unit tests for should include the `doctest.h` file. 

One of the benefits of doctest is that we can place our unit tests in the same file that contains our source code. Our practice will be to have each doctest unit test placed directly after the method it tests. In the coordinate class, we only test the `distanceTo()` method, with the tests starting in line 102 of `Coordinate.h`:

```
TEST_CASE("testing Coordinate<T>::distanceTo") {
    Coordinate<float> f1, f2;
 
    // distance should be 0
    CHECK(f1.distanceTo(f2) == 0.0f);
 
    f1.setX(11.0f); f1.setY(11.0f);
    f2.setX(11.0f); f2.setY(11.0f);
    // distance should still be 0
    CHECK(f1.distanceTo(f2) == 0.0f);
 
    Coordinate<double> f3(0.7071068, 0.0d);
    Coordinate<double> f4(0.0d, 0.7071068);
    // distance should be 1 -- within floating point tolerance errors
    CHECK(f3.distanceTo(f4) == doctest::Approx(1.0));
 
    Coordinate<long double> f5(2.0L, 3.0L);
    Coordinate<long double> f6(-3.0L, -2.0L);
    // distance should be approx 7.071
    CHECK(f5.distanceTo(f6) == doctest::Approx(7.071));
}
```

In this unit test, we create a variety of `Coordinate` objects, parameterized with different floating point types, and then verify that the `distanceTo()` method returns the expected distance between points. 

If we build our code and execute the unit tests, like this,

```
make
./CoordinateTests
```

the unit tests will execute, and if our code does what it should, we see this output:

```
[doctest] doctest version is "2.4.6"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases: 1 | 1 passed | 0 failed | 0 skipped
[doctest] assertions: 4 | 4 passed | 0 failed |
[doctest] Status: SUCCESS!
```

### Running code in our environment

In a bash environment, we build our code with the `make` command. Navigate with `cd` to the directory containing the code you're interested in, then execute `make`. This will build the executable(s) for the code in that directory. If unit tests are used, the `make` command will build both the standard executable and the unit test executable. All of this is controlled by the contents of the makefile. 

Here are the contents of the makefile for the `MontePi` application:

```
all:    CoordinateTests MontePi
 
CoordinateTests:    CoordinateTests.cpp
    g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN CoordinateTests.cpp -o CoordinateTests
 
MontePi:    MontePi.cpp
    g++ -std=c++11 -Wall -O3 -I ../../doctest -DDOCTEST_CONFIG_DISABLE MontePi.cpp -o MontePi
 
clean:
    rm CoordinateTests MontePi
```
 
The makefile controls the construction of two executables: `CoordinateTests` (the unit tests for the coordinate class) and `MontePi` (an application for estimating the value of 𝛑 using a Monte Carlo simulation). Here are explanations of some of the bits in the makefile:

- `g++` is the name of the C++ compiler in our WSL environment
- `-std=c++11` tells the compiler to use the C++ 11 standard, which a relatively recent, and widely used version of the language
- `-Wall` tells the compiler to report all warnings, in addition to all syntax errors
- `-I ../../doctest` adds the doctest unit testing directory to the compiler's include path search
- `-DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN` configures doctest to create a standalone unit-testing program
- `-DDOCTEST_CONFIG_DISABLE` disables doctest, so our unit tests are not part of the "production" code
- `-o` sets the name of the output file for the executable
 
The `make` command used by itself causes both executables to be built. If we specify a target, e.g., `make MontePi`, only that target is built. `make clean` will remove the executable files. 

