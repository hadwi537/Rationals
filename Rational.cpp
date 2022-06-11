#include "Rational.h"

namespace cosc326 {
	/**
	 * @brief Construct a new Rational:: Rational object
	 * 
	 * Default constructor
	 *  -- if zero, put both to zero
	 *  -- sign is kept on numerator
	 * 
	 */
	Rational::Rational() {
		numerator = Integer("0");
		denominator = Integer("0");
	}
	/**
	 * @brief Construct a new Rational:: Rational object
	 * 
	 * @param str to construct from
	 */
	Rational::Rational(const std::string& str) {
		size_t start;
		size_t end = 0;
		std::string nums[3] = {"", "", ""};
		const char delim = '/';
		size_t i = 0;

		while((start = str.find_first_not_of(delim, end)) != std::string::npos){
			end = str.find(delim, start); 
			nums[i] = str.substr(start, end - start);	
			i++;		
		}
		
		if (nums[0].find('.') != std::string::npos){
			size_t endWhole = nums[0].find(".");
			std::string wholeStr = nums[0].substr(0, endWhole);
			std::string num = nums[0].substr(endWhole+1, nums[0].size());
			denominator = Integer(nums[1]); 
			numerator = num + denominator * Integer(wholeStr).getNumber();
			numerator.setSign(Integer(wholeStr).getSign());
		} else if (nums[0] != "" && nums[1] != ""){
			numerator = Integer(nums[0]);
			denominator = Integer(nums[1]);
		} else {
			numerator = Integer(nums[0]);
			denominator = Integer("1");
		}
		// std::cout << "numerator: " << numerator << std::endl;
		// std::cout << "denomintaor: " << denominator << std::endl;
	}

	Rational::Rational(const Rational& r) {
		numerator = r.numerator;
		denominator = r.denominator;
	}

	Rational::Rational(const Integer& a) {
		numerator = a;
		denominator = Integer("1");
	}

