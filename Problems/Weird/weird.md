#Weird
###Problem

In mathematics, weird numbers are natural numbers that are abundant but not semiperfect. In other words, a natural number N is a weird number if and only if:

Sum of its proper divisors (i.e. less than N ) is greater than the number.
No subset of its divisors sum to N.
For example, the set of proper divisors of 12 is { 1, 2, 3, 4, 6 } . The sum of these numbers exceed 12, however, 12 is not a weird number since 1 + 2 + 3 + 6 = 12.
However, 70 is a weird number since its proper divisors are {1, 2, 5, 7, 10, 14, 35} and no subset sums to 70 .

Write a program to determine if the given numbers are weird or not.

###Input

In the first line of input, the number of test cases C ( <= 200 ) is given. In each of the following C lines, a natural number N_i is given. All input numbers are greater than 1, and less than or equal to 500,000 .

###Output

Output will consist of C lines, each line containing either weird or not weird , denoting the weird-ness of the corresponding input.

###Example input
```
2
12
70
```
###Example output
```
not weird
weird
```