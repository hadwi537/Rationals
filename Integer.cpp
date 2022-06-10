#include "Integer.h"

namespace cosc326 {
	/**
	 * @brief Construct a new Integer:: Integer object
	 * 
	 * positive = false
	 * negative = true
	 * 
	 */
	Integer::Integer() {
		number = "0";
		sign = false;
	}

	Integer::Integer(const Integer& i) {
		number = i.number;
		sign = i.sign;
	}

	Integer::Integer(const std::string& s) {
		if (isdigit(s[0])){
			number = s;
			sign = 0; //+
		} else {
			number = s.substr(1);
			sign = (s[0] == '-');
		}
	}

	Integer::~Integer() {
		
	}

	Integer& Integer::operator=(const Integer& i) {
		this->number = i.number;
		this->sign = i.sign; 
		return *this;
	}

	Integer Integer::operator-() const {
		sign = !sign;
		return Integer(*this);
	}

	Integer Integer::operator+() const {
		sign = false;
		return Integer(*this);
	}

	Integer& Integer::operator+=(const Integer& i) {
		(*this) = (*this) + i;
		return *this;
	}

	Integer& Integer::operator-=(const Integer& i) {
		(*this) = (*this) - i;
		return *this;
	}

	Integer& Integer::operator*=(const Integer& i) {
		(*this) = (*this) * i;
		return *this;
	}

	Integer& Integer::operator/=(const Integer& i) {
		(*this) = (*this)/i;
		return *this;
	}

	Integer& Integer::operator%=(const Integer& i) {
		(*this) = (*this)%i;
		return *this;
	}
	/**
	 * @brief Add two integers
	 * 
	 * @param lhs 
	 * @param rhs 
	 * @return Integer 
	 */
	Integer operator+(const Integer& lhs, const Integer& rhs) {
		Integer addition;
		
		if (lhs.getSign() == rhs.getSign()){ //a + b
			addition.setNumber(lhs.add(lhs.getNumber(), rhs.getNumber()));
			addition.setSign(lhs.getSign());
		} else if (lhs.getSign() == true && rhs.getSign() == false){ //-a + b
			//-a+b = b - a
			addition.setNumber(rhs.subtract(rhs.getNumber(), lhs.getNumber()));
			addition.setSign(lhs.absolute() > rhs.absolute()); // if a > b then -a + b is -ve (true)
		} else { //a + (-b) = a - b
			addition.setNumber(lhs.subtract(lhs.getNumber(), rhs.getNumber()));
			// std::cout << (lhs > rhs) << std::endl;
			addition.setSign(lhs.absolute() < rhs.absolute()); //-ve if |a| < |b| 
		}

		if (addition.getNumber() == "0"){
			addition.setSign(false); //defualt if zero set to false
		}
		return addition;
	}
	/**
	 * @brief Add two strings
	 * 
	 * @param number1 
	 * @param number2 
	 * @return std::string 
	 */
	std::string Integer::add(std::string number1, std::string number2) const{
		std::string add = (number1.length() > number2.length()) ? number1 : number2;
		char carry = '0';
		int diffLength = abs( (int) (number1.size() - number2.size()));
		if (number1.size() > number2.size()){
			number2.insert(0, diffLength, '0');
		} else {
			number1.insert(0, diffLength, '0');
		}

		for (int i = number1.size()-1; i>= 0; --i){
			add[i] = ((carry-'0') + (number1[i]-'0')+ (number2[i]-'0')) + '0';
			if (i != 0){
				if (add[i] > '9'){
					add[i] -= 10;
					carry = '1';
				} else {
					carry = '0';
				}
			}
		}
		if (add[0] > '9'){
			add[0] -= 10;
			add.insert(0,1,'1');
		}
		while (add[0] == '0' && add.length() != 1){ //remove leading zeros
			add.erase(0,1);
		}

		return add;
	}
	/**
	 * @brief Subtract two strings
	 * 
	 * @param number1 
	 * @param number2 
	 * @return std::string 
	 */
	std::string Integer::subtract(std::string str1, std::string str2) const{
		// make sure str1 is not smaller
		if (isSmaller(str1, str2))
			swap(str1, str2);
	
		//result
		std::string str = "";
	
		// Calculate length of both strings
		int n1 = str1.length(), n2 = str2.length();
		
		str1 = reverse(str1);
		str2 = reverse(str2);
	
		int carry = 0;
	
		// subtract index by index
		for (int i = 0; i < n2; i++) {	
			int sub
				= ((str1[i] - '0') - (str2[i] - '0') - carry);
	
			// If subtraction is less then zero
			// then  add 10 into sub and take carry as 1 for next step
			if (sub < 0) {
				sub = sub + 10;
				carry = 1;
			}
			else
				carry = 0;
	
			str.push_back(sub + '0');
		}
	
		// subtract remaining digits of larger number
		for (int i = n2; i < n1; i++) {
			int sub = ((str1[i] - '0') - carry);
	
			// if the sub value is -ve, then make it positive
			if (sub < 0) {
				sub = sub + 10;
				carry = 1;
			}
			else
				carry = 0;
	
			str.push_back(sub + '0');
		}
	
		// reverse resultant string
		str = reverse(str);
		while (str[0] == '0' && str.length() != 1){ //remove leading zeros
			str.erase(0,1);
		}

		return str;
	}

