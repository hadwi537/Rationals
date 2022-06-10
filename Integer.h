
// Most compilers understand the once pragma, but just in case...
#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>

namespace cosc326 {

	class Integer {
		mutable std::string number;
		mutable bool sign; 
		
		public:

			Integer();                             // Integer i;
			Integer(const Integer& i);             // Integer j(i);
			Integer(const std::string& s);         // Integer k("123");

			~Integer();

			Integer& operator=(const Integer& i);  // j = i;

			// Unary operators
			Integer operator-() const;                   // -j;
			Integer operator+() const;                   // +j;

			// Arithmetic assignment operators
			Integer& operator+=(const Integer& i); // j += i;
			Integer& operator-=(const Integer& i); // j -= i;
			Integer& operator*=(const Integer& i); // j *= i;
			Integer& operator/=(const Integer& i); // j /= i;
			Integer& operator%=(const Integer& i); // j %= i;

			// lhs < rhs -- a 'friend' means operator isn't a member, but can access the private parts of the class.
			// You may need to make some other functions friends, but do so sparingly.
			friend bool operator<(const Integer& lhs, const Integer& rhs);

			//getters and setters
			std::string getNumber() const;
			void setNumber(std::string str);
			bool getSign() const;
			void setSign(bool s);

			//misc
			Integer absolute() const;
			std::string add(std::string number1, std::string number2) const;
			std::string subtract(std::string number1, std::string number2) const;
			std::string multiply(std::string number1, std::string number2) const;
			std::pair<Integer, Integer> divide (std::string numerator, std::string denominator) const;
			bool isSmaller(std::string str1, std::string str2) const;
			std::string reverse(std::string str) const;

			friend std::istream& operator>>(std::istream& is, Integer& i);        // std::cin >> i;
		

		private:
			
	};

	// Binary operators
	Integer operator+(const Integer& lhs, const Integer& rhs); // lhs + rhs;
	Integer operator-(const Integer& lhs, const Integer& rhs); // lhs - rhs;
	Integer operator*(const Integer& lhs, const Integer& rhs); // lhs * rhs;
	Integer operator/(const Integer& lhs, const Integer& rhs); // lhs / rhs;
	Integer operator%(const Integer& lhs, const Integer& rhs); // lhs % rhs;

	std::ostream& operator<<(std::ostream& os, const Integer& i);  // std::cout << i << std::endl;

	bool operator> (const Integer& lhs, const Integer& rhs); // lhs > rhs
	bool operator<=(const Integer& lhs, const Integer& rhs); // lhs <= rhs
	bool operator>=(const Integer& lhs, const Integer& rhs); // lhs >= rhs
	bool operator==(const Integer& lhs, const Integer& rhs); // lhs == rhs
	bool operator!=(const Integer& lhs, const Integer& rhs); // lhs != rhs

	Integer gcd(const Integer& a, const Integer& b);  // i = gcd(a, b);
}

#endif
