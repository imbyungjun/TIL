#Function

[1. Anonymous function](#1-anonymous-function)

[2. Declarative function](#2-declarative-function)

[3. Arguments and return values](#3-arguments-and-return-values)

[4. Arguments](#4-arguments)

[5. Variable argument function](#5-variable-argument-function)

[6. Return values](#6-return-values)

[7. Inner function](#7-inner-function)

[8. Callback function](#8-callback-function)

[9. Function that returns function](#9-function-that-returns-function)

[10. 클로저](#10-클로저)

[11. Native functions in javascript](#11-native-functions-in-javascript)

###1. Anonymous function
**Anonymous function** doesn't have a name but, it is a function.

```
// Anonymous function
var func = function() { 	
	alert("Hello");
};

// We can see contents of the func
alert(func);

// It looks like string but, it is a function type variable
alert(typeof(func));

```

###2. Declarative function
**Declarative function** has a name. Usually declare function like this way.

```
// Decalre fucntion
function func() {
	alert("Hello");
}

// Call func() function
func();
```

\* Redeclaration of function

```
func();
function func() { alert("A"); }
function func() { alert("B"); }

var foo = function() { alert("A"); };
var foo = function() { alert("B"); };
foo();
```

\* Result

```
B
B
```
###3. Arguments and return values
Function can have arguments and a return value.

```
function func_name(arg1, arg2, arg3 ...) {
	...
	return ret_val;
}
```

###4. Arguments
JavaScript allows that more or less arguments than specified.

```
var arr1 = Array();
var arr2 = Array(10);
var arr3 = Array(273, 103, 57, 32);

alert(arr1 + '\n' + arr2 + '\n' + arr3);
```

\* Result

```

,,,,,,,,,
273, 103, 57, 32
```

\* **3 types of Array( )**

Form | Description
:----:|:-----:
Array( ) | Create empty array
Array(Number) | Creat array that has size of *Number*
Array(any, ..., any) | Create array with given arguments


###5. Variable argument function


###6. Return values

###7. Inner function

###8. Callback function

###9. Function that returns function

###10. 클로저

###11. Native functions in javascript