	Rational::Rational(const Integer& a, const Integer& b) {
		numerator = a;
		denominator = b;
	}

	Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
		numerator = c*a + b;
		denominator = c;
	}

	Rational::~Rational() {

	}
	/**
	 * @brief Assignemnt operator
	 * 
	 * @param r 
	 * @return Rational& 
	 */
	Rational& Rational::operator=(const Rational& r) {
		(*this).denominator = r.getDenominator();
		(*this).numerator = r.getNumerator();
		return *this;
	}
	/**
	 * @brief Unary operator
	 * 
	 * @return Rational 
	 */
	Rational Rational::operator-() const {
		return Rational(*this).numerator*Integer("-1");
	}
	
	Rational Rational::operator+() const {
		if ((*this).numerator < Integer("0")){
			(*this).numerator *= Integer("-1");
		}
		return Rational(*this);
	}
	/**
	 * @brief += value
	 * 
	 * This performs basic fractional addition
	 * 
	 * @param r 
	 * @return Rational& 
	 */
	Rational& Rational::operator+=(const Rational& r) {
		numerator = ((numerator * r.getDenominator()) + (denominator*r.getNumerator()));
		denominator *= r.getDenominator();
		return *this;
	}

	/**
	 * @brief -=
	 * performs basic fractional subtraction
	 * 
	 * @param r 
	 * @return Rational& 
	 */
	Rational& Rational::operator-=(const Rational& r) {
		numerator = (numerator * r.getDenominator()) - (denominator*r.getNumerator());
		denominator *= r.getDenominator();
		return *this;
	}
	/**
	 * @brief *= 
	 * Uses basic fractioanl multiplicaiton
	 * 
	 * @param r 
	 * @return Rational& 
	 */
	Rational& Rational::operator*=(const Rational& r) {
		numerator = numerator * r.getNumerator();
		denominator = denominator * r.getDenominator();
		return *this;
	}
	
	/**
	 * @brief /
	 * a/b / c/d = (a * d)/(b*c)
	 * 
	 * @param r 
	 * @return Rational& 
	 */
	Rational& Rational::operator/=(const Rational& r) {
		numerator = numerator * r.getDenominator();
		denominator = denominator * r.getNumerator();
		return *this;
	}
	/**
	 * @brief addition
	 * 
	 * Uses += method for calculation
	 * 
	 * @param lhs 
	 * @param rhs 
	 * @return Rational 
	 */
	Rational operator+(const Rational& lhs, const Rational& rhs) {
		Rational result;
		result = lhs;
		result += rhs;
		return result;
	}

	Rational operator-(const Rational& lhs, const Rational& rhs) {
		Rational result;
		result = lhs;
		result -= rhs;
		return result;
	}

	Rational operator*(const Rational& lhs, const Rational& rhs) {
		Rational result;
		result = lhs;
		result *= rhs;
		return result;
	}

	Rational operator/(const Rational& lhs, const Rational& rhs) {
		Rational result;
		result = lhs;
		result /= rhs;
		return result;
	}

	/**
	 * @brief Output rational to stream
	 * Also simplifies the rational
	 * 
	 * @param os 
	 * @param i 
	 * @return std::ostream& 
	 */
	std::ostream& operator<<(std::ostream& os, const Rational& i) {
		i.simplify();
		std::string out; //string to store output
		Integer whole = i.getNumerator()/i.getDenominator();
		Integer tempNumerator = i.getNumerator() - whole*i.getDenominator();
		std::string stringNumer = tempNumerator.getNumber();
		std::string stringDenom = i.getDenominator().getNumber(); 

		out.append(i.getNumerator().getSign() ? "-" : "");
 		if (whole == Integer("0")){ // fractional number 0<=1
			if (i.getNumerator() == Integer("0")){
				os << out.append("0");
				return os;
			}
			os << out.append(stringNumer).append("/").append(stringDenom);
			return os;
		 }
		if (tempNumerator == Integer("0")){ //whole number
			os << out.append(whole.getNumber());
			return os;
		}

		//fractional |r| > 1
		out.append(whole.getNumber()).append(".").append(stringNumer).append("/").append(stringDenom);
		os << out;
		return os;
	}

	void Rational::simplify() const {
		//simplify rational
		// std::cout << "numerator: " << numerator << std::endl;
		// std::cout << "Denominator " << denominator << std::endl;
		Integer denom = gcd(numerator, denominator);
		// std::cout << "denom: " << denom << std::endl;
		denom.setSign(false); //always set denom to positive
		numerator /= denom;  
		denominator /= denom; 
		
		if (denominator.getSign()){ //i.e denominator negative
			if (numerator.getSign()){ //also negative
				numerator.setSign(false);
				denominator.setSign(false);
			} else {
				numerator.setSign(true);
				denominator.setSign(false);
			}
		}
		// std::cout << numerator << std::endl;
	}

	std::istream& operator>>(std::istream& is, Rational& i) {
		is >> i.numerator >> i.denominator;
		return is;
	}
	/**
	 * @brief less than operator
	 * 
	 * equate denominators by multiplying 
	 * either rational by the other divisor
	 * 
	 * Then simply compare the resulting numerators
	 * 
	 * @param lhs 
	 * @param rhs 
	 * @return true 
	 * @return false 
	 */
	bool operator<(const Rational& lhs, const Rational& rhs) {
		Rational lhVal = lhs;
		Rational rhVal = rhs;

		//equate denominators
		lhVal.numerator *= rhVal.denominator;
		rhVal.numerator *= lhVal.denominator;
		//so just compare numerators
		return (lhVal.numerator < rhVal.numerator);
		
	}

	bool operator> (const Rational& lhs, const Rational& rhs) {
		return !(lhs < rhs || rhs == lhs);
	}

	bool operator<=(const Rational& lhs, const Rational& rhs) {
		return (lhs < rhs || lhs == rhs);
	}

	bool operator>=(const Rational& lhs, const Rational& rhs) {
		return (lhs > rhs || lhs == rhs);
	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
		Rational lhVal = lhs;
		Rational rhVal = rhs;

		//equate denominators
		lhVal.setNumerator(lhVal.getNumerator() *= rhVal.getDenominator());
		rhVal.setNumerator(rhVal.getNumerator() *= lhVal.getDenominator());
		//so just compare numerators
		return ((lhVal.getNumerator() - rhVal.getNumerator()) == Integer("0"));
	}

	bool operator!=(const Rational& lhs, const Rational& rhs) {
		return !(lhs == rhs);
	}

	Integer Rational::getNumerator() const{
		return numerator;
	}
	void Rational::setNumerator(Integer i){
		numerator = i;
	}
	Integer Rational::getDenominator() const{
		return denominator;
	}
	void Rational::setDenominator(Integer i){
		denominator = i;
	}

}