	std::string Integer::reverse(std::string str) const{
		int len = str.length();
		int n = len-1;
		for (int i = 0; i < (len/2);i++){
			std::swap(str[i], str[n]);
			n = n-1;
		}
		return str;
	}
	/**
	 * @brief subtract two integers
	 * 
	 * a - b = a + -b
	 * 
	 * @param lhs 
	 * @param rhs 
	 * @return Integer 
	 */
	Integer operator-(const Integer& lhs, const Integer& rhs) {
		Integer result;
		result.setSign(!rhs.getSign());
		result.setNumber(rhs.getNumber());
		return (lhs + result);
	}

	Integer operator*(const Integer& lhs, const Integer& rhs) {
		Integer multiply;
		multiply.setNumber(lhs.multiply(lhs.getNumber(), rhs.getNumber()));
		multiply.setSign(lhs.getSign() != rhs.getSign());

		if (multiply.getNumber() == "0"){
			multiply.setSign(false);
		}
		return multiply;
	}
	/**
	 * @brief Multiply two strings
	 * 
	 * @param number1 
	 * @param number2 
	 * @return std::string 
	 */
	std::string Integer::multiply(std::string number1, std::string number2) const{
		if (number1.length()>number2.length()){
			number1.swap(number2);
		}

		std::string res = "0";
		for (int i=number1.length()-1; i>=0; --i){
			std::string temp = number2;
			int currDigit = number1[i]-'0';
			int carry = 0;
			for (int j = temp.length()-1; j >= 0; --j){
				temp[j] = ((temp[j]-'0') * currDigit) + carry;

				if (temp[j] > 9){
					carry = (temp[j]/10);
					temp[j] -= (carry*10);
				} else {
					carry = 0;
				}
				temp[j] += '0'; 
			}
			if (carry > 0){
				temp.insert(0, 1, (carry+'0'));
			}
			temp.append((number1.length()-i-1), '0'); //i.e * by 10,100 etc
			res = add(res, temp); // O(n)
		}

		while (res[0] == '0' && res.length() != 1){ //remove leading zeros
			res.erase(0,1);
		}
		return res;
	}

	Integer operator/(const Integer& lhs, const Integer& rhs) {
		if (rhs == Integer("0")){
			throw "Division by zero is not allowed";
		}
		Integer quotient;
		quotient = lhs.divide(lhs.getNumber(), rhs.getNumber()).first;

		quotient.setSign(lhs.getSign() != rhs.getSign());

		if (quotient.getNumber() == "0"){
			quotient.setSign(false);
		}
		return quotient;
	}

