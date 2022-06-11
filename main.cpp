#include <iostream>
#include <string>
#include <climits>
#include "Integer.h"
#include "Rational.h"
#include <vector>

using namespace cosc326;

int main()
{   
    Integer a("-42949");
    Integer c("922337");
    Integer d("42949");
    Integer f("20");
    Integer e("5");
    Integer d1("42949");
    std::cout << "a: " << a << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "d: " << d << std::endl;
    std::string al = "2452345345234123123178"; 
    std::string bl = "23459023850983290589042"; //this larger
    Integer ai(al);
    Integer bi(bl);
    std::cout << "ai: " << ai << std::endl;
    std::cout << "bi: " << bi << std::endl;
    std::cout << "ai / bi: " << ai / bi  << std::endl; 
    std::cout << "bi / ai: " << bi / ai  << std::endl; 

    std::cout << "ai % bi " << ai % bi  << std::endl;

    

    std::cout << "c + d: "<< c + d  << std::endl;
    std::cout << "c - d: "<< c - d  << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "a + c: "<< a + c  << std::endl;
    std::cout << a  * a << std::endl; 
    std::cout << c % d  << std::endl; 
    std::cout << "f / e: " << f/e << std::endl;
    std::cout << "c / d: " << c/d << std::endl; 
    std::cout << "3 -= 4: " << (f -= e) << std::endl;
    std::cout << "3 - 4: " << (f - e) << std::endl; 
    std::cout << "c >= d: " << (c >= d) << std::endl; 
    // std::cout << "05 - 20: " << e-f << std::endl;
    std::cout << "00 > 20: " << (Integer("00") >= Integer("20")) << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << (d1 < d) << std::endl;

    std::cout << "gcd(f,e): " << gcd(f, e) << std::endl;
    std::cout << "gcd(3212254,12098): " << gcd(Integer("3212254"), Integer("12098")) << std::endl;
    std::cout << "gcd(ai,bi): " << gcd(ai, bi) << std::endl;
    std::cout << "f % e: " << f%e << std::endl;
    // Integer a("922337");
	Integer b("42949");
	std::cout << "b -  a: " << b - a << std::endl;
	// // std::cout << b << std::endl;

    cosc326::Rational r2(a,b);

    std::cout << "r2: " << r2 << std::endl;
    Rational r3 ("3.4/5");
    Rational r4 ("9.1/3");
    std::cout << "r3: " << r3 << std::endl;
    std::cout << "r4: " << r4 << std::endl;
    std::cout << "r3 + r4: " << r3 + r4 << std::endl; //13.2/15
    std::cout << "197 / 15: " << Integer("197") / Integer("15") << std::endl;

    std::cout << "r(0): " << Rational("0") << std::endl;
    std::cout << "r3 < r4: " << (r3 < r4) << std::endl;
    std::cout << "r3 - r4: " << r3 - r4 << std::endl;
    std::cout << "r3: " << r3 << std::endl;
    std::cout << "r4 > r3: " << (r4 > r3) << std::endl;
    
    // std::cout << Integer("57") - Integer("140") << std::endl;

    std::cout << "gcd(ai, bi): " << gcd(ai, bi) << std::endl; //no more!
    std::cout << "inf loop: " << Integer("159903932569026")/ Integer("5185961365832") << std::endl; //no more!
    std::cout << "inf loop2: " << Integer("18491780")/ Integer("30022") << std::endl; //no more!

    Rational r2T("2/3");
    std::cout << "r2T: " << r2T <<  std::endl;
    Rational r7("+15.32/2"); 
    std:: cout << "r7: " << r7 << std::endl; //31

    Rational r8(Integer("15"), Integer("32"), Integer("2")); 
    std::cout << "r8: " << r8 << std::endl;

    Rational r5T("4/3");
    std::cout << "r2T + r5T: " << r2T + r5T << std::endl; 

    
    cosc326::Rational rLT(bi,ai);
    // std::cout << "gcd(large): " << gcd(bi, ai) << std::endl;
    std::cout << "26 / 12: " << Integer("26") / Integer("12") << std::endl;
    std::cout << "rLT: " << rLT << std::endl;

    Integer num = Integer("20");
    Integer denom = Integer("3");
    std::cout << "20 / 3: " << num/denom << std::endl;
    std::cout << "23459023850983290589042 / 2: " << Integer("23459023850983290589042")/Integer("2") << std::endl;

    //now this doesn't work
    std::cout << "13 / -5/7: " << Rational("13") / Rational("-5/7") << std::endl;

    std::cout << "-3.2/4: " << Rational("-3.2/4") << std::endl;

    
    return 0;

}
