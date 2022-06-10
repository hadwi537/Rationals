Compile:
g++ -o main Integer.cpp Rational.cpp main.cpp

run:
./main


Implimentation Details:

Integer:
    Fields:
    * string to represent the number
    * boolean to represent the string

    Methods:
    * Getters and setters to modify Fields
    * add method that adds two strings using a loop over the two numbers
        * analogus subtract method
    * mutliply method (again a loop through the digits of the number)
    * Division: Essentially, it works by having a guess at the Quotient
    Based off the difference between the two numbers.
    It then iterates and moves in the correct direction as fast as possible

    # is smaller - determines if the numerical value of one string is smaller 
    * gcd - recusive gcd method

    General comments:
    * Once the above were defined, operaterations like +=, -= could then
    be defined in terms of the already implimented operaterations
    * This idea was used to build all the comparison operators from the " < " and "==" operator


Rational:
    Fields:
        * numerator (Integer)
        * denominator (Integer)

    Methods:
        * apart from getters and setters, nothing else was introduced
        as the basic arithemic operators could be easily calculed using
        fractional arithemic and the already implimented Intger class

    General comments:
        * The numerator and denominator and stored and only simplified using 
        the gcd of these numbers when the value is output in the "<<" stream 
        operator. The idea being that its faster overall just to do this once and not 
        after every operation.

Group Members:
William Hadden, John Marshall