	Integer operator%(const Integer& lhs, const Integer& rhs) {
		Integer modulo;
		modulo = lhs.divide(lhs.getNumber(), rhs.getNumber()).second;
		modulo.setSign(lhs.getSign() != rhs.getSign());

		if (modulo.getNumber() == "0"){
			modulo.setSign(false);
		}
		return modulo;
	}
	/**
	 * @brief Divide two integers
	 * 
	 * @param lhs 
	 * @param rhs 
	 * @return std::pair<Integer, Integer> . quotient, remainder
	 */
	std::pair<Integer, Integer> Integer::divide (std::string lhs, std::string rhs) const{ 
		Integer N = Integer(lhs); //numerator
		Integer D = Integer(rhs); //denominantor
		Integer R = Integer("0"); //Remiainder
		Integer Q = Integer("0"); //quotient
		Integer step = Integer("1");
		int sizeDiff = lhs.length() - rhs.length(); //differnce in length of numbers (Q)
		
		for (int i = 0; i < sizeDiff; i++){
			step *= Integer("10");
		}
		if (D > N){ //zero
			return std::make_pair(Q, N-D*Q);
		}
		if (D == Integer("0")){
			throw ("division by zero");
		}

		if (N == D){
			Q = Integer("1");
			R = N - D*Q;
			return std::make_pair(Q, R);
		}
		Q = step;
		Integer guess;
		Integer diff;
		// std::cout << "Q: " << Q << std::endl;
		// std::cout << "numerator" << N << std::endl;
		// std::cout << "Denominator" << D << std::endl;

		int count = 0;
		int stepIndex = N.getNumber().length(); //for adjusting step length
		while (true){
			// std::cout << "Q: " << Q << std::endl;
			// std::cout << "step: " << step << std::endl;
			// std::cout << "diff " << diff << std::endl;
			guess = D * Q;
			diff = N - guess;
			if (Integer(diff.getNumber()) < Integer(D.getNumber())){
				if (guess <= N){
					break;
				}
			}
			if (guess > N){
				if (Q > Integer("100000")){
					stepIndex = diff.getNumber().length();  //not quite
				}
				//good here
				step = Integer(step.getNumber().substr(0, std::max(stepIndex-=1, 1)));
				if (step < Integer("1")){
					step = Integer("1");
				}
				Q -= step;
			} else {
				if (Q > Integer("100000")){
					stepIndex = diff.getNumber().length();  //not quite
				}
				//good here
				step = Integer(step.getNumber().substr(0, std::max(stepIndex-=1, 1)));
				if (step < Integer("1")){
					step = Integer("1");
				}
				Q += step;
			}
			count++;
			// if (count > 5){
			// 	break;
			// }
		}
		// std::cout << "diff: " << diff.getNumber() <<std::endl;
		// std::cout << "D: " << D.getNumber() <<std::endl; 
		// std::cout << "exit cond: " << (Integer(diff.getNumber()) < Integer(D.getNumber())) << std::endl;
		// std::cout << "quotient " << Q << std::endl;

		R = N - D*Q;

		// std::cout << "R: " << R << std::endl;

		std::string result = Q.getNumber();
		while (result[0] == '0' && result.length() != 1){ //remove leading zeros
			result.erase(0,1);
		}
		Q = Integer(result);
		std::string remString = R.getNumber();
		while (remString[0] == '0' && remString.length() != 1){ //remove leading zeros
			remString.erase(0,1);
		}
		R = Integer(remString);
		return std::make_pair(Q, R);

	}


	std::ostream& operator<<(std::ostream& os, const Integer& i) {
		std::stringstream ss;
		
		if (i.getSign()){
			os << "-" << i.getNumber() << std::endl;
		} else {
			os << "+" << i.getNumber() << std::endl;
		}
		return os;
	}

	std::istream& operator>>(std::istream& is, Integer& i) {
		is >> i.sign >> i.number;
		return is;
	}
	/**
	 * @brief is smaller of two strings
	 *  (numerical)
	 * TESTED
	 * @param str1 
	 * @param str2 
	 * @return true 
	 * @return false 
	 */
	bool Integer::isSmaller(std::string str1, std::string str2) const{
		int n1 = str1.length(), n2 = str2.length();
		if (n1 < n2)
			return true;
		if (n2 < n1)
			return false;
	
		for (int i = 0; i < n1; i++)
			if (str1[i] < str2[i])
				return true;
			else if (str1[i] > str2[i])
				return false;
	
		return false;
	}
	/**
	 * @brief lhs < rhs
	 * 
	 * @param lhs 
	 * @param rhs 
	 * @return true 
	 * @return false 
	 */
	bool operator<(const Integer& lhs, const Integer& rhs) {
		if (lhs.getSign() == rhs.getSign()){ //same sign
			return lhs.isSmaller(lhs.getNumber(), rhs.getNumber());
		}
		if (lhs.getSign() == true && rhs.getSign() == false){ //left negative, right positive
			return true;
		}
		return false;
	}

	bool operator> (const Integer& lhs, const Integer& rhs) {
		return !(lhs < rhs || rhs == lhs); 
	}

	bool operator<=(const Integer& lhs, const Integer& rhs) {
		return (lhs < rhs || lhs == rhs);
	}

	bool operator>=(const Integer& lhs, const Integer& rhs) {
		return (lhs > rhs || lhs == rhs);
	}

	bool operator==(const Integer& lhs, const Integer& rhs) {
		return lhs.getNumber() == rhs.getNumber() && lhs.getSign() == rhs.getSign();
	}

	bool operator!=(const Integer& lhs, const Integer& rhs) {
		return !(lhs == rhs);
	}


	Integer gcd(const Integer& a, const Integer& b) {
		if (b == Integer("0")){
			return a;
		}
		// std::cout << b << std::endl;
		return gcd(b, a % b);
	}

	std::string Integer::getNumber() const{
		return number;
	}
	void Integer::setNumber(std::string str){
		number = str;
	}
	/**
	 * @brief Get sign
	 * 
	 * @return true (negative)
	 * @return false (positive)
	 */
	bool Integer::getSign() const{
		return sign;
	}
	void Integer::setSign(bool s){
		sign = s;
	}
	/**
	 * @brief Get absolute value of integer
	 * 
	 * @return Integer 
	 */
	Integer Integer::absolute() const{
		return Integer(getNumber());
	}
}